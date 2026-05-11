#include <Arduino.h>
#include "DHTSensor.h"
#include "layout.h"
#include "secrets.h"
#include "StateMachine.h"

// DHT Sensor setup
DHTSensor dhtSensor(DHT_DATA_PIN, DHT22, 4000, true); // Pin, Type, Frequency, Verbose

//TinyMatrixEngine setup
TinyMatrixEngine ledMatrix;

// WiFi setup
unsigned long lastPostTime = 0;
WiFiClient client;

// Global state variable
states globalState = INIT;

void setup() {
  // Initialize components
  Serial.begin(9600);

  // Initialize LED Matrix
  ledMatrix.begin();

  // Initialize DHT Sensor
  dhtSensor.begin();

  switchState(globalState, INIT, ledMatrix);
  delay(3000); 
}

void loop() {
  static unsigned long msecLst = -INIT_INTERVAL; // Force immediate connection attempt on startup

  switch (globalState)
  {
  case INIT:
    if (millis() - msecLst > INIT_INTERVAL) {
      msecLst = millis();
      if (getWifiStatus() != WL_CONNECTED) {
        connectToWiFi(WIFI_NETWORK_NAME, WIFI_PASSWORD);
      } else {
        Serial.println("\nConnected to WiFi!\n");
        switchState(globalState, RUNNING, ledMatrix);
      }
    }
    break;
  case RUNNING:
    // Read DHT sensor data
    static float temperature = 0;
    static float humidity = 0;
    temperature = dhtSensor.readTemperature();
    humidity = dhtSensor.readHumidity();

    if (millis() - msecLst > POST_INTERVAL) {
      msecLst = millis();
      postTempHum(client, WEB_ADDRESS, temperature, humidity);
    }
    break;
  case ERROR:
    // Error handling code
    break;

  default:
    break;
  }
}