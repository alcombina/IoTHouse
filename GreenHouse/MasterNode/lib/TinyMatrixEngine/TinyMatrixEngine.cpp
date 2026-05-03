#include "TinyMatrixEngine.h"

// =========================
// Constructor
// =========================
TinyMatrixEngine::TinyMatrixEngine()
: __matrix() {}

void TinyMatrixEngine::begin() {
    __matrix.begin();
    __matrix.loadFrame(__frame);
}

void TinyMatrixEngine::show() {
    __matrix.loadFrame(__frame);
}

void TinyMatrixEngine::shiftFrameRight() {
    uint8_t pixels[8][12] = {0};

    // unpack
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 12; x++) {
            int bit = y * 12 + x;
            if (__frame[bit / 32] & (1UL << (bit % 32))) {
                pixels[y][x] = 1;
            }
        }
    }

    // shift right by 1 pixel
    uint8_t shifted[8][12] = {0};

    for (int y = 0; y < 8; y++) {
        for (int x = 1; x < 12; x++) {
            shifted[y][x - 1] = pixels[y][x];
        }
    }

    // repack
    uint32_t new_frame[3] = {0};

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 12; x++) {
            if (shifted[y][x]) {
                int bit = y * 12 + x;
                new_frame[bit / 32] |= (1UL << (bit % 32));
            }
        }
    }

    // update the frame
    __frame[0] = new_frame[0];
    __frame[1] = new_frame[1];
    __frame[2] = new_frame[2];
}

void TinyMatrixEngine::getFrameBitmap(bool print) {

    uint8_t bitmap[8][12] = {0};
    for (int f = 0; f < 3; f++) {
        uint32_t frame = __frame[f];

        for (int bit = 0; bit < 32; bit++) {
            int index = f * 32 + bit;   // 0..95

            int row = index / 12;
            int col = index % 12;

            bitmap[row][col] = (frame >> (31 - bit)) & 1;
        }
    }

    // debug print 
    if (print) {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 12; col++) {
                Serial.print(bitmap[row][col] ? " X " : " . ");
            }
            Serial.println();
        }
    }
}