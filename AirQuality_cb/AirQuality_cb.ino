
#define DEBUG
#define MY_DEBUG
 
#include <MH-Z14.h>
#include <timeout.h>

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
#define CHILD_ID_ERR  2

MyMessage msgAirQuality(CHILD_ID_AQ, V_LEVEL);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);
MyMessage msgErr(CHILD_ID_ERR, V_LEVEL);

CO2Sensor AQSensor;
uint32_t  sensorTimer;
uint8_t ledBlink = 0;

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
  AQSensor.setCallback(AQSensorRead);
  sensorTimer = millis();
  AQSensor.readRequest();
}


void presentation()  
{ 
  // Send the Sketch Version Information to the Gateway
  sendSketchInfo(SN, SV);
  // Register all sensors to node (they will be created as child devices)
  
  present(CHILD_ID_AQ, S_AIR_QUALITY);
  present(CHILD_ID_TEMP, S_TEMP);
  
  present(CHILD_ID_ERR, S_DUST);
}

void receive(const MyMessage &message) 
{
}
  

uint8_t AQSensorRead(uint16_t CO2Level, uint8_t temperature, uint8_t error)
{
  Serial.print(millis()/1000, DEC);
  if (!error)
  { 
    Serial.print(": Level read ");
    Serial.println(CO2Level);
    send(msgAirQuality.set(CO2Level));
    send(msgTemp.set(temperature));
    
  }
  else 
  {
    Serial.print(": Error read ");
    Serial.println(error, HEX);
    
  }
  send(msgErr.set(error));
  digitalWrite(13, ledBlink);
  ledBlink ^= 1;
}


void loop()      

{  
  AQSensor.process();
  
  if (secTimeout(sensorTimer, 30))
  {
    AQSensor.readRequest();
    sensorTimer = millis();
    // Serial.println("Read request");
  }
}

