

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(8, OUTPUT);

}


void loop() {
  

  int lPot = analogRead(A0);
  
//  int dutyHigh = map(lPot, 0, 700, 0, 1000);
//  int triggerPulseLength = map(rPot, 0, 700, 1, 1000);

//  int dutyTotal = triggerPulseLength;
//  
//  while(dutyHigh > dutyTotal){
//    dutyTotal += triggerPulseLength;
//  }
  
  
//  digitalWrite(8, HIGH);
//  delayMicroseconds(dutyHigh);
// 
//  digitalWrite(8, LOW);
//  delayMicroseconds( triggerPulseLength - dutyHigh);

  Serial.print("L Pot");
  Serial.println(lPot);
//  Serial.print(" Duty Total: ");
//  Serial.print(dutyTotal);
//  Serial.print(" R Pot ");
//  Serial.println(rPot);
//  Serial.print(" Duty low: ");
//  Serial.println(dutyTotal - dutyHigh);
  
 
  
 

  
}

