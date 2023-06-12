// LeaderCode
#include <Wire.h>

int DAQpin = 13; //Whatever pin you have 
int Input;
void setup() 
{
  Wire.begin(); //Empty parenthesis sets up the leader
  Serial.begin(9600);
  pinMode(DAQpin, OUTPUT);
  UserInput();
}

void loop() 
{
if (Serial.available())
  {
    Input = Serial.parseInt();
    Serial.print("The frequency is: ");
    Serial.println(Input);
  }

else(true); //Wire.begin to Wire.end sends the signal in Wire.write() to each follower. Copy and paste them as many times as you need. 
//I commented out an example of what to do to add another follower arduino. 
  {
digitalWrite(DAQpin, HIGH);

Wire.beginTransmission(8); // Make sure you have the right 
Wire.write(1);
Wire.endTransmission();

//Wire.beginTransmission(9);
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
    //Nothing Happens
  }
  Input = Serial.parseInt();
  Serial.print("You want command: ");
  Serial.println(Input);
}