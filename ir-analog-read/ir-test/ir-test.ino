int sensor_pin = A0; // pin of the ir sensor
int in_val = 0; // Raw value of sensor
int smooth_val = 0; // Smoothed value from sensor

int tick_count = 0; // Number of cycles so far

// Usef for averaging
const int SAMPLE_SIZE = 10;
int samples[SAMPLE_SIZE];
int total = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  in_val = analogRead(sensor_pin);
  int sample_index = tick_count % SAMPLE_SIZE;

  total -= samples[sample_index];
  samples[sample_index] = in_val;
  total += samples[sample_index];

  smooth_val = total / SAMPLE_SIZE;
  
  Serial.print(in_val);  // Raw value
  Serial.print("\t");

  Serial.print(0);  // Min
  Serial.print("\t");
  Serial.print(1023);  // Max
  Serial.print("\t");
  
  Serial.print(smooth_val);
  Serial.println();

  tick_count += 1;
}
