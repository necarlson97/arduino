#include <HID-Project.h>
#include <HID-Settings.h>

//#include <HID-Project.h>
#include "HID-Project.h"

void setup() {
 pinMode(A0, INPUT);
 pinMode(A1, INPUT);

 Gamepad.begin();
}

void loop() {
  
  Gamepad.xAxis(analogRead(a0));
  Gamepad.yAxis(analogRead(a1));


  Gamepad.write();
  delay(500);

}
