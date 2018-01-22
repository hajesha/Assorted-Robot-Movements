//This code will travel through a city with pre determined dimensions
//avoiding buildings
//traveling on the right side of the road ( which is indicated by black tape on the ground)
//extinguish and avoid running into the candles 

//Roads are similiar to real life roads as in they are solid and end at an intersection
//at every intersection there are candles to extinguish 

#include <Ultrasonic.h> 
int counter = 1;

boolean previousState = false; //false is left, true is right
boolean frontLine = false; //if the front sensor senses a line

Ultrasonic ultraWarm(A1, A0);

//LED:
byte flameDetected = 12;

//Motor
const int AIA = 6; //right
const int AIB = 7;

const int BIA = 3; //left
const int BIB = 5;

//IR Sensor
int irF = 8;
int irL = 4;
int irB = 9;

//Speed
//byte speed = 255;
byte speed = 200;
int quarterTime = 650;
int halfTime = 1150;
//int forwardOffset = 28;
int forwardOffset = 2;
int forwardTimer = 2500;
int rightTurn = 250;
int backwardTimer = 1000;
int nextLaneCount = 500;
int forwardCandle = 750;

//Timer
long timer;
long currentTime;
long turnTimer;
long previousTime;

//Readings
int readingFlame; //flame 
int readingIRL; //irL
int readingIRF; //irF
int readingIRB; // irB

//Flame Sensor
int flameSensor = A2;

//Booleans
boolean fireStealth;
boolean lineFound;
boolean backObject;
boolean frontObject;
boolean longWay;
boolean cornerFound;

void setup() {
  // put your setup code here, to run once:
  //MOTORS:
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  //IR
  pinMode(irL, INPUT);
  digitalWrite(irL,HIGH);
  pinMode(irF, INPUT);
  digitalWrite(irF,HIGH);
  pinMode(irB, INPUT);
  digitalWrite(irB,HIGH);

  //Timer
  turnTimer = 50;
  timer = 1750;
  previousTime=0;
  backwardTimer = 100;

  //Flame
  pinMode(flameSensor, INPUT);
  digitalWrite(flameSensor, INPUT_PULLUP);

  //Booleans
  lineFound = false;
  fireStealth = false;
  frontObject=false;
  backObject=false;
  longWay=true;
  cornerFound = false;

  //LED:
  pinMode(flameDetected, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(counter == 1){
    startup();
    lengthwayAlgo();
    upAlgo();
    counter = 3;
  }else{
    stopping();
  }
}

void startup() {
  //Will do the beginning of the algorithm.
  while(readingIRF == LOW){
    doReadings();
    forward();
  }
  backward();
  delay(350);
  
  right();
  delay(600);
  
  findLineNoUltra();
  followLength();
  
  left();
  delay(100); //was 100
  
  followLength();
  
  stopping();
  delay(1000);
}

void lengthwayAlgo(){
  //go through the long rows one by one
  //**************************************************************START OF SETUP
  left();
  delay(10);

  forward();
  delay(100);
  
  //now, needs to go to the end of the box <- keep following lines until the front sensor senses
  followLength();

  //**************************************************************END OF SETUP

  while(!cornerFound){ //***************************************************ALGORITHM
    left();
    delay(50); //this will face the proper direction

    bounceOnLine(); //want to follow only one line
    //if the front IR senses, then at a corner
    doReadings();
    previousTime = currentTime;
    
    if(!frontLine){
      //continue      
      forwardLeft(); //turn left, past the center line
  
      //go through all lines in the row
      followLength();
  
      //need to back up past line, then turn right
      backRight();
      //now, facing the way we want to go
      bounceOnLine();
      //want to stop here if the front is triggered
      if(!frontLine){
        //want to go forward a bit, then turn right
        forward();
        delay(250);
    
        right();
        delay(25);
    
        //now, want to find line & follow till the end
        followLength();
    
        //reached the end, so now want to turn left & go past one line
      }else{
        cornerFound = true;
      }
      
    }else{
      cornerFound = true;
    }
    
  }
  
}

void upAlgo(){ //this will need to be made into a loop eventually
  //will need to add in the stopping conditions
  cornerFound = false; //reset the cornerFound so that it can be used in this algo
  //************************************************* START OF SETUP
  //go back and turn right
  backRight();// ************************************************************************************************************************************************************************************************************************************
  //facing towards the end ; want to go until the end
  followLength();
  //******************************************* END OF SETUP

  //************************************************************ALGORITHM
  while(!cornerFound){
    //back up
    backRight();
    //go until come off one line
    bounceOnLine();
    if(!frontLine){ //run only if the front doen't sense
      forward();
      delay(750);
      //need to turn right
      right();
      delay(quarterTime + 250); //was + 150
      //will be facing the next row to go down
      followLength();
      //want to turn left
      left();
      delay(quarterTime);
      //follow only one line
      bounceOnLine();
      if(!frontLine){ //run only if the front doesn't sense
        //forward a bit, then turn left
        forwardLeft();
        followLength();
      }else{
        cornerFound = true;
      }
      
    }else{
      cornerFound = true;
    }
    
  }
  
  
  
  
}

void forwardLeft(){ //USED IN BOTH THE UP ALGO AND LENGTHWAYS ALGO******************
  //need to go forward past the center line, then turn left
  forward();
  delay(2100); //need to go past the center of the line

  forwardTurnLefter();
  delay(2000);
  
  left();
  delay(950);
}

void backRight(){ //USED IN BOTH THE UP ALGO AND LENGTHWAYS ALGO************* THIS WILL NEED TO BE CHANGED ACCORDING TO FLOOR
  //this is to back up past the center line, then to turn right
  right();
  delay(quarterTime); // bc the findLine goes back & left always
      
  backward();
  delay(1800);
  
  right();
  delay(quarterTime);
}

void followLength(){
  //this will follow all lines in a row/column; until the front sensor senses
  //it will then reset the front boolean

  while(!frontLine){
      bounceOnLine();
    }

    frontLine = false; //reset the front line (bc front line was wanted to be found)
    
}


void bounceOnLine(){
  //will turn right once it is off the line, then go forward with a left bias
  findLineUltra();
  //now we are on the line

  doReadings();
  previousTime = currentTime;

  while((previousTime > currentTime - timer) && !frontLine){//mo bounce
    doReadings();
    if(readingIRL == LOW){
      left();
      delay(35);
      forward();
      delay(25); //was 85
    }else{
      forward();
      delay(40);
      right();
      previousTime = currentTime; //reset the timer
    }
  }

  doReadings();
  previousTime = currentTime;

  
  
  //HERE: WANT TO CHANGE SO THAT IT GOES UNTIL THE BACK IR SENSES
  while(readingIRB == LOW && !frontLine){
    doReadings();
   // resetAfterLine();
   right();
    if(previousTime > currentTime - 200){
      readingIRB = LOW;
    }
  }

  if(!frontLine){
    backward();
    delay(150);
    right();
    delay(310); 
    forward();
    delay(100);
  }
  
  doReadings();
  
}

void findLineNoUltra(){
  frontLine = false;
  doReadings();

  while(readingIRL == LOW && !frontLine){//looking for new line
    forwardTurnLefter();
    doReadings();
    
    candleSensing();
    
    if(readingIRF == HIGH){
      frontLine = true;
      backward();
      delay(500);
      left();
      delay(quarterTime + 100);
    }
  }
}

void findLineUltra(){
  frontLine = false;
  doReadings();

  while(readingIRL == LOW && !frontLine){//looking for new line
    forwardTurnLefter();
    doReadings();

    if (frontObject)
    {
      left();
      delay(254);
    }
    
    candleSensing();
    
    if(readingIRF == HIGH){
      frontLine = true;
      backward();
      delay(500);
      left();
      delay(quarterTime + 100);
    }
  }
}






void candleSensing()
//Will detect if a candle is nearby 
//Ends when the candle readings have been interpreted 
{ 
  if(readingFlame < 750) 
  //If the fire is closer than a set distance
  {
    fireStealth = true;
    digitalWrite(flameDetected, HIGH);
  }

  else if ( readingFlame >= 900 && fireStealth) // was 945
  //If you dont sense the flame anymore but you once did 
  {
    fireStealth = false; 
    digitalWrite(flameDetected, LOW);
    
  }
  
}


void doReadings()
//Will update all the sensor readings
//Will end once everything is updated
{
  //IR
  readingIRL = digitalRead(irL);
  readingIRF = digitalRead(irF);
  readingIRB = digitalRead(irB);

  //Ultrasonic
  //backObject = (ultraCold.distanceRead(CM) < 5 && ultraCold.distanceRead(CM) > 1);
  frontObject = (ultraWarm.distanceRead(CM) < 8 && ultraWarm.distanceRead(CM) > 3);

  //Flame
  readingFlame = analogRead(flameSensor);

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
  //this is modified for the end of the line

 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, speed - 80); //was 80
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
 analogWrite(AIA, speed - 100);
 analogWrite(AIB, 0);
 analogWrite(BIA, speed);
 analogWrite(BIB, 0);
}

void leftTurnForward() 
{
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, speed - 100);
 analogWrite(BIB, 0);
}

void rightBack(){
  analogWrite(AIA, 0);
  analogWrite(AIB, speed - 100);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}


void leftBack(){
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIA, 0);
  analogWrite(BIB, speed - 100);
}

void resetAfterLine(){
 analogWrite(AIA, 0);
 analogWrite(AIB, speed);
 analogWrite(BIA, 0);
 analogWrite(BIB, speed - 100);
}

