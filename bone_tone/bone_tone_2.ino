
int out_pin = 11; // Digital pin for pwm audio out
int fret_pin = 5; // Alalog pin for 
int pot_pin = 0; // Analog pin for potentiometer

int pot_val = 0; // Analog in from potentiometer
int fret_val = 0; // Analog in from fret ribbon

int dur = 0; // Duration to hold note
int freq = 0; // Frequency of note

// frane counter
int count = 0;
const int smoother_size = 10;
int smoother[smoother_size];
int smooth_total = 0;

void setup() {
  pinMode(fret_pin, INPUT);
  pinMode(pot_pin, INPUT);
  pinMode(out_pin, OUTPUT);
  Serial.begin(4800);
}

void loop() {
  fret_val = analogRead(fret_pin);
  pot_val = analogRead(pot_pin);

  fret_val = 1023-fret_val;
  int rough_freq = map(fret_val, 0, 300, 0, 1000);
  fret_avg(rough_freq);


  Serial.print(fret_val);
  Serial.print('\t');
  Serial.print(rough_freq);
  Serial.println();
  
  dur = 0;

  if (freq > 100) {
    tone(out_pin, freq, dur);
  } else {
    noTone(out_pin);
  }
  delay(dur);
  count += 1;
}

int fret_avg(int rough) {
  int read_index = count % smoother_size;
  smooth_total -= smoother[read_index];
  smoother[read_index] = rough;
  smooth_total += smoother[read_index];
  freq = smooth_total / smoother_size;
}

long logmap(long in, long in_upper, long lower, long upper) {
  // Bounds an analog input (0-in_upper) logarythmically
  long reverse = log(in+lower) / log(in_upper)*upper;
  long out = (upper - reverse);

  if (out < lower) return lower;
  else if (out > upper) return upper;
  else return out;
}
