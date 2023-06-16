// Follower Code
#include <Wire.h>
int LEDpin = 13; //Change the LED pin to YOUR LEDpin
int Input;
void setup()
{
  pinMode(LEDpin, OUTPUT);
  Wire.begin(8); //Make sure this ID value matches the leader in the Wire.beginTransmission!
  Wire.onReceive(receiveEvent);
}
void loop()
{
}
void receiveEvent(int OPTIONAL)
{
  Input = Wire.read();
  if (Input == 1)
  {
    digitalWrite(LEDpin, HIGH);
  }
  else if (Input == 0)
  {
    digitalWrite(LEDpin, LOW);
  }
}