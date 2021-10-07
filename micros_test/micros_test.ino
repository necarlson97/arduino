unsigned long t;
int headphonePin = 11; // headphone pwm
// values coming from the pots
long val1 = 0;
long val2 = 0;

void setup(){
  Serial.begin(9600);
}
void loop(){
  t = micros();

  val1 = analogRead(A0);
  val2 = analogRead(A2);

  Serial.print(val1);
  Serial.print('\t');
  Serial.println(val2);


  if (t % val1 < val2) {
    digitalWrite(headphonePin, HIGH);
  } else {
    digitalWrite(headphonePin, LOW);
  }
  delayMicroseconds(50);
}
