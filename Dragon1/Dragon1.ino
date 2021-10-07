#include <IRremote.h>

int fade=0;
String command;

int toFade=5;
int fadeSpeed=50;

IRrecv irrecv(3);
decode_results results;

void setup() {
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  irrecv.enableIRIn();

  digitalWrite(13, LOW);
  //Serial.begin(9600);
}

void fadeLed(int ledPin, int i){
  while(fade<200){
    analogWrite(ledPin, fade);
    delay(30);
    fade+=i;
  }
  while(fade>0){
    analogWrite(ledPin, fade);
    delay(30);
    fade-=i;
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    String hexResults = String(results.value, HEX);
    if(hexResults == "5fa02fd") command = "up";
    if(hexResults == "5faba45") command = "down";
    if(hexResults == "5faca35") command = "one"; 
    if(hexResults == "5fa0af5") command = "two"; 
    if(hexResults == "5fa48b7") command = "three";
    if(hexResults == "5faf20d") command = "four"; 
    
    irrecv.resume();
  }

  if(command == "one") toFade = 9;
  if(command == "two") toFade = 10;
  if(command == "three") toFade = 6;

  if(command == "up" && fadeSpeed <249) fadeSpeed +=5;
  if(command == "down" && fadeSpeed >6) fadeSpeed -=5;

  //Serial.println("c: "+command+", led: "+toFade+", s: "+fadeSpeed);

  command = "";
  fadeLed(toFade, fadeSpeed);
  
}
