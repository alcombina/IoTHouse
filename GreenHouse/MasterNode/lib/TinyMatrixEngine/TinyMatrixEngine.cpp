#include "TinyMatrixEngine.h"

// =========================
// Constructor
// =========================
TinyMatrixEngine::TinyMatrixEngine()
: __matrix() {}

void TinyMatrixEngine::begin() {
    __matrix.begin();
}


void TinyMatrixEngine::clearFrame() {
    static const uint32_t emptyFrame[3] = {0x0, 0x0, 0x0};
    __matrix.loadFrame(emptyFrame);
}

void TinyMatrixEngine::setState(int index) {
    uint32_t frame[3] = {
        __st[0] | __N[index][0], 
        __st[1] | __N[index][1],
        __st[2] | __N[index][2]
    };
    __matrix.loadFrame(frame);
}
