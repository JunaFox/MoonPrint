#include "moon_print.h"

MoonPrint mp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mp.setup();
}

void loop() {
  mp.run();
  
}
