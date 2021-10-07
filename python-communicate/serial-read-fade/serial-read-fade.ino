int LED_PIN = 9; // PWM pin of led(s)
int brightness = 0; // Current brightness of led [0-maxBrightness]
int maxBrightness= 255; // between [0-255]
bool fadingOn = true;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

  // User serial command to trigger fade cycle
  if(Serial.read() == 's') {
    fadingOn = true;
  }

  // Turn around at maxBrightness and at 0
  if (brightness >= maxBrightness) {
    fadingOn = false;
  }
  
  // Change brightness
  if (fadingOn) {
    brightness ++;
  } else if (brightness > 0) {
    brightness --;
  }

  // Push value to pin, and delay for next loop
  analogWrite(LED_PIN, brightness);
  delay(10);
}
