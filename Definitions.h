#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define speedPinA 8
#define speedPinB 9
#define servoPinA 2
#define servoPinB 3

int speed;
int error = 0; 
byte type = 0;
byte vibrate = 0;
int AngleLeftRight;//Left and right, servoA
int AngleUpDown;//Up and down, servoB
int pulsewidth;
int err1; int err2;
int CarState = 0;

typedef struct{
  boolean UP;
  boolean DOWN;
  boolean LEFT;
  boolean RIGHT;
  boolean CIRCLE; 
  boolean STOP;
  boolean START;
  int LY;
  int LX;
  int RY;
  int RX;
  }RAWDATA;

void turnLeft(int speed){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);  
  }

void turnRight(int speed){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);
  }

void goAhead(int speed){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);  
  }

void goBack(int speed){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(speedPinA, speed);
  analogWrite(speedPinB, speed);  
  }

void halt(int speed){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);  
  analogWrite(speedPinA,speed);
  analogWrite(speedPinB,speed);
  }

void servo(int Mypin,int Myangle){
  pulsewidth=(Myangle*11)+500;
  digitalWrite(Mypin,HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(Mypin,LOW);
  delay(20-pulsewidth/1000);
  }

void angle(int RX, int RY){
  AngleLeftRight = map(RX,0,255,0,179);
  AngleUpDown = map(RY,0,255,60,120);//假设竖直方向上水平对应舵机是90度,往下转角度减小（待修改）。
  }

void shoot(){
  
  }

void angle_init(){
  for (int i = 0; i<50; i++){
    //The data need to be justified.
    servo(servoPinA,90);
    servo(servoPinB,90);
    }
  }

