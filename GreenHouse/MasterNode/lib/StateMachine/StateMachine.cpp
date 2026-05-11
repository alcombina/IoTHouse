#include "StateMachine.h"

void switchState(states& currentState, states newState, TinyMatrixEngine& ledMatrix) {
    currentState = newState;
    ledMatrix.setState(currentState);
}

uint16_t getWifiStatus() {
    return WiFi.status();
}

void connectToWiFi(const char* ssid, const char* password) {
    if (getWifiStatus() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    }
}

void postTempHum(WiFiClient& client, const char* host, const float& temperature, const float& humidity) {
    
}