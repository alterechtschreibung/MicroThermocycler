
#include "OneWire.h"
#include "DallasTemperature.h"

// DS18S20 Temperature chip i/o
OneWire ds(12);  // on pin 12

// decode temperature values
DallasTemperature sensors(&ds);

void setup(void)
{
  // start serial port
  Serial.begin(11500);
  sensors.begin();
}

void loop(void)
{
  sensors.requestTemperatures(); // Temp abfragen

  Serial.print(sensors.getTempCByIndex(0) );
  Serial.print(" Grad Celsius\n");
}

