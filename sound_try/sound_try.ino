#include <Adafruit_NeoPixel.h>


#define PIN_LED     15
#define PIN_BUZZER  13
#define PIN_LT_EN   16

// create pixel object, 1 pixel connected at PIN_LED
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  
  Serial.begin(9600);

  pixel.begin();  // initialize neopixel
  pixel.show();

  pinMode(PIN_LT_EN, OUTPUT);
  digitalWrite(PIN_LT_EN, HIGH);  // enable light sensor

}

void loop() {
  int v = analogRead(A0);

  // Print value
  Serial.print("Light value: ");
  Serial.println(v);

  // Set show value as red light
  pixel.setPixelColor(0, v/4, 0, 0);
  pixel.show();

  // Play value as sound
  //analogWrite(PIN_BUZZER, v+100);
  delay(100);
}
