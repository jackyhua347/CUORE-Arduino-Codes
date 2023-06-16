# CUORE-Arduino-Codes
Light, Humidity and Temperature Sensors for CUORE Arduinos

Arduino_Code_LightsOnly - This is to set the Arduinos up so that they blink. They do nothing else but blink. The leader code sends a signal to your oscilloscope or DAQ 

Arduino_Code_Test - This code is to test each individual arduino to make sure it's wired properly and it's working. Upon running this code, you're prompted to input a delay in milliseconds to start the corresponding light to start blinking 

Arduino_PTH - Once you set up the Pressure/Temperature/Humidity SparkFun ESP8266 Thing Arduino and I2C it to 2 Arduino Nanos, this code will control all the Arduinos. The follower Nanos use the same exact follower code as in the Arduino_Code_LightsOnly, so use that one for the followers. 