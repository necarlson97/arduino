#include <SD.h>             
#define SD_ChipSelectPin 4 

#include <TMRpcm.h>          

TMRpcm tmrpcm; 

// the indexes of the current file that he is on in each file set
// either regular lines, or touched wires lines
int line; 
int wires;

int c; // counter of how where in his cycle we are
void setup(){
  
  pinMode(3, INPUT_PULLUP);
  tmrpcm.speakerPin = 9;

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    //Serial.println("SD fail");  
    return;   // don't do anything more if not
  }

  playFile("pain_is"); // just for testing
  
  bootUp();
}

void playFile(String fileName){
  fileName += ".wav";
  tmrpcm.play(fileName.c_str());
  while(tmrpcm.isPlaying()) delay(100);
}

void bootUp(){
  playFile("boot"); // alice annonces booting up

  // re-set our counters
  c=0;
  line=0;
  wires=0;
}

void loop(){
  
  if(digitalRead(3) == LOW) {
    playFile("wires"+String(wires));
    wires= (wires+1) % 21;
  }
  else if(c % 10 == 0) {  
    Serial.println("\nPlaying Line " + String(line));

    if(line>30) playFile("line"+String(line-30)+"_2");
    else playFile("line"+String(line));
    
    line = line+1;
    
    if(line >=60) sleepMode(); // ran out of lines, enter sleep mode
  }

  c = c+1;
  delay(100);
}

void sleepMode(){
  playFile("down"); // alice announces shutting down
  delay(15 *1000); // and N-82G sleeps for a set ammount of time
  bootUp(); // then restarts
}

