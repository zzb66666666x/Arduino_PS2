#include <PS2X_lib.h>  //for v1.6
#include "Definitions.h"
#include <Servo.h>
PS2X ps2x; // create PS2 Controller Class
RAWDATA PS2data;
Servo MyservoA;
Servo MyservoB;

void setup(){
Serial.begin(57600);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
//pinMode(speedPinA,OUTPUT);
//pinMode(speedPinB,OUTPUT);
pinMode(servoPinA,OUTPUT);
pinMode(servoPinB,OUTPUT);
pinMode(FrictionPulleyA,OUTPUT);
pinMode(FrictionPulleyB,OUTPUT);
pinMode(SupplyMotor,OUTPUT);
digitalWrite(SupplyMotor,HIGH);
MyservoA.attach(servoPinA);//下层左右转动的舵机
MyservoB.attach(servoPinB);
delay(300);
angle_init();
SpeedControllerINIT();
error = ps2x.config_gamepad(12,11,10,13,false,true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

if(error == 0){
  Serial.println("Found Controller, configured successful");
  Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  //Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to [url]www.billporter.info[/url] for updates and to report bugs.");
}
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit [url]www.billporter.info[/url] for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit [url]www.billporter.info[/url] for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
//FINISH SET UP HERE.  
}

void dataFetch(){
  PS2data.UP = ps2x.Button(PSB_PAD_UP);
  PS2data.DOWN = ps2x.Button(PSB_PAD_DOWN);
  PS2data.LEFT = ps2x.Button(PSB_PAD_LEFT);
  PS2data.RIGHT = ps2x.Button(PSB_PAD_RIGHT);
  PS2data.CIRCLE = ps2x.Button(PSB_CIRCLE);
  PS2data.STOP = ps2x.ButtonPressed(PSB_CROSS);
  PS2data.START = ps2x.ButtonPressed(PSB_TRIANGLE);
  PS2data.INIT = ps2x.ButtonPressed(PSB_SQUARE);
  PS2data.RX = 255-ps2x.Analog(PSS_RX);
  PS2data.RY = ps2x.Analog(PSS_RY);
  PS2data.LX = ps2x.Analog(PSS_LX);
  PS2data.LY = ps2x.Analog(PSS_LY);
  //Serial.println("Finished");
  }
void shoot(){
  digitalWrite(SupplyMotor,HIGH);
  while (1){
    digitalWrite(SupplyMotor,LOW);
    digitalWrite(FrictionPulleyA,HIGH);
    digitalWrite(FrictionPulleyB,HIGH);
    delayMicroseconds(1600);
    digitalWrite(FrictionPulleyA,LOW);
    digitalWrite(FrictionPulleyB,LOW);
    delayMicroseconds(18400);
    ps2x.read_gamepad();
    if (ps2x.ButtonReleased(PSB_CIRCLE)){
      digitalWrite(SupplyMotor,HIGH);
      digitalWrite(FrictionPulleyA,HIGH);
      digitalWrite(FrictionPulleyB,HIGH);
      delayMicroseconds(1000);//高电平持续2000微秒（油门最高点）
      digitalWrite(FrictionPulleyA,LOW);
      digitalWrite(FrictionPulleyB,LOW);
      delayMicroseconds(19000);     
      break;
      }
    }
  }  
void Car_Control(){
  if (PS2data.START){CarState = 1;}
  else if (PS2data.STOP){CarState = 0;}
  else {//pass
  }
  if (CarState){
  if ((PS2data.UP || PS2data.DOWN || PS2data.LEFT || PS2data.RIGHT)){
    if (PS2data.UP){
      //Serial.println("UP");
      speed = 200;
      goAhead(speed);
      }
    if (PS2data.DOWN){
      speed = 200;
      goBack(speed);
      }
    if (PS2data.LEFT){
      speed = 255;
      turnLeft(speed);      
      }
    if (PS2data.RIGHT){
      speed = 255;
      turnRight(speed);      
      }
    }
  else {//由摇杆接管
    if (PS2data.LX < 100){
      //左转
      //speed = 2*(127-PS2data.LX);
      speed = 255;
      turnLeft(speed);
      }
    else if (PS2data.LX > 155){
      //右转
      //speed = 2*(PS2data.LX-128);
      speed = 255;
      turnRight(speed);
      }
    else {
      //Don't have to turn around.
      //Serial.println("Go ahead or back.");
      //Serial.println(PS2data.LY)
      if (PS2data.LY < 125){
        //前进
        //speed = 2*(127-PS2data.LY);
        speed = 255;
        goAhead(speed);
        }
      else if (PS2data.LY > 130){
        //后退
        //speed = 2*(PS2data.LY-128);
        speed = 255;
        goBack(speed);
        }
      else {//摇杆中立
        speed =0;
        halt(speed);
        }
      }
    }
    if (!(((PS2data.RX >= 123)&&(PS2data.RX <= 132))&&((PS2data.RY >= 123)&&(PS2data.RY <= 132)))){//右摇杆不在中心
        angle(PS2data.RX,PS2data.RY);
        servo();
        }
    else{//右摇杆就在中心附近
      //检查是否归位
      if (PS2data.INIT){
        angle_init();
        }
      }
    if (PS2data.CIRCLE){
        shoot();
      }
    else{
      digitalWrite(SupplyMotor,HIGH);
      digitalWrite(FrictionPulleyA,HIGH);
      digitalWrite(FrictionPulleyB,HIGH);
      delayMicroseconds(1000);//高电平持续2000微秒（油门最高点）
      digitalWrite(FrictionPulleyA,LOW);
      digitalWrite(FrictionPulleyB,LOW);
      delayMicroseconds(19000);      
      }
  }
  else {//CarState is 0
    speed = 0;
    digitalWrite(SupplyMotor,HIGH);
    digitalWrite(FrictionPulleyA,LOW);
    digitalWrite(FrictionPulleyB,LOW);
    halt(speed);
  }
}

void angle_init(){
  AngleLeftRight = DefaultLRAngle;
  AngleUpDown = DefaultUDAngle;
  for (int i = 0; i<50; i++){
    MyservoB.write(AngleUpDown);
    MyservoA.write(AngleLeftRight);
    }
  }
  
void servo(){
  int i,j;
  for (i=0; i<=50; i++){
    MyservoA.write(AngleLeftRight);
    }
  for (j=0; j<=50; j++){
    MyservoB.write(AngleUpDown);
    }
  }

void loop(){  
  if(error == 1) //skip loop if no controller found
  {return;}   
  if(type == 2) //Guitar Hero Controller
   {return;}
  else{
    //DualShock Controller
    ps2x.read_gamepad();
    dataFetch();
    delay(20);  
    //Serial.println(PS2data.LX); 
    Car_Control();
  }
}
