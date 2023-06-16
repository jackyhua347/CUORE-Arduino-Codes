//Test Code to check if Arduinos are working
#include <Wire.h>

int Input;
int LEDpin = 13; //Change this to your pin number
 
void setup() {
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  InputFrequency();
}

void loop() 
{
  if (Serial.available()) //Type in a number in the Serial Monitor when you want to change the frequency! This is measured in milliseconds of delay, so 2Hz = 500 millisecond delay, you would type in 500 in the Serial Monitor
  {
    int newInput = Serial.parseInt();
    if (newInput != 0)
    {
      Input = newInput;
      Serial.print("The new frequency is: ");
      Serial.println(Input);
    }
  }
    
      digitalWrite(LEDpin, HIGH);
      delay(Input);
      digitalWrite(LEDpin, LOW);
      delay(Input);
    
}

void InputFrequency() 
{
  Serial.println("Desired Frequency: (Keep this number in the hundreds for ms delay) ");
  while (!Serial.available()) 
  {
    // Waits until user provides input
  }
  Input = Serial.parseInt();
  Serial.print("You want: ");
  Serial.println(Input);
}