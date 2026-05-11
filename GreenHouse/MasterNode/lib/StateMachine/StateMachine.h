#pragma once
#include "WiFiS3.h"
#include "TinyMatrixEngine.h"
#include <string>

#define INIT_INTERVAL  3000 // Time between WiFi connection attempts in milliseconds
#define POST_INTERVAL 10000 // Time between POST requests in milliseconds

// States definitions
enum states {
  INIT,
  RUNNING,
  ERROR
};

// Function prototypes
void switchState(states& currentState, states newState, TinyMatrixEngine& ledMatrix);
uint16_t getWifiStatus();
void connectToWiFi(const char* ssid, const char* password);
void postTempHum(WiFiClient& client, const char* host, const float& temperature, const float& humidity);