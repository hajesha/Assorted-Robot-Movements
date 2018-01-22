//This code turn off the the LED light after 3 seconds

unsigned long currentTime;//the time the microcontroller has been on for

long timer = 3000; //right now set for 3 sec (in milliseconds)
unsigned long previousTime; //last time the timer was updated


void setup() {

  //BUILT-IN LIGHT:
  pinMode(LED_BUILTIN, OUTPUT);
  
  //TIMER:
  previousTime = 0;

}

void loop() {
 
  currentTime = millis();//updates currentTime

  if(previousTime == 0)
  {
    previousTime = currentTime; //initilizes the previous time
  }
  else
  {
    if(previousTime <= currentTime-timer)//time ran out
    {
      digitalWrite(LED_BUILTIN, LOW);
    } 
    else if (previousTime > currentTime - timer)//theres still time
    {
      digitalWrite(LED_BUILTIN, HIGH);
    } 
    else//doesn't serve a purpose but kept so both timer cases are explictly said 
    {
      previousTime = 0;
    }
  }

}
