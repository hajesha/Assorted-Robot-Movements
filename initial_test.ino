//this is the initial version of the code for lab 4
//LEFT AND RIGHT HAVE BEEN CHANGED SO THAT THEY ARE ACTUALLY LEFT AND RIGHT****************************************************

#include <Ultrasonic.h>

const int AIA = 6; //on the right
const int AIB = 7;
const int BIA = 3; //on the left
const int BIB = 5;
byte speed = 255;

//EDGE SWITCHES
int inPin1 = 9;//switch 1 EDGE
int inPin2 = 10;//switch 2 EDGE


//INFRARED LINES
int ir = 4; // pin IR is in
int ir2 = 8; //pin the 2nd IR is in

//FLAME SENSORS
int rightFlame = A2;
int leftFlame = A3;

//OBJECT DETECTION
Ultrasonic ultraCold(A5, A4); //1st number = trigger pin; 2nd num = echo pin
Ultrasonic ultraWarm(A1, A0);

//READINGS
int reading1; //switch 1
int reading2; //switch 2

int reading3; //IR1
int reading4; //IR2

int readRightFlame;
int readLeftFlame;

//TIMER THINGS:
unsigned long loopTime;
unsigned long currentTime;

long timer = 5; //to be used for the line detection <- right now set for 3 sec (in milliseconds)
unsigned long previousTime; //last time the timer was updated

boolean flag;

int state;

void setup() {
  // put your setup code here, to run once:
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  //EDGE DETECTION
  pinMode(inPin1, INPUT);  //intializing the inpin
  digitalWrite(inPin1, HIGH);
  pinMode(inPin2, INPUT);  //intializing the inpin
  digitalWrite(inPin2, HIGH);

  //LINE DETECTION
  pinMode(ir, INPUT);  //intializing the iR
  digitalWrite(ir, HIGH);
  pinMode(ir2, INPUT);  //intializing iR2
  digitalWrite(ir2, HIGH);
  
  //FLAME SENSORS
  pinMode(rightFlame, INPUT);
  digitalWrite(rightFlame, INPUT_PULLUP);  // set pullup on analog pin 0

  pinMode(leftFlame, INPUT);
  digitalWrite(leftFlame, INPUT_PULLUP);  // set pullup on analog pin 0

  //TIMER STUFF:
  previousTime = 0;

  flag = false;

  loopTime = 0; //corner turns

}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  
  //EDGES:
  reading1 = digitalRead(inPin1);   //reads input from the switch1
  reading2 = digitalRead(inPin2);   //reads input from the switch2

  //LINE:
  reading3 = digitalRead(ir);   //reads input from infrared
  reading4 = digitalRead(ir2);   //reads input from infrared2

  //FLAME SENSING:
  readRightFlame = analogRead(rightFlame);
  readLeftFlame = analogRead(leftFlame);

  if (reading1 == LOW){//SWITCH1 EDGE 
      backward();
      delay(500);
      right();
      delay(900);
  
  }else if (reading2 == LOW){//SWITCH2 EDGE
      backward();
      delay(500);
      left();
      delay(550);

  }else if(reading3 == HIGH && reading4 == HIGH){
    right();
    delay(400);
    previousTime = currentTime + 2000;
    flag = true;
    
  }else if(reading3 == HIGH){ 
      left();
      previousTime = currentTime + 2000;
      flag = true;
  
  }else if(reading4 == HIGH){
      right();
      previousTime = currentTime + 2000;
      flag = true;
      
  }else if((ultraCold.distanceRead(CM) < 30 && ultraCold.distanceRead(CM) > 1) && (ultraWarm.distanceRead(CM) < 30 && ultraWarm.distanceRead(CM) > 1) ){
      //they are both pushed
      right();
      delay(500);
      flag = false;
      
  }else if(ultraWarm.distanceRead(CM) < 30 && ultraWarm.distanceRead(CM) > 1){
      //motor A
      left();
      delay(500);
      flag = false;
      
  }else if(ultraCold.distanceRead(CM) < 30 && ultraCold.distanceRead(CM) > 1){
      //motor B
      right();
      delay(300);
      flag = false;
      
  }else if ( previousTime > currentTime && reading3 == LOW && flag == true) {
    forwardTurnLefter();

  }else if (previousTime > currentTime && reading4 == LOW && flag == true){
    forwardTurnRighter();
    
  }else if ( previousTime <= currentTime && flag == true ){
    flag = false; 
    
  }else {
    //previousTime = currentTime;
    loopTime = 0;
    forward();
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

void forwardTurnLefter()
{ 
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, speed-70);
 analogWrite(BIB,0);
}

void forwardTurnRighter(){
  analogWrite(AIA, speed - 70);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB,0);
}

