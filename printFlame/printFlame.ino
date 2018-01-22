//This code prints the values read by the flame sensor to the screenand turns on the LED when 

int sensorF = A2; //flame sensor

int reading;

void setup() {
  pinMode(sensorF, INPUT);
  digitalWrite(sensorF, INPUT_PULLUP);  
  Serial.begin(9600);
  reading = 0;
}

void loop() 
{
  reading = analogRead(sensorF);
  Serial.print("reading from sensor: ");
  Serial.println(reading, DEC);
}
