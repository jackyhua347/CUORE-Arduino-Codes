// Pressure/Temp/Humidity leader
//Make sure you change the int DAQpin to your DAQpin on the Arduino
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <SparkFunBME280.h>

//   Network values
const char WiFiSSID[] = "yale wireless";
const char SC_host[] = "cuttlefish.physics.yale.edu";
const int SC_port = 5556;

//   This is the name of the table in the database where your data will be stored
char DB_entry_string_temp[] = "CUORE_1_T";
char DB_entry_string_hum[] = "CUORE_1_H";
char DB_entry_string_press[] = "CUORE_1_P";

//  These keep track of how often the DB data is written
const unsigned long postRate = 10000; // 10 seconds
unsigned long lastPost = 0;

//  global variables to store the sensor values and frequency
float curr_temp;
float curr_press;
float curr_hum;

//Defines the DAQpin and the Input of the delay
int Input;
int DAQpin = 5;

// Initialize the libraries
BME280 pthSensor;

// setup and loop
void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DAQpin, OUTPUT);
  Wire.begin();

  curr_temp = 0;
  curr_press = 0;
  curr_hum = 0;
  UserInput();
  initPTH();
  connectWiFi();
  readPTH();
}

void loop()
{
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

  postToDB(DB_entry_string_temp, curr_temp);
  postToDB(DB_entry_string_hum, curr_hum);
  postToDB(DB_entry_string_press, curr_press);
  readPTH();

  digitalWrite(DAQpin, HIGH);

  Wire.beginTransmission(8); //Make sure this ID matches the one written in Wire.begin() on the follower
  Wire.write(1);
  Wire.endTransmission();
//Sample of how to add more followers on the lead
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

/// default setting we found that work pretty well
void initPTH()
{
  pthSensor.settings.commInterface = I2C_MODE;
  pthSensor.settings.I2CAddress = 0x77;
  pthSensor.settings.runMode = 2;
  pthSensor.settings.tStandby = 0;

  pthSensor.settings.filter = 0;
  pthSensor.settings.tempOverSample = 1;
  pthSensor.settings.pressOverSample = 1;
  pthSensor.settings.humidOverSample = 1;

  delay(100);
  pthSensor.begin(); // Initializes the I2C Interface
  delay(100);
}

// 1 function that will read out the temperature, pressure and humidity, and put it in the global variables
void readPTH()
{
  curr_temp = pthSensor.readFloatHumidity();
  curr_press = pthSensor.readFloatPressure() / 100.0;
  curr_hum = pthSensor.readTempC();
}

//
int postToDB(char *sensor_name, float value)
{
  // send the given value to the slow control database via the 'Listen_Daemon'

  digitalWrite(LED_BUILTIN, HIGH); // turn LED on, to indicate data transfer
  WiFiClient client;
  if (!client.connect(SC_host, SC_port))
  {
    return 0;
  }
  client.print("Write ");
  client.print(sensor_name);
  client.print(" = ");
  client.println(value);

  while (client.available())
    String line = client.readStringUntil('\r');

  //   Before we return, turn the LED off.
  digitalWrite(LED_BUILTIN, LOW);

  return 1; // Return success
}

/////
void connectWiFi()
{
  byte ledStatus = LOW;
  WiFi.mode(WIFI_STA);

  WiFi.begin(WiFiSSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    // Blink the LED
    digitalWrite(LED_BUILTIN, ledStatus); // Write LED high/low
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;
    delay(100);
  }
}

void UserInput()
{
  Serial.println("Command: ");
  while (!Serial.available())
  {
    // Nothing Happens
  }
  Input = Serial.parseInt();
  Serial.print("You want command: ");
  Serial.println(Input);
}