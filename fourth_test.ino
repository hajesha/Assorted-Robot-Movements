#include <Ultrasonic.h>


const int AIA = 6; //on the right
const int AIB = 7;
const int BIA = 3; //on the left
const int BIB = 5;
byte speed = 255;

int inPin1 = 9;//switch 1 EDGE
int inPin2 = 10;//switch 2 EDGE

int ir = 4; // pin IR is in

int reading1; 
int reading2; 

int reading3; //for ir

unsigned long loopTime = 0;
unsigned long currentTime;

long timer = 3000; //to be used for the line detection <- right now set for 15 sec (in milliseconds)
unsigned long previousTime; //last time the timer was updated

boolean flag;

Ultrasonic ultraCold(A5, A4); //1st number = trigger pin; 2nd num = echo pin
Ultrasonic ultraWarm(A1, A0);


void setup() {
  
 pinMode(AIA, OUTPUT);
 pinMode(AIB, OUTPUT);
 pinMode(BIA, OUTPUT);
 pinMode(BIB, OUTPUT);

 previousTime = 0;

//EDGE DETECTION
 pinMode(inPin1, INPUT);  //intializing the inpin
 digitalWrite(inPin1, HIGH);
 pinMode(inPin2, INPUT);  //intializing the inpin
 digitalWrite(inPin2, HIGH);

 //LINE DETECTION
  pinMode(ir, INPUT);  //intializing the iR
  digitalWrite(ir, HIGH);
  flag = false;
 
}

void loop() {
  reading1 = digitalRead(inPin1);   //reads input from the switch1
  reading2 = digitalRead(inPin2);   //reads input from the switch2

  reading3 = digitalRead(ir);   //reads input from infrared

  currentTime = millis();

  if (reading1 == LOW){//SWITCH1 EDGE 
      backward();
      delay(500);
      left();
      delay(900);
  
    }else if (reading2 == LOW){//SWITCH2 EDGE
      backward();
      delay(500);
      right();
      delay(550);

    }else if((ultraCold.distanceRead(CM) < 20 && ultraCold.distanceRead(CM) > 1) && (ultraWarm.distanceRead(CM) < 20 && ultraWarm.distanceRead(CM) > 1) ){
      //they are both pushed
      left();
    }else if(ultraWarm.distanceRead(CM) < 20 && ultraWarm.distanceRead(CM) > 1){
      //motor A
      right();
   }else if(ultraCold.distanceRead(CM) < 20 && ultraCold.distanceRead(CM) > 1){
      //motor B
      left();
   }else if(reading3 == HIGH){
      left();
      previousTime = currentTime + 5000; //*******************************MAY NEED TO CHANGE HOW LONG TO FOLLOW LINE
      flag = true;
   }else if ( previousTime > currentTime && reading3 == LOW && flag == true) {
    forwardTurnLefter();
   }
   else if ( previousTime <= currentTime && flag == true ){
    flag = false; 
   }
   else {
      previousTime = currentTime;
      forward();
   }
   
}

void forwardTurnLefter()
{
  //left();
  
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed-70);
  analogWrite(BIB,0);
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

void right()///WERK
{
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, 0);
 analogWrite(BIB, speed);
 
}

void left()
{
 analogWrite(AIA, 0);
 analogWrite(AIB, speed);
 analogWrite(BIA, speed);
 analogWrite(BIB, 0);
}
