//Change pin definitions for uno
#define IN1 4 //
#define IN2 5 //
#define IN3 6 //
#define IN4 7 //
//#define speedPinA 8 
//#define speedPinB 9 
#define servoPinA 14 //
#define servoPinB 15 //
#define DefaultLRAngle 100
#define DefaultUDAngle 96
#define FrictionPulleyA 16 //Left motor.
#define FrictionPulleyB 17 //Right motor.
#define SupplyMotor 18

int speed;
int error = 0; 
byte type = 0;
byte vibrate = 0;
int AngleLeftRight = DefaultLRAngle;//Left and right, servoA
int AngleUpDown = DefaultUDAngle;//Up and down, servoB
int CarState = 0;

typedef struct{
  boolean UP;
  boolean DOWN;
  boolean LEFT;
  boolean RIGHT;
  boolean CIRCLE; 
  boolean STOP;
  boolean START;
  boolean INIT;
  int LY;
  int LX;
  int RY;
  int RX;
  }RAWDATA;

void turnRight(int speed){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  //analogWrite(speedPinA, speed);
  //analogWrite(speedPinB, speed);  
  }

void turnLeft(int speed){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  //analogWrite(speedPinA, speed);
  //analogWrite(speedPinB, speed);
  }

void goAhead(int speed){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  //analogWrite(speedPinA, speed);
  //analogWrite(speedPinB, speed);  
  }

void goBack(int speed){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //analogWrite(speedPinA, speed);
  //analogWrite(speedPinB, speed);  
  }

void halt(int speed){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);  
  //analogWrite(speedPinA,speed);
  //analogWrite(speedPinB,speed);
  }


void angle(int RX, int RY){
  AngleLeftRight = map(RX,0,255,75,125);
  AngleUpDown = map(RY,0,255,88,104);
  }

void SpeedControllerINIT(){
  for(int i=0;i<=1000;i++){
    digitalWrite(FrictionPulleyA,HIGH);
    digitalWrite(FrictionPulleyB,HIGH);
    delayMicroseconds(2000);//高电平持续2000微秒（油门最高点）
    digitalWrite(FrictionPulleyA,LOW);
    digitalWrite(FrictionPulleyB,LOW);
    delayMicroseconds(18000);
    }
  for(int i=0;i<=1000;i++){
    digitalWrite(FrictionPulleyA,HIGH);
    digitalWrite(FrictionPulleyB,HIGH);
    delayMicroseconds(1000);//高电平持续1000微秒（油门最低点）
    digitalWrite(FrictionPulleyA,LOW);
    digitalWrite(FrictionPulleyB,LOW);
    delayMicroseconds(19000);
    }
  }

  

