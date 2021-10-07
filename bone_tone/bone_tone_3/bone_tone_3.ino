// TODO DOC PROJECT
#include "volume2.h"
Volume v;

int wire_pin = A0; // Nicron wire going into here, other end is ground
int pick_pin = 13; // Pin of the 'gitaur pick' switch
int wire_val = 5; // Raw value of wire
int smooth_val = 0; // Smoothed value from wire
int out_pin = 3; // PWM digital pin for the sound output

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

  wire_val = analogRead(wire_pin);

  // Decay the strum volume over time
  if (strum_ratio > 0) {
    strum_ratio -= decay;
  } else if (strum_ratio < 0) {
    strum_ratio = 0;
  }

  float vol_level = strum_ratio * 100;
  
  int sample_index = tick_count % SAMPLE_SIZE;

  total -= samples[sample_index];
  samples[sample_index] = wire_val;
  total += samples[sample_index];

  smooth_val = total / SAMPLE_SIZE;
  
  int freq = map(smooth_val, 300, 650, 10, 1000);
  freq = 1000 - freq;
  
  Serial.print(vol_level);
  Serial.print("\t");
  Serial.print(freq);
  Serial.println();

  freq = constrain(freq, 0, 1000);

  if (smooth_val > 0) {
    v.tone(freq, SQUARE, vol_level);
  } else {
    v.noTone();
  }
  delay(100);
  tick_count += 1;
}
