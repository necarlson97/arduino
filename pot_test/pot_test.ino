// Audio out pin (pwm)
int outPin = 11;

// length of a cycle (min, max, resolution)
long maxlen = 50000L;
long minlen = maxlen / 10000;
long lenres = 10;
// length of a thump (min, max, resolution)
long minthump = maxlen;
long maxthump = maxlen*10;
long thumpres = lenres*1000;

void setup() {
//  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
}

void loop() {
  // microsecs since start
  long t = micros();
  
  // values coming from the pots
  long val1 = analogRead(A0);
  long val2 = analogRead(A2);

//  Serial.print(val1);
//  Serial.print('\t');
//  Serial.println(val2);

  long thump = map(val2, 0, 1023, maxlen, maxlen*10);
  thump = (thump / thumpres) * thumpres;
  long cycle = (t % thump);

  // length of cycle (microseconds)
  long len = logmap(val1, minlen, maxlen);
  len = (len / lenres) * lenres;
  // how much of cycle is high
  long high = map(cycle, minlen, maxlen, minlen, len);

  slowPlay(high, len-high);
}

// Play a single square wave __---__
// high - micros up high
// low - micros down low
void slowPlay(long high, long low) {
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

