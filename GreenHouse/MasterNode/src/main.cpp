#include <Arduino.h>
#include "TinyMatrixEngine.h"


TinyMatrixEngine ledMatrix;

void setup() {
  Serial.begin(9600);
  ledMatrix.begin();
  ledMatrix.getFrameBitmap(true);
}

void loop() {
  // Serial.println("Ciao");
  delay(5000);
}