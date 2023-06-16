// LeaderCode
#include <Wire.h>

int DAQpin = 13; //Put in YOUR DAQpin
int Input;
void setup() 
{
  Wire.begin(); //Empty parenthesis sets up the leader
  Serial.begin(9600);
  pinMode(DAQpin, OUTPUT);
  UserInput();
}

void loop() //You can type in the Serial Monitor a new delay for when you want the lights to blink. 
{//This delay is measured in milliseconds. If you want the light to turn on for half a second and then turn off for half a second (Frequency of 2 Hz), you would type 500 in the Serial Monitor 
if (Serial.available())
{
  int newInput = Serial.parseInt();
  if (newInput != 0)
    {
      Input = newInput;
      Serial.print("The new frequency is: ");
      Serial.println(Input);
    }
}

digitalWrite(DAQpin, HIGH);

Wire.beginTransmission(8); //The number in Wire.beginTramission is the ID of the follower arduino. Make sure the arduino you want to blink has Wire.begin(8)!! 
Wire.write(1);
Wire.endTransmission();

//Wire.beginTransmission(9); //You can uncomment if you need multiple lights to blink - this is a demonstration of how to add additional lights. Note that this follower arduino ID is 9
//Wire.write(1);
//Wire.endTransmission();

delay(Input);

digitalWrite(DAQpin, LOW);

Wire.beginTransmission(8);
Wire.write(0);
Wire.endTransmission();

//Wire.beginTransmission(9);
//Wire.write(0);
//Wire.endTransmission();

delay(Input);
  }
}
//This command defines the initial input. You have to input some "delay" before the lights start blinking
void UserInput()
{
  Serial.println("Command: ");
  while(!Serial.available()) 
  {
    //Waits for the user input before it starts blinking
  }
  Input = Serial.parseInt();
  Serial.print("You want command: ");
  Serial.println(Input);
}