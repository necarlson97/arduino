int slider_pin = 5;
int slider_val = 0;
int count = 0;
void setup() {
  pinMode(slider_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  slider_val = analogRead(slider_pin);
  Serial.print(slider_val);
  Serial.print("\t");
  int zig = (count % 2 == 0) * 1023;
  Serial.print(zig);

  Serial.println();
  count++;
}
