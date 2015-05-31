#include <OneWire.h>
#include <DallasTemperature.h>

#define PIN_LED 13
#define PIN_TEMP_DATA 12
#define PIN_FET_IN1 4
#define PIN_FET_IN2 5
#define PIN_FET_IN3 6
#define PIN_FET_IN4 7
#define PIN_FET_EN_A 8
#define PIN_FET_EN_B 9

// DS18S20 Temperature chip i/o
OneWire ds(PIN_TEMP_DATA);

// decode temperature values
DallasTemperature sensors(&ds);

void disable();

void setup(void)
{
    // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  delay(100);
  digitalWrite(PIN_LED, HIGH);
  
  pinMode(PIN_TEMP_DATA, INPUT);
  
  pinMode(PIN_FET_IN1, OUTPUT);
  pinMode(PIN_FET_IN2, OUTPUT);
  pinMode(PIN_FET_IN3, OUTPUT);
  pinMode(PIN_FET_IN4, OUTPUT);
  disable();

  // enable by default
  pinMode(PIN_FET_EN_A, OUTPUT);
  pinMode(PIN_FET_EN_B, OUTPUT);
  digitalWrite(PIN_FET_EN_A, HIGH);
  digitalWrite(PIN_FET_EN_B, HIGH);
  
  sensors.begin();
  
  // 1wire
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
}

float getTemp()
{
  // read temperature
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  // and output to serial port
  Serial.print( temp );
  Serial.print(" Grad Celsius\n");
  
  return temp;
}

void heat()
{
    analogWrite(PIN_FET_IN1, 128); // heating
    analogWrite(PIN_FET_IN4, 128); // heating
}

void cool()
{
    analogWrite(PIN_FET_IN2, 128); // cooling
    analogWrite(PIN_FET_IN3, 128); // cooling
}

void disable()
{
  digitalWrite(PIN_FET_IN1, LOW);
  digitalWrite(PIN_FET_IN2, LOW);
  digitalWrite(PIN_FET_IN3, LOW);
  digitalWrite(PIN_FET_IN4, LOW);
}

void loop(void)
{
  // phase 1: melting, 95 degrees, 2min
  // phase 2: primer annealing, 58-63 degrees, 2min
  // phase 3: extension 72 degrees, 2min
  // repeat

  digitalWrite(PIN_LED, HIGH);

  for (int i=0; i<4; i++)
  {
  analogWrite(PIN_FET_IN1, 100); // heating
  analogWrite(PIN_FET_IN4, 100); // heating
    delay(3000);
    disable();
    delay(500);
    getTemp();    
  }
  
  digitalWrite(PIN_LED, LOW);
  disable();
  delay(2000);
}
