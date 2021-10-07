#include <IRremote.h>

void setup() {
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  int irValue = digitalRead(A1);
  Serial.println(irValue);

}
