// Green and white wires plugged into digital pins 2 and 3
// (red wire into 5v, black wire into ground)
char whtPin = 2;
char grnPin = 3;
void setup() {
  pinMode(whtPin, INPUT);
  pinMode(grnPin, INPUT);
  // To recive data, open your serial monitor
  // and set the baud rate to 9600
  Serial.begin(9600);
}

// A temporary array for capturing bits comming in
//bool bitArray[8];
byte lastByte;
// A counter where we are in the bit array
int bitCount = 0;
// The stored up bytes of the last transmission
String packedge = "";

int silenceCount = 0;
void loop() {

  // Read in the values from the green / white wires
  int white = digitalRead(2);
  int green = digitalRead(3);

  // If we recieved a bit, store it in the byte
  if (white != 1 or green != 1) {
    Serial.print(white);
    lastByte = (lastByte << 1) + white;
    bitCount += 1;
    silenceCount = 0;
  }
  // Once we 'fill' a byte, add it to the packedge
  if (bitCount == 8) {
    Serial.println();
    bitCount = 0;
    packedge += String(lastByte) + ' ';
    lastByte = 0;
  }
  
  // Since sometimes we get 7 bytes (ucard) and sometimes 4 (mlh)
  // I set it to print out whenever it is finished recieveing bytes
  silenceCount += 1; 
  if (silenceCount > 30000) {
    // We have not recieved any bits in a while
    // If we have any stored bytes, print them
    if (packedge != "") {
      Serial.println();
      Serial.println("Last transmission:");
      Serial.println(packedge);
      Serial.println();
      packedge = "";
    }
  }
}
