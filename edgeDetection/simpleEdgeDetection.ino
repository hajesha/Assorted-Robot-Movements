//This code with turn backwards and then left if the right switch is triggered 
//backwards and then right if the left switch is triggered
//goes forwards otherwise
const int AIA = 6;//forward motor a
const int AIB = 7;//backward motor a
const int BIA = 3;//forward motor b
const int BIB = 5;//backward motor b
byte speed = 255;

int inPin1 = 9;//microswitch 1
int inPin2 = 10;//microswitch 2

int reading1; 
int reading2; 

void setup() {
  
 pinMode(AIA, OUTPUT);
 pinMode(AIB, OUTPUT);
 pinMode(BIA, OUTPUT);
 pinMode(BIB, OUTPUT);

 pinMode(inPin1, INPUT);  //intializing the inpin
 digitalWrite(inPin1, HIGH);

 pinMode(inPin2, INPUT);  //intializing the inpin
 digitalWrite(inPin2, HIGH);
 
}
void loop() 
{
  
    reading1 = digitalRead(inPin1);   //reads input from the switch1
    reading2 = digitalRead(inPin2);   //reads input from the switch2

    if (reading1 == LOW)//SWITCH1
      right();
    else if (reading2 == LOW)//SWITCH2
      left();
    else 
      forward();


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

void right()
{
 backward();
 delay(500);
  
 analogWrite(AIA, speed);
 analogWrite(AIB, 0);
 analogWrite(BIA, 0);
 analogWrite(BIB, speed);
 
 delay(500);
}

void left()
{
 backward();
 delay(500);
 
 analogWrite(AIA, 0);
 analogWrite(AIB, speed);
 analogWrite(BIA, speed);
 analogWrite(BIB, 0);
 
 delay(800);
}

