#include "volume2.h"
Volume v;

void setup() {
  Serial.begin(9600);
}

void loop() {

  for (int vol=0; vol<100; vol++) {
    v.tone(440, SINE, vol);
    
    Serial.print(vol);
    Serial.println();

    delay(10000);
  }
}
