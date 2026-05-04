#pragma once
#include <Arduino_LED_Matrix.h>

class TinyMatrixEngine {
private:
    ArduinoLEDMatrix __matrix;
    const uint32_t __st[3]   = {0xe0, 0x880ec02,0x80e80000};
    uint32_t __N [10][3] =  {
    { 0x0, 0xe00a00a0, 0xa00e000 }, // 0
	{ 0x0, 0x400c0040, 0x400e000 }, // 1
	{ 0x0, 0xc0020040, 0x800e000 }, // 2
	{ 0x0, 0xe0020060, 0x200e000 }, // 3
	{ 0x0, 0xa00a00e0, 0x2002000 }, // 4
	{ 0x0, 0xe00800e0, 0x200e000 }, // 5
	{ 0x0, 0xe00800e0, 0xa00e000 }, // 6
	{ 0x0, 0xe0020020, 0x2002000 }, // 7
	{ 0x0, 0xe00a00e0, 0xa00e000 }, // 8
	{ 0x0, 0xe00a00e0, 0x200e000 }  // 9
};



public:

    TinyMatrixEngine();

    void begin();
    void clearFrame();
    void setState(int index);
};