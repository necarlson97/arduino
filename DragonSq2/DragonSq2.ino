#include <Adafruit_NeoPixel.h>
#include <IRremoteESP8266.h>

#define PIN_LED     15
#define PIN_BUZZER  13

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

String command;
String prevCommand;

int fadeSpeed=25;

int i=-100;
int r=200;
int g=200;
int b=100;

boolean fadingUp=true;
boolean pause=false;

IRrecv irrecv(4);
decode_results results;

void setup() {


  pinMode(PIN_BUZZER, OUTPUT); // Turn off sound
  digitalWrite(PIN_BUZZER, 0);
  pinMode(4, INPUT); // Ir input

  irrecv.enableIRIn(); // Enable ir decoder
  pixel.begin(); // Enable onboard pixel
  pixel.setBrightness(55);
  pixel.show();

}

String getCommand(String hexResults){
  String c;
  if(hexResults == "5fa02fd") c = "plus";
  else if(hexResults == "5faba45") c = "minus";
  else if(hexResults == "5faca35") c = "one"; 
  else if(hexResults == "5fa0af5") c = "two"; 
  else if(hexResults == "5fa48b7") c = "three";
  else if(hexResults == "5faf20d") c = "four"; 
  else if(hexResults == "5fa32cd") c = "five"; 
  
  else if(hexResults == "5fa708f") c = "six"; 
  else if(hexResults == "5fad22d") c = "seven"; 
  else if(hexResults == "5fa12ed") c = "eight"; 
  else if(hexResults == "5fa50af") c = "nine"; 
  else if(hexResults == "5fa22dd") c = "zero"; 

  else if(hexResults == "ffffffff") if(prevCommand == "minus" || prevCommand == "plus") c = prevCommand;
  
  else c = "";
  return c;
}

void loop() {
  if (irrecv.decode(&results)) {
    String hexResults = String(results.value, HEX);
    
    command = getCommand(hexResults);
    
    irrecv.resume();
  }

  if(command != "") prevCommand = command;
  
  if(command == "one") { //Red
    i=-100;
    r = 255;
    g = 0;
    b = 0;
  }
  if(command == "two") { //Orange
    i=-100;
    r = 255; 
    g = 165;
    b = 0;
  }
  if(command == "three") { //Yellow
    i=-100;
    r = 255; 
    g = 255;
    b = 0;
  }
  if(command == "four") { //Green
    i=-100;
    r = 0;
    g = 255;
    b = 0;
  }
  if(command == "five") { //Blue
    i=-100;
    r = 0;
    g = 0;
    b = 255;
  }
  if(command == "six") { //Purple
    i=-100;
    r = 128; 
    g = 0;
    b = 128;
  }
  if(command == "nine") { //White
    i=-100;
    r = 255; 
    g = 255; 
    b = 255;
  }
  
  if(command == "zero") { //Black
    r = 0;
    g = 0;
    b = 0;
  }

  if(command == "plus" && fadeSpeed <100) fadeSpeed +=5;
  if(command == "minus" && fadeSpeed >20) fadeSpeed -=5;

  if(fadingUp) i+=fadeSpeed;
  else i-=fadeSpeed;
  
  if(i<-1000+(fadeSpeed*10)) {
    fadingUp = true;
    i=0;
    pause = false;
  }
  else if(i<0) {
    pause = true;
  }
  else if(i>255) {
    fadingUp = false;
    i=255;
  }

  command = "";
  if(pause) {
    pixel.setBrightness(0); //How bright is is directly propotional to how fast it is (and both are good bounded 5-100)
    pixel.setPixelColor(0, pixel.Color(0,0,0));
  }
  else{
    pixel.setBrightness(fadeSpeed); //How bright is is directly propotional to how fast it is (and both are good bounded 5-100)
    pixel.setPixelColor(0, pixel.Color(r*i/255,g*i/255,b*i/255));
  }
  pixel.show();
  
  delay(60);
  
}

