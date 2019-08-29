//Change pin definitions for uno
#define IN1 4 //
#define IN2 5 //
#define IN3 6 //
#define IN4 7 //
//#define speedPinA 8 //
//#define speedPinB 9 //
#define servoPinA 3 //
#define servoPinB 15 //
#define DefaultLRAngle 100
#define DefaultUDAngle 90
//#define FrictionPulleyA 24 //Left motor.
//#define FrictionPulleyB 25 //Right motor.
//#define M2006Motor 26

int speed;
int error = 0; 
byte type = 0;
byte vibrate = 0;
int AngleLeftRight = 100;//Left and right, servoA
int AngleUpDown = 90;//Up and down, servoB
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
  boolean StopShooting;
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
  AngleUpDown = map(RY,0,255,82,98);//假设竖直方向上水平对应舵机是90度,往下转角度减小（待修改）。
  }

void shoot(){
   //analogWrite(FrictionPulleyA,255);
   //analogWrite(FrictionPulleyA,255);
   //delay(30);
   //analogWrite(M2006Motor,255);
  }

