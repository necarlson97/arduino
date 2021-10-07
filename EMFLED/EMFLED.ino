#define sample 300
int IN_PIN = A0;
float emf;
int LED_PIN = 11;
int sampleArray[sample];

unsigned long averaging;

void setup() {
  Serial.begin(9600);
}

void loop() {
                    
  for(int i = 0; i < sample; i++){ 
     sampleArray[i] = analogRead(IN_PIN);
     averaging += sampleArray[i];
  }                         
  
  emf = averaging / sample;
  
  emf = constrain(emf, 0, 100);
  emf = map(emf, 0, 100, 0, 255);
  analogWrite(LED_PIN, emf);    
  Serial.println(emf);  
  averaging = 0;
}
