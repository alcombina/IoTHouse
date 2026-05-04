#include <Arduino.h>
#include "TinyMatrixEngine.h"


TinyMatrixEngine ledMatrix;
int num = 0;

void setup() {
  Serial.begin(9600);
  ledMatrix.begin();
  ledMatrix.setState(0);
}

void loop() {
  int newNum = (millis() / 1000) % 10; // Display numbers from 0 to 9 in a loop every second
  if (newNum != num) {
    num = newNum;
    ledMatrix.setState(num);
    Serial.print("Current number: ");
    Serial.println(newNum);
  }
}