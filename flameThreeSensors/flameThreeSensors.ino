//Will turn on left motor if left flame sensor detect a flame
//Will turn on right motor if the right flame sensor detects a flame
//Both motors will go if both sensors detect a flame
//LEFT AND RIGHT HAVE BEEN CHANGED SO THAT THEY ARE ACTUALLY LEFT AND RIGHT****************************************************

//ANAOLG VALUES ARE FROM 0 TO 1023
//flameRight is digital
//flameMiddle is analog

const int AIA = 6; //on the right
const int AIB = 7;
const int BIA = 3; //on the left
const int BIB = 5;
byte speed = 255;

int rightFlame = A2; // FLAME SENSORS
int leftFlame = A3;
int middleFlame = A4; // This will most likely change

int readRightFlame;
int readLeftFlame;
int readMiddleFlame;

void setup() {
  // put your setup code here, to run once:
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  
  pinMode(rightFlame, INPUT);
  digitalWrite(rightFlame, INPUT_PULLUP);  // set pullup on analog pin 0

  pinMode(leftFlame, INPUT);
  digitalWrite(leftFlame, INPUT_PULLUP);  // set pullup on analog pin 0

  pinMode(middleFlame, INPUT);
  digitalWrite(middleFlame, INPUT_PULLUP);  // set pullup on analog pin 0
}

void loop() {
  // put your main code here, to run repeatedly:

  readRightFlame = analogRead(rightFlame);
  readLeftFlame = analogRead(leftFlame);
  readMiddleFlame = analogRead(middleFlame);

  if(readMiddleFlame < 500){
    //go forward
    forward();
  }else if(readRightFlame < 500){
    //right motor
    rightMotor();
  }else if(readLeftFlame < 500){
    //left motor
    leftMotor();
  }else{
    stopping();
  }

}

void stopping()
{
 analogWrite(AIA, 0);
 analogWrite(AIB, 0);
 analogWrite(BIA, 0);
 analogWrite(BIB, 0);
}

void backward()
{
 analogWrite(AIA, 0);
 analogWrite(AIB, speed);
 analogWrite(BIA, 0);
 analogWrite(BIB, speed);
}

void forward()
{
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, speed);
 analogWrite(BIB,0);
}

void left()
{
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, 0);
 analogWrite(BIB, speed);
 
}

void right()
{
 analogWrite(AIA, 0);
 analogWrite(AIB, speed);
 analogWrite(BIA, speed);
 analogWrite(BIB, 0);
}

void leftMotor(){  
 analogWrite(AIA, 0);
 analogWrite(AIB, 0);
 analogWrite(BIA, speed);
 analogWrite(BIB,0);
}

void rightMotor(){
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB,0);
}

