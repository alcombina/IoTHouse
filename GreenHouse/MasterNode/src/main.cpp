#include <Arduino.h>
#include "TinyMatrixEngine.h"
#include "DHTSensor.h"
#include "layout.h"

// DHT Sensor setup
DHTSensor dhtSensor(DHT_DATA_PIN, DHT22, 2000, true);

TinyMatrixEngine ledMatrix;
int num = 0;

void setup() {
  Serial.begin(9600);

  ledMatrix.begin();
  ledMatrix.setState(0);

  dhtSensor.begin();
}

void loop() {
  int newNum = (millis() / 1000) % 10; // Display numbers from 0 to 9 in a loop every second
  if (newNum != num) {
    num = newNum;
    ledMatrix.setState(num);
    // Serial.print("Current number: ");
    // Serial.println(newNum);
  }

  // Read DHT sensor data
  static float temperature = 0;
  static float humidity = 0;
  temperature = dhtSensor.readTemperature();
  humidity = dhtSensor.readHumidity();
}