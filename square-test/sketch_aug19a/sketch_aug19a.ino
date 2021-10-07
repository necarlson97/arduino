int LED_PIN = 9; // PWM pin of led(s)
int brightness = 0; // Current brightness of led [0-maxBrightness]
int maxBrightness= 255; // between [0-255]
bool fadingOn = true;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_PIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  // Turn around at maxBrightness and at 0
  if (brightness >= maxBrightness) {
    fadingOn = false;
  } else if (brightness <= 0) {
    fadingOn = true;
  }
  
  if (brightness == 0) {  // Wait after a blink
//    delay(2000);
  }
  
  // Change brightness
  if (fadingOn) {
    brightness ++;
  } else {
    brightness --;
  }

  // Push value to pin, and delay for next loop
  analogWrite(LED_PIN, brightness);
  delay(10);
}
