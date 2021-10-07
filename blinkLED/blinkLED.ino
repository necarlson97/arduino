#include <Adafruit_NeoPixel.h>

#define PIN_LED     15
#define PIN_BUZZER  13

volatile int delaytime = 200;    // milliseconds

// create pixel object, 1 pixel connected at PIN_LED
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  // turn off buzzer
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, 0);
  
  // initialize LED
  pixel.begin();
  // lower brightess (default is 256)
  pixel.setBrightness(48);
  pixel.show();
  
}

void loop() {

  blink(255, 0, 0);  // blink red
  blink(0, 255, 0);  // blink green
  blink(0, 0, 255);  // blink blue
  
  fade(255, 0, 0);   // fade red
  fade(0, 255, 0);   // fade green
  fade(0, 0, 255);   // fade blue
}

void blink(byte r, byte g, byte b) {
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  // every time you change the color
  // you must call pixel.show() to push it to the LED
  pixel.show();
  delay(delaytime);   // delay specified milliseconds

  pixel.setPixelColor(0, pixel.Color(0, 0, 0)); // turn off (set color to 0)
  pixel.show();
  delay(delaytime);
}

void fade(byte r, byte g, byte b) {
  // smoothly fade color from 0,0,0 to r,g,b
  for(int i=0;i<255;i++) {
    pixel.setPixelColor(0, pixel.Color(r*i/255, g*i/255, b*i/255));
    pixel.show();
    delay(3);
  }
  // fade back to 0,0,0
  for(int i=255;i>=0;i--) {
    pixel.setPixelColor(0, pixel.Color(r*i/255, g*i/255, b*i/255));
    pixel.show();
    delay(3);
  }
}
