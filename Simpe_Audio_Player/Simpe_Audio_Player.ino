#include <SD.h>             
#define SD_ChipSelectPin 4 

#include <TMRpcm.h>          


TMRpcm tmrpcm;   
String wavFile = "pain_is.wav";


void setup(){

  tmrpcm.speakerPin = 9; 

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  
}


void loop(){

  if(wavFile != "") {
    tmrpcm.play(wavFile.c_str());
    while(tmrpcm.isPlaying()) {
      digitalWrite(2, HIGH);
      delay(50);
    }
    digitalWrite(2, LOW);
    Serial.println("Played: "+wavFile);
    wavFile = "";
  }
  else {
    wavFile = Serial.readString();
    if(wavFile != "") Serial.println("Input: "+wavFile);
    delay(100);
  }

}
