// Green and white wires plugged into digital pins 2 and 3
// (red wire into 5v, black wire into ground)
// If you are having issues, try jiggling the wires!
char whtPin = 2;
char grnPin = 3;
void setup() {
  pinMode(whtPin, INPUT);
  pinMode(grnPin, INPUT);
  // To recive data, open your serial monitor
  // and set the baud rate to 9600
  Serial.begin(9600);
  Serial.println("Now listening...");
}

// A temporary array for capturing bits comming in (max 100)
bool bits[100];
// A counter where we are in the bit array
int bitCount = 0;

int silenceCount = 0;
void loop() {

  // Read in the values from the green / white wires
  int white = digitalRead(2);
  int green = digitalRead(3);

  // If we recieved a bit, store it
  if (white != 1 or green != 1) {
    Serial.print(green);
    bits[bitCount] = green;
    bitCount ++;
    silenceCount = 0;
  }
  
  // Whenever the bits have finished comming in,
  // write them out
  silenceCount += 1; 
  if (silenceCount > 30000) {
    // We have not recieved any bits in a while
    // If we have any stored bytes, print them
    if (bitCount > 0) {
      Serial.println();
      Serial.println("Last transmission:");
      for(int i=0; i<bitCount; i++) {
        Serial.print(bits[i]);
      }
      Serial.println();
      bitCount = 0;
    }
  }
}
