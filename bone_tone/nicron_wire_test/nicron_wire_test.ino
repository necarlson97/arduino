// TODO DOC PROJECT

int wire_pin = A0; // Nicron wire going into here, other end is ground
int pick_pin = 13; // Pin of the 'gitaur pick' switch
int wire_val = 5; // Raw value of wire
int smooth_val = 0; // Smoothed value from wire

// TODO DOC
bool pick_val = LOW;
float strum_ratio = 0;
float decay = 0.05;

int tick_count = 0; // Number of cycles so far

// Usef for averaging
const int SAMPLE_SIZE = 10;
int samples[SAMPLE_SIZE];
int total = 0;
 
void setup() {
  Serial.begin(9600);
}

void loop() {
  // If there is a 'strum' with the 'pick'
  // TODO DOC
  bool curr_pick_val = digitalRead(pick_pin);
  if (curr_pick_val != pick_val) {
    strum_ratio = 1;
    pick_val = curr_pick_val;
  }

  wire_val = analogRead(wire_pin) * strum_ratio;

  // Decay the strum volume over time
  if (strum_ratio > 0) {
    strum_ratio -= decay;
  } else if (strum_ratio < 0) {
    strum_ratio = 0;
  }
  
  int sample_index = tick_count % SAMPLE_SIZE;

  total -= samples[sample_index];
  samples[sample_index] = wire_val;
  total += samples[sample_index];

  smooth_val = total / SAMPLE_SIZE;
  
//  Serial.print(wire_val);  // Raw wire value
//  Serial.print("\t");

//  Serial.print(0);  // Min
//  Serial.print("\t");
//  Serial.print(1023);  // Max
//  Serial.print("\t");

//  Serial.print(pick_val);
//  Serial.print("\t");
//  Serial.print(curr_pick_val);
//  Serial.print("\t");
//  Serial.print(strum_ratio);
//  Serial.print("\t");
//  Serial.print(smooth_val);
//  Serial.println();

  tick_count += 1;
}
