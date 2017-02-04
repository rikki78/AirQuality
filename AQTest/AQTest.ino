#include "co2sensor.h"
#include "timeout.h"

CO2Sensor AQSensor;
uint32_t  sensorTimer;

void setup()  
{
  Serial.begin(9600);
  AQSensor.set_callback(AQSensorRead);
  sensorTimer = millis();
}

uint8_t AQSensorRead(uint16_t level, uint8_t error)
{
  if (!error)
  {
    Serial.print("Level read ");
    Serial.println(level);
  }
  else 
  {
    Serial.print("Error read ");
    Serial.println(error);
  }
}

void loop()      
{
  AQSensor.process();
  
  if (secTimeout(sensorTimer, 10))
  {
    AQSensor.read();
    sensorTimer = millis();
    Serial.println("Read request");
  }
  
}