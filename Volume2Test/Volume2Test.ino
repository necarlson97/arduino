#include "volume2.h"
Volume v;

int vPot;
int dPot;
int fPot;

int vol;
int dur;
int freq;
int duty;

void setup() {
  Serial.begin(9600);
  //v.begin();
}

void loop() {

  vPot = analogRead(A0);
  dPot = analogRead(A1);
  fPot = analogRead(A2);

  //vol = map(vPot, 0, 1024, 0, 100);
  vol = 100;
  dur = map(dPot, 0, 1024, 0, 10240);
  freq = vPot;
  duty = map(fPot, 0, 1024, 1, 32);

  byte wave[32];
  for(int i=0; i<32; i++){
    if(i<duty) wave[i]=225;
    else wave[i]=0;
  }
  
  v.setCustomWave(wave);
  v.tone(freq, CUSTOM, vol);
  delay(dur);

//  Serial.print("Vol: ");
//  Serial.print(vol);
//  Serial.print(", Dur: ");
//  Serial.print(dur);
//  Serial.print(", Freq: ");
//  Serial.println(freq);

}
