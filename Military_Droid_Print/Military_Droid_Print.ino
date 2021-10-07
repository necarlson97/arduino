
// the indexes of the current file that he is on in each file set
// either regular lines, or touched wires lines
int line; 
int wires;

int c; // counter of how where in his cycle we are
void setup(){

  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);

  playFile("pain_is"); // just for testing
  
  bootUp();
}

void playFile(String fileName){
  fileName += ".wav";
  Serial.println("Played: "+fileName);
}

void bootUp(){
  playFile("boot"); // alice annonces booting up

  // re-set our counters
  c=0;
  line=0;
  wires=0;
}

void loop(){

  Serial.print("\tc: "+String(c));
  
  if(digitalRead(3) == LOW) {
    Serial.println("\nWires touched");
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
  delay(5 *1000); // and N-82G sleeps for a set ammount of time
  bootUp(); // then restarts
}

