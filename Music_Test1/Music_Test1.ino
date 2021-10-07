#include <Adafruit_NeoPixel.h>
#include "pitches.h"

#define PIN_BUTTON   0
#define PIN_BUZZER  13
#define PIN_LED     15
#define PIN_LT_EN   16  // light sensor enable

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

// play note at given frequency (Hz)
// if frequency is 0, turn off buzzer
void play_note(int freq) {
  if(freq>0) {
    // send square wave at freq Hz with 50% duty cycle
    analogWrite(PIN_BUZZER, 512);
    analogWriteFreq(freq);
  } else {
    analogWrite(PIN_BUZZER, 0);
  }
}

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED,    OUTPUT);
  pinMode(PIN_LT_EN,  OUTPUT);

  digitalWrite(PIN_BUZZER, 0);
  digitalWrite(PIN_LT_EN,  1);

  pixel.begin();
  pixel.setBrightness(100);
}

void loop() {
  // put your main code here, to run repeatedly:

  int i = random(7);
  int n = i*110;
  
  int j = pow(2,random(4));
  int d = 1000/j;

  pixel.setPixelColor(0, i*35, j*16, random(256) );
 
  pixel.show();
  play_note(n);
  delay(d);
  

}
