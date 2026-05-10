#include <Arduino.h>
#include "layout.h"
#include "secrets.h"
#include "TinyMatrixEngine.h"
#include "DHTSensor.h"
#include "WiFiS3.h"

// DHT Sensor setup
DHTSensor dhtSensor(DHT_DATA_PIN, DHT22, 4000, true); // Pin, Type, Frequency, Verbose

//TinyMatrixEngine setup
TinyMatrixEngine ledMatrix;

// WiFi setup
#define POST_INTERVAL 10000 // Time between POST requests in milliseconds
unsigned long lastPostTime = 0;
WiFiClient client;

// State machine
enum states {
  INIT,
  RUNNING,
  ERROR
};

states state;
const long initRetryMillis = 3000;

void setup() {
    // Initialize components
  state = INIT;
  Serial.begin(9600);

  // Initialize LED Matrix
  ledMatrix.begin();
  ledMatrix.setState(INIT);

  // Initialize DHT Sensor
  dhtSensor.begin();
}

void loop() {
  static unsigned long lastClock = -initRetryMillis; // Force immediate connection attempt on startup

  switch (state)
  {
  case INIT:
    if (millis() - lastClock < initRetryMillis) {
      break; // Wait for 3 seconds before trying to connect again
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connecting to WiFi...");
      WiFi.begin(WIFI_NETWORK_NAME, WIFI_PASSWORD);
    } else {
      Serial.println("\nConnected to WiFi!");
      state = RUNNING;
      ledMatrix.setState(RUNNING);
    }

    break;
  case RUNNING:
    // Read DHT sensor data
    static float temperature = 0;
    static float humidity = 0;
    temperature = dhtSensor.readTemperature();
    humidity = dhtSensor.readHumidity();
    break;
  case ERROR:
    // Error handling code
    break;

  default:
    break;
  }
}