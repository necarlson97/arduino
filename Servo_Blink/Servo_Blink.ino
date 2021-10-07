#include <Servo.h>

Servo s;

int pos = 0;


void setup() {
  // put your setup code here, to run once:
  s.attach(13);
}

void loop() {
  // put your main code here, to run repeatedly:
  s.write(0);
  delay(1000);
  s.write(180);
  delay(1000);
}
