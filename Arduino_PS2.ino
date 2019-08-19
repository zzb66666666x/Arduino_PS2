#include <PS2X_lib.h>  //for v1.6
#include "Definitions.h"

PS2X ps2x; // create PS2 Controller Class

void setup(){
Serial.begin(57600);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(speedPinB,OUTPUT);
delay(300);
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
  angle_init();
//FINISH SET UP HERE.  
}

void Car_Control_A(){
      //Serial.println(controlMode);
      if(ps2x.Button(PSB_START)){
        //Serial.println("START");
        speed = 120;
        goAhead(speed);
        }
      if(ps2x.Button(PSB_PAD_UP)){
        //Serial.println("up");
        speed = 200;
        goAhead(speed);
        }
      if(ps2x.Button(PSB_PAD_DOWN)){
        //Serial.println(DOWN);
        speed = 200;
        goBack(speed);
        }
      if(ps2x.Button(PSB_PAD_LEFT)){
        //Serial.println("LEFT");
        speed = 200;
        turnLeft(speed);
        }
      if(ps2x.Button(PSB_PAD_RIGHT)){
        //Serial.println("Right");
        speed = 200;
        turnRight(speed);
        }
      if(ps2x.Button(PSB_SELECT)){
        speed = 0;
        halt(speed);  
        }
      err1 = abs(RX-128);err2 = abs(RY-128);
      //avoid some mistake
      if(err1 >= 3 || err2 >= 3){
        angle(RX,RY);
        for (int i = 0; i<5; i++){
        servo(servoPinA,AngleLeftRight);
        servo(servoPinB,AngleUpDown);
        }
        }
}

void Car_Control_B(){
      //Serial.println(controlMode);
      //前进
      if (LY<127){
        speed = 2*(127-LY);
        goAhead(speed);
      }
      //后退
      if (LY>127){
        speed=2*(LY-128);
        goBack(speed);
      }
      //左转
      if (LX<128){
        speed = 2*(127-LX);
        turnLeft(speed);
      }
      //右转
      if (LX>128){
              //Serial.println(LX);
        speed=2*(LX -128);
        turnRight(speed);
      }
      //如果摇杆居中
      if (LY>=127 && LY<=127 && LX>=128 && LX<=128){
        speed = 0;
        halt(speed);
      }
      err1 = abs(RX-128);err2 = abs(RY-128);
      //avoid some mistake
      if (err1 >= 3 || err2 >= 3){
        angle(RX,RY);
        for (int i = 0; i<50; i++){
        servo(servoPinA,AngleLeftRight);
        servo(servoPinB,AngleUpDown);
        }        
        }
      if (ps2x.Button(PSB_CIRCLE)){
        shoot();  
      }
}

void loop(){  
  if(error == 1) //skip loop if no controller found
  {return;}   
  if(type == 2) //Guitar Hero Controller
   {return;}
  else{
    //DualShock Controller
    ps2x.read_gamepad(false, vibrate);
    RY=ps2x.Analog(PSS_RY);
    RX=ps2x.Analog(PSS_RX);
    LY=ps2x.Analog(PSS_LY);
    LX=ps2x.Analog(PSS_LX);    
    if (loopCount()){
      delay(100);
      loopCounter++;
      }
    Serial.println(RX); 
    //Serial.println(RX);   
    if(ps2x.ButtonPressed(PSB_TRIANGLE)){
      if (controlMode == 1){controlMode = 2;}
      else {controlMode = 1;}
      }  
    switch(controlMode)
    {
      case 1:
        Car_Control_A();
        break;
      case 2:
        Car_Control_B();
        break;
      default:break;
     }
  }
}
