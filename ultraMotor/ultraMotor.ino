//Drives left if left ultra is sensed 
//drives right if right is sensed
#include <Ultrasonic.h> 

const int AIA = 6; //on the right
const int AIB = 7;
const int BIA = 3; //on the left
const int BIB = 5;
byte speed = 255;

Ultrasonic ultraCold(A5, A4); //1st number = trigger pin; 2nd num = echo pin
Ultrasonic ultraWarm(A1, A0);

void setup() {
  // put your setup code here, to run once:
  //MOTORS
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if(ultraWarm.distanceRead(CM) < 20 && ultraWarm.distanceRead(CM) > 1)
   {
      //motor A
      analogWrite(AIA, speed);
      analogWrite(AIB, 0);
   }
   else if(ultraCold.distanceRead(CM) < 20 && ultraCold.distanceRead(CM) > 1)
   {
      //motor B
      analogWrite(BIA, speed);
      analogWrite(BIB, 0);
   else
   {
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

void left()///WERK
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
