"# AirQuality" 


Date: 22 January 2017

With this library you can read the CO2 level from a MH-Z14 CO2 sensor via a serial UART connection.
The connection for this is using the SoftwareSerial library. By default the pin for RX is 3, for TX is 4. To use
other pins define CO_2_UART_RX and CO_2_UART_TX before including the library (so above #include "MH-Z14.h")

There are two ways to read from the sensor (see examples).
1. By using a callback mechanism
Set a callback using setCallback()
Request a read with readRequest(). 
Make sure the process() is handled in loop()
When the read is done, the callback is called with the values read.

2. By waiting for the read to be ready
In some situations you might want to wait for the read to be ready (e.g. battery powered applications) where you want to return to sleep afterwards.
In that case you can use the readAndWait() function. In worst case situations (when the sensor is not responding) it could take a second before a timeout is 
raised.

Two values are read from the sensor, ie. the CO2 value and the temperature. The temperature is not well documented and I assume that is the internal temperature of the sensor.
The sensor updates its values approximately each 30 seconds, so that would be the minimum read time that should be taken into account in the sketch.