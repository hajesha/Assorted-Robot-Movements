//Blinks for various time depending on how far the object is
#include <Ultrasonic.h> 

Ultrasonic ultraCold(A5, A4); //1st number = trigger pin; 2nd num = echo pin
Ultrasonic ultraWarm(A1, A0);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if(ultraCold.distanceRead(CM) > 20){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(10000);                      // wait for 10 second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(4000);                       // wait for 4 second
   }else if(ultraCold.distanceRead(CM) > 15){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(6000);                       // wait for 6 second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(4000);                       // wait for 4 second
   }else if(ultraCold.distanceRead(CM) > 10){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(4000);                       // wait for 4 second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(4000);                       // wait for 4 second
   } else if(ultraCold.distanceRead(CM) < 10){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for 4 second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);                       // wait for 4 second
   }
}
