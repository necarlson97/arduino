#include <Adafruit_NeoPixel.h>
#include <IRremoteESP8266.h>

#define PIN_LED     15
#define PIN_BUZZER  13

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BUZZER, OUTPUT); // Turn off sound
  digitalWrite(PIN_BUZZER, 0);
  pinMode(4, INPUT); // Ir input

  pixel.begin();

}

void loop() {
  int four = digitalRead(4);
  if(four == 0) {
    pixel.setBrightness(10); //How bright is is directly propotional to how fast it is (and both are good bounded 5-100)
    pixel.setPixelColor(0, pixel.Color(255,0,0));
    pixel.show();
  }
  if(four == 1) {
    pixel.setBrightness(50); //How bright is is directly propotional to how fast it is (and both are good bounded 5-100)
    pixel.setPixelColor(0, pixel.Color(0,0,255));
    pixel.show();
  }
  else {
    pixel.setBrightness(four); //How bright is is directly propotional to how fast it is (and both are good bounded 5-100)
    pixel.setPixelColor(0, pixel.Color(four,255,255));
    pixel.show();
  }

}
