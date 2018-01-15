//This is exam version two
//Hajesha, Sam, Harley

#include <Ultrasonic.h>

//Flame Sensor
int flameSensor = A3;

//IR Sensor
int irF = 8;
int irL = 4;

//Ultrasonic
Ultrasonic ultraWarm(A5, A4);
Ultrasonic ultraCold(A1, A0);

//Motor
const int AIA = 6; //right
const int AIB = 7;

const int BIA = 3; //left
const int BIB = 5;

//Speed
byte speed = 255;
int quarterTime = 537;
int halfTime = 1150;
int forwardOffset = 28;
int forwardTimer = 2500;
int rightTurn = 250;
int backwardTimer = 1000;
int nextLaneCount = 500;
int forwardCandle = 750;


//Readings
int readingFlame; //flame 
int readingIRL; //irL
int readingIRF; //irF

//Timer
long timer;
long currentTime;
long turnTimer;
long previousTime;

//Booleans
boolean fireStealth;
boolean lineFound;
boolean backObject;
boolean frontObject;
boolean longWay;


void setup() 
{
  //Timer
  turnTimer = 50;
  timer = 2000;
  previousTime=0;
  backwardTimer = 100;

  //Booleans
  lineFound = false;
  fireStealth = false;
  frontObject=false;
  backObject=false;
  longWay=true;


  //Motor
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  //Flame
  pinMode(flameSensor, INPUT);
  digitalWrite(flameSensor, INPUT_PULLUP);

  //IR
  pinMode(irL, INPUT);
  digitalWrite(irL,HIGH);
  pinMode(irF, INPUT);
  digitalWrite(irF,HIGH);

}

void loop() 
{

  //the rest of the beginning code goes
  awayFromWallLeft(quarterTime);
  searchForLine();
  doReadings();

  while(!longWay)
  {
    while(readingIRF != HIGH)
    //This is to traverse each lane
    {
      doReadings();
      onLine();
      lineBreak();
    }

    //Once the lane is done
    backFromWallLeft(quarterTime); 
    searchForLine();
    if(longWay)
    {
      doReadings();
      onLine();
      nextLaneLeft();

      while(readingIRF != HIGH )
      //This is to traverse each lane
      {
        doReadings();
        onLine();
        lineBreak();
      }

    
      //Once the lane is done
      awayFromWallRight(quarterTime); 
      searchForLine();
      if(longWay)
      {
        doReadings();
        onLine();
        nextLaneRight();
      }
    }
  }

 
}


void nextLaneLeft()
{
  forward();
  delay(nextLaneCount);
  left();
  delay(quarterTime);
  searchForLine();
   
}

void nextLaneRight()
{
  forward();
  delay(nextLaneCount);
  right();
  delay(quarterTime);
  searchForLine();
   
}

void lineBreak()
//This method will figure out what to do with the line breaks
//Ends when the new line is found or the wall is found
{
  while (speed == 255)
  //moves forward until the candle is detected
  {
    doReadings();
    forward();
  }
  while(speed == 200)
  //still moves forward until candle is extinguished
  {
    doReadings();
    forward();
  }

  //turns to avoid the candle
  right();
  delay(rightTurn);
  forward();
  delay(forwardCandle);

  while( readingIRL != HIGH && readingIRF !=HIGH)
  //while the new line is not found
  {
    doReadings();
    forwardTurnLefter();
  }
  
}

void onLine()
//This method will follow the line
//Ends once the end of the line is reached
{
  
  while( readingIRL == HIGH) 
  //forward while on the line
  {
    doReadings();
    forward();  
  }

  if(readingIRL == LOW) 
  //if it gets off the line
  {
    doReadings();
    previousTime = currentTime;
   
    while(readingIRL != HIGH)
    //while it hasn't found its way
    {
      doReadings();
      if (previousTime <= currentTime-turnTimer) 
      //timer ran out
      {
        left();
        delay(turnTimer);
        break; 
      }
      else 
      //still got time
      {
        right();
      }
      
    }
  }
}

void awayFromWallLeft(int duration)
//This method will turn away from the wall and 
//Ends once a line is found
{
  left();
  delay(duration);
  forward();
  delay(forwardTimer);
  
}

void backFromWallLeft(int duration)
//This method will turn away from the wall and 
//Ends once a line is found
{
  left();
  delay(duration);
  backwards();
  delay(forwardTimer);
  
}

void backFromWallRight(int duration)
//This method will turn away from the wall and 
//Ends once a line is found
{
  right();
  delay(duration);
  backwards();
  delay(forwardTimer*2);
  
}

void searchForLine()
// Will look for the newline
//Ends once the line is found
{
  doReadings();
  while(readingIRL != HIGH && readingIRF !=HIGH)
  {
    doReadings();
    forwardTurnLefter();
  }

  if(readingIRF == HIGH)
  {
    longWay=false;
  }
}


void candleSensing()
//Will detect if a candle is nearby 
//Ends when the candle readings have been interpreted 
{ 
  if(readingFlame < 710) 
  //If the fire is closer than a set distance
  {
    stopping();
    delay(100);
    speed = 230;
    fireStealth = true;
  }

  else if ( readingFlame >= 955 && fireStealth) 
  //If you dont sense the flame anymore but you once did 
  {
    fireStealth = false; 
    speed = 255;
  }
  
}

void doReadings()
//Will update all the sensor readings
//Will end once everything is updated
{
  //IR
  readingIRL = digitalRead(irL);
  readingIRF = digitalRead(irF);

  //Ultrasonic
  backObject = (ultraCold.distanceRead(CM) < 5 && ultraCold.distanceRead(CM) > 1);
  frontObject = (ultraWarm.distanceRead(CM) < 5 && ultraWarm.distanceRead(CM) > 1);

  //Flame
  readingFlame = analogRead(flameSensor);
  candleSensing();

  //Time
  currentTime = millis();
    
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
 analogWrite(BIB, speed-forwardOffset);
}
void forward()
{
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, speed-forwardOffset);
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

void rightTurnForward()
{
 analogWrite(AIA, 0);
 analogWrite(AIB, speed-100);
 analogWrite(BIA, speed);
 analogWrite(BIB, 0);
}

void leftTurnForward()
{
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, 0);
 analogWrite(BIB, speed-100);
}

