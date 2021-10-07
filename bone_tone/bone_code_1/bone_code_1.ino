int outPin = 11; // audio out (pwm)

int frets_in = 5; // Log resistive ribbon pin
int pot_in = 0; // Potentiometer pin

// the micros spent high/low for the two square waves
long high1 = 0; 
long low1 = 0; 
long high2 = 0;
long low2 = 0;

// micros sicne start
long t = 0;

long maxlen = 1000L;
long minlen = maxlen / 1000;

void setup() {
  pinMode(outPin, OUTPUT);
//  Serial.begin(9600);
}

void loop() {
  t = micros();
  long val2 = analogRead(frets_in);
  long val1 = analogRead(pot_in);

  loopTone(val1, val2);
  
}

void loopTone(long val1, long val2) {

 
  // length of cycle (micros)
  long len1 = logmap(val1, minlen, maxlen);
  long len2 = logmap(val2, minlen, maxlen);

  // Current position in cycle (warble?)
  long cycle = t % (maxlen - minlen);

  high1 = len1 / 2; // 50% duty (for now)
  high2 = len2 / 2;

  //  high1 = map(cycle, minlen, maxlen, minlen, len);
  
  if (cycle < high1 and cycle < high2) { // Both cycles up, so go 100%
    digitalWrite(outPin, HIGH);
  } else if (cycle < high1 or cycle < high2) { // One cycle up, so go 50%
    if (cycle % 2 == 0) digitalWrite(outPin, HIGH);
  } else { // Go 0%
    digitalWrite(outPin, LOW);
  }
}

//void blockingTone() {
//  digitalWrite(headphonePin, HIGH);
//  delayMicro(high);
//  digitalWrite(headphonePin, LOW);
//  delayMicro(low);
//}

void delayMicro(long in) {
  if (in < 16383) delayMicroseconds((int)in);
  else delay(in / 1000);
}

long logmap(long in, long lower, long upper) {
  // Bounds an analog input (0-1023) logarythmically
  long reverse = log(in+lower) / log(1023)*upper;
  long out = (upper - reverse);

  if (out < lower) return lower;
  else if (out > upper) return upper;
  else return out;
}

float floatmap(long in) {
 // Bounds an analog input (0-1023) between 0-1
 return (float)(in) / 1023;
}
