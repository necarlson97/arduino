#include <IRremote.h>

int fade=0;


void setup() {
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void fadeLed(int ledPin, int i){
  while(fade<200){
    analogWrite(ledPin, fade);
    delay(30);
    fade+=i;
  }
  while(fade>0){
    analogWrite(ledPin, fade);
    delay(30);
    fade-=i;
  }
}

void loop() {
  int toFade = 11;
  fadeLed(toFade, 20);
  
}
