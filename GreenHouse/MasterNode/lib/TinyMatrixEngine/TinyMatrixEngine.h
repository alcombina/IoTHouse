#pragma once

#include <Arduino_LED_Matrix.h>

class TinyMatrixEngine {
private:
    ArduinoLEDMatrix __matrix;
    uint32_t __frame[3] = {0x80080080,0x08008008,0x00800800}; 

public:
    TinyMatrixEngine();

    void begin();
    void show();
    void shiftFrameRight();
    void getFrameBitmap(bool);
};