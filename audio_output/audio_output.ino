void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}

void loop() {

  int fPot = analogRead(A0);
  int dPot = analogRead(A1);

  int freq = map(fPot, 0, 700, 33, 8000);
  int dur = map(dPot, 0, 700, 0, 1000);

  Serial.print("Dur: ");
  Serial.print(dPot);
  Serial.print(" Frequency: ");
  Serial.println(freq);

  tone(6, freq, dur);
  


}
