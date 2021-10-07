// Audio out pin (pwm)
int outPin = 11;

// length of a cycle (min, max, resolution)
long maxlen = 25000L;
long minlen = maxlen / 20000;

long count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
}

void loop() {
//  // microsecs since start
//  long t = micros();
//  
//  // values coming from the pots
//  long val1 = analogRead(A0);
//  long val2 = analogRead(A2);
//
//  // length of cycle (microseconds)
//  long len = logmap(val1, minlen, maxlen);
//  long linear = map(val1, 0, 1023, minlen, maxlen);
//
////  Serial.print(linear);
////  Serial.print('\t');
////  Serial.println(len);
//  
//  long high = len/2;
//
//  

  long val1 = analogRead(A0);
  long freq = map(val1, 0, 1023, 1000, 10000);
  
  long val2 = analogRead(A2);
  long maxdroop = map(val2, 0, 1023, 0, 10);
  long droop = 1;

  Serial.print(droop);
  Serial.print('\t');
  Serial.println((count % maxdroop));

  if ((count % maxdroop) < droop) {
    freq /= 2;
  }
  
  for (float duty=0; duty<1; duty += 0.1) {
    long high = freq * duty;
    long low = freq - high;
    slowPlay(high, low); 
  }
  count += 1;
}

// Play a single square wave __---__
// high - micros up high
// low - micros down low
void slowPlay(long high, long low) {
//  for (int i=0; i<high; i++) {
//    Serial.println(1);
//  }
//  for (int i=0; i<low; i++) {
//    Serial.println(0); 
//  }
  
  digitalWrite(outPin, HIGH);
  delayMicro(high);
  digitalWrite(outPin, LOW);
  delayMicro(low);
}

// Delay in microseconds
void delayMicro(long in) {
  if (in < 16383) delayMicroseconds((int)in);
  else delay(in / 1000);
}

// Map a analog val (0-1023) within bounds logarythmically
long logmap(long in, long lower, long upper) {
  long reverse = log(in+lower) / log(1023)*upper;
  long out = (upper - reverse);

  if (out < lower) return lower;
  else if (out > upper) return upper;
  else return out;
}

// Map a analog val (0-1023) between 0-1
float floatmap(long in) {
 return (float)(in) / 1023;
}

