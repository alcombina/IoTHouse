# pragma once
# include <DHT.h>

class DHTSensor {
private:
    DHT __dht;
    unsigned long __dhtFrequency;
    unsigned long __lastReadTimeTemp;
    float         __lastReadValTemp;
    unsigned long __lastReadTimeHum;
    float         __lastReadValHum;
    bool          __verbose;
public:
    DHTSensor(uint8_t pin, uint8_t type, unsigned long frequency = 2000, bool verbose = false);
    void setFrequency(unsigned long frequency);
    void setVerbose(bool verbose);
    void begin();
    float readTemperature();
    float readHumidity();

};