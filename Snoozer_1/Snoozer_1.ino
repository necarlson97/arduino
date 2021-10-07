#include <Adafruit_NeoPixel.h>

#define PIN_BUTTON   0
#define PIN_BUZZER  13
#define PIN_LED     15
#define PIN_LT_EN   16  // light sensor enable

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);



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

// return a weighted random breath length (in miliseconds)
int getBreathDur() {
  int dur;
  int i = random(5);
  if(i == 0) dur = 500;
  if(i == 4) dur = 2000;
  else dur = 1500;
  return dur;
}

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

void loop() {
  // put your main code here, to run repeatedly:

  int durIn = getBreathDur(); // duration of breath in
  int durOut = getBreathDur();

  //breathe in
  pixel.setPixelColor(0, 20, 70, 200);
  pixel.show();
  play_note(100);
  delay(durIn);
  // pause 1
  pixel.setPixelColor(0, 0, 0, 0);
  pixel.show();
  play_note(0);
  delay(durIn - 500);
  //breathe out
  pixel.setPixelColor(0, 50, 20, 100);
  pixel.show();
  play_note(50);
  delay(durIn);
  // pause 2
  pixel.setPixelColor(0, 0, 0, 0);
  pixel.show();
  play_note(0);
  delay(durIn - 500);
  

}
