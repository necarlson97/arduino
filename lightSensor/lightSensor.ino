#include <Adafruit_NeoPixel.h>

#define PIN_LED    15
#define PIN_LT_EN  16 // light sensor enable

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();  // initialize neopixel
  pixel.show();

  pinMode(PIN_LT_EN, OUTPUT);
  digitalWrite(PIN_LT_EN, HIGH);  // enable light sensor

  Serial.begin(115200); // start serial communication
}

void loop() {

  int value = analogRead(A0); // read sensor value, range [0,1023]
  Serial.print("sensor value: ");
  Serial.println(value);      // output value to serial
  
  pixel.setPixelColor(0, pixel.Color(0, 0, (1024-value)/4));
  pixel.show();
  
  delay(200);
}

