#include "volume2.h"
Volume v;
void setup() {

}

void loop() {

  for(int vol = 200; vol<224; vol++){
    v.tone(vol, SQUARE, vol);
    delay(1000);
  }
  
}
