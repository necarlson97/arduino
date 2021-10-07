#include <Adafruit_NeoPixel.h>
#include <IRremoteESP8266.h>

#define PIN_LED     15
#define PIN_BUZZER  13

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

String command;

int fadeSpeed=50;

int i=1;
int r=200;
int g=200;
int b=100;
boolean fadingUp=true;

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

void loop() {
  if (irrecv.decode(&results)) {
    String hexResults = String(results.value, HEX);
    
    if(hexResults == "5fa02fd") command = "plus";
    if(hexResults == "5faba45") command = "minus";
    if(hexResults == "5faca35") command = "one"; 
    if(hexResults == "5fa0af5") command = "two"; 
    if(hexResults == "5fa48b7") command = "three";
    if(hexResults == "5faf20d") command = "four"; 
    if(hexResults == "5fa32cd") command = "five"; 
    
    if(hexResults == "5fa708f") command = "six"; 
    if(hexResults == "5fad22d") command = "seven"; 
    if(hexResults == "5fa12ed") command = "eight"; 
    if(hexResults == "5fa50af") command = "nine"; 
    if(hexResults == "5fa22dd") command = "zero"; 
    
    irrecv.resume();
  }
  
  if(command == "one") { //Red
    r = 255;
    g = 0;
    b = 0;
  }
  if(command == "two") { //Orange
    r = 255; 
    g = 165;
    b = 0;
  }
  if(command == "three") { //Yellow
    r = 255; 
    g = 255;
    b = 0;
  }
  if(command == "four") { //Green
    r = 0;
    g = 255;
    b = 0;
  }
  if(command == "five") { //Blue
    r = 0;
    g = 0;
    b = 255;
  }
  if(command == "six") { //Purple
    r = 128; 
    g = 0;
    b = 128;
  }
  if(command == "nine") { //White
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
  
  if(i<0) {
    fadingUp = true;
    i=0;
  }
  else if(i>255) {
    fadingUp = false;
    i=255;
  }

  command = "";

  pixel.setBrightness(fadeSpeed); //How bright is is directly propotional to how fast it is (and both are good bounded 5-100)
  pixel.setPixelColor(0, pixel.Color(r*i/255,g*i/255,b*i/255));
  pixel.show();
  delay(50);
  
}

