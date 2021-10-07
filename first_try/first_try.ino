#include <Adafruit_NeoPixel.h>


#define PIN_LED     15
#define PIN_BUZZER  13

// create pixel object, 1 pixel connected at PIN_LED
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  // turn off buzzer
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, 0);
  
  // initialize LED
  pixel.begin();
  pixel.setBrightness(48);
  pixel.show();
  // lower brightess (default is 256)
  

}

void loop() {

  // random color values
  int r = random(0,255);
  int g = random(0,255);
  int b = random(0,255);
  // random brightness value
  int i = random(0, 255);
  
  pixel.setPixelColor(0, r, g, b);
  pixel.setBrightness(i);
  pixel.show();
  delay(100);

  
  
  
  
}
