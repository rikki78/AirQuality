
#define DEBUG
//#define MY_DEBUG

#include "MH-Z14.h"
#include "timeout.h"

// Enable repeater functionality for this node
#define MY_REPEATER_FEATURE

#define MY_RADIO_NRF24
#define MY_BAUD_RATE  9600 // Sets the serial baud rate for console and serial gateway
#define SV "0.2"
#define MY_NODE_ID 20 // Sets a static id for a node
#define SN "Air Quality Sensor"

#include <EEPROM.h>
#include <readVcc.h>
#include <MySensors.h>

#define CHILD_ID_AQ 0
#define CHILD_ID_TEMP 1

MyMessage msgAirQuality(CHILD_ID_AQ, V_LEVEL);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);

CO2Sensor AQSensor;
uint32_t  sensorTimer;
uint16_t  CO2Level;

void before()  
{ 
    // This will execute before MySensors starts up
}

void setup()  
{ 
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Arduino init");
  #endif
  AQSensor.begin();
  sensorTimer = millis();
}

void presentation()  
{ 
  // Send the Sketch Version Information to the Gateway
  sendSketchInfo(SN, SV);
  // Register all sensors to node (they will be created as child devices)
  
  present(CHILD_ID_AQ, S_AIR_QUALITY);
  present(CHILD_ID_TEMP, S_TEMP);
}

void loop()
{  
  if (secTimeout(sensorTimer, 10))
  {
    CO2Level = AQSensor.readAndWait();
    sensorTimer = millis();
    Serial.print("Read ");
    Serial.println(CO2Level);
    if (CO2Level)
      send(msgAirQuality.set(CO2Level));
  }
}

