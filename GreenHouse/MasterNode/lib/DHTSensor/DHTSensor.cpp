#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type, unsigned long frequency, bool verbose) : __dht(pin, type), __dhtFrequency(frequency), __verbose(verbose) {
    __lastReadTimeTemp = -__dhtFrequency; // Force immediate reading on first call
    __lastReadTimeHum = -__dhtFrequency; // Force immediate reading on first call
    readTemperature(); // Initialize temperature reading
    readHumidity();    // Initialize humidity reading
}

void DHTSensor::setFrequency(unsigned long frequency) {
    this->__dhtFrequency = frequency;
}
void DHTSensor::setVerbose(bool verbose) {
    this->__verbose = verbose;
}

void DHTSensor::begin() {
    __dht.begin();
}

float DHTSensor::readTemperature() {
    if (millis() - __lastReadTimeTemp > __dhtFrequency) {
        __lastReadTimeTemp = millis();
        __lastReadValTemp = __dht.readTemperature();
        if (__verbose) {
            if (isnan(__lastReadValTemp)) {
                Serial.println("Failed to read temperature from DHT sensor!");
            } else {
                Serial.print("Temperature: ");
                Serial.print(__lastReadValTemp);
                Serial.println(" C");
            }
        }
    }
    return __lastReadValTemp;
}

float DHTSensor::readHumidity() {
    if (millis() - __lastReadTimeHum > __dhtFrequency) {
        __lastReadTimeHum = millis();
        __lastReadValHum = __dht.readHumidity();
        if (__verbose) {
            if (isnan(__lastReadValHum)) {
                Serial.println("Failed to read humidity from DHT sensor!");
            } else {
                Serial.print("Humidity:    ");
                Serial.print(__lastReadValHum);
                Serial.println(" %");
            }
        }
    }
    return __lastReadValHum;
}

