#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>

/// The band that will be tuned by this sketch is FM.
#define FIX_BAND RADIO_BAND_FMWORLD

#define FIX_STATION 10330

TEA5767 radio;    // Create an instance of Class for Si4703 Chip

uint8_t test1;
byte test2;

int prevStation = 0;

/// Setup a FM only radio configuration
/// with some debugging on the Serial port
void setup() {
  // open the Serial port
  Serial.begin(57600);
  Serial.println("Radio...");
  delay(200);

  // Initialize the Radio 
  radio.init();
  radio.debugEnable();
  
  radio.setBandFrequency(FIX_BAND, FIX_STATION);
  radio.setMono(false);

  radio.debugAudioInfo();
} // setup


void loop() {

  int a0 = analogRead(A0);
  int station = map(a0, 0, 1024, 10000, 20000);
  if(station != prevStation) radio.setBandFrequency(FIX_BAND, station);
  prevStation = station;
  
  
//  for(int s=0; s<20000; s+=10){
//    radio.setBandFrequency(FIX_BAND, s);
//  }

//  for(int s=radio.getMinFrequency(); s<radio.getMaxFrequency(); s+=10){
//    radio.setBandFrequency(FIX_BAND, s);
//  }

  delay(200);
} 

// End.

