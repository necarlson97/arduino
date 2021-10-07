#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "pitches.h"

#define PIN_BUTTON   0
#define PIN_BUZZER  13
#define PIN_LED     15
#define PIN_LT_EN   16  // light sensor enable

#define BLINK_DELAY_TIME  500 // 500 milliseconds

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

int demo_index = 0;
// the variable below is modified by interrupt service routine, so declare it as volatile
volatile boolean button_clicked = false;

// play note at given frequency (Hz)
// if frequency is 0, turn off buzzer
void play_note(int freq) {
  if(freq>0) {
    // send square wave at freq Hz with 50% duty cycle
    analogWrite(PIN_BUZZER, 512);
    analogWriteFreq(freq);
  } else {
    analogWrite(PIN_BUZZER, 0);
  }
}

// play a melody given the notes and durations of each note
void play_melody(int notes[], int durations[], int num_notes) {

  for (int i = 0; i < num_notes; i++) {
    int delaytime = 1000 / durations[i];
    play_note(notes[i]);
    delay(delaytime);
    
    play_note(0);
    delay(delaytime*0.3); // add 30% pause between notes
  }  
}

void demo_startup() {
  // these notes are macro defines in pitches.h
  // they define the frequency of each note
  int notes[] = {NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4};

  // the duration of each note:
  // 4 = quarter note, 8 = eighth note, etc.:
  int durs[] = {4, 8, 8, 4, 8, 2};
  
  play_melody(notes, durs, sizeof(notes)/sizeof(int));
}

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED,    OUTPUT);
  pinMode(PIN_LT_EN,  OUTPUT);
  
  digitalWrite(PIN_BUZZER, 0);
  digitalWrite(PIN_LT_EN,  1);  // enable light sensor

  demo_startup();
  delay(500);
  
  pixel.begin();
  // set low brightness to avoid blind your eyes!
  pixel.setBrightness(48);
  
  // set interrupt on falling edge of button click
  attachInterrupt(PIN_BUTTON, button_handler, FALLING);
}

void demo_tune() {
  // these notes are macro defines in pitches.h
  // they define the frequency of each note
  int notes[] = {NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_E5,
                 NOTE_DS5,NOTE_B4, NOTE_DS5,NOTE_D5, NOTE_AS4, NOTE_D5,
                 NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_A5,
                 NOTE_G5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5};

  // the duration of each note:
  // 4 = quarter note, 8 = eighth note, etc.:
  int durs[] = {8, 8, 8, 8, 8, 8, 4,
                8, 8, 4, 8, 8, 4,
                8, 8, 8, 8, 8, 8, 8, 8,
                8, 8, 8, 8, 2};
  
  play_melody(notes, durs, sizeof(notes)/sizeof(int));
  delay(500);
}

void demo_blink(byte r, byte g, byte b) {
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
  delay(BLINK_DELAY_TIME);

  pixel.setPixelColor(0, pixel.Color(0, 0, 0));
  pixel.show();
  delay(BLINK_DELAY_TIME);    
}

void demo_wheel() {
  for(byte i=0;i<255;i++) {
    pixel.setPixelColor(0, wheel(i));
    pixel.show();
    delay(10);
  }
}

void demo_light_sensor() {
  if(analogRead(A0) > 500) {
    pixel.setPixelColor(0, pixel.Color(0, 255, 0));
    pixel.show();
    play_note(0);
  } else {
    pixel.setPixelColor(0, pixel.Color(255, 0, 0));
    pixel.show();
    play_note(1000);
  }
}

ESP8266WebServer server(80);

#include "html_homepage.h"
void on_homepage() {
  String html = FPSTR(html_homepage);
  server.send(200, "text/html", html);
}

// this returns device status in JSON, e.g.
// {"button":0,"light":450}
void on_status() {
  String html = "";
  html += "{\"button\":";
  html += (1-digitalRead(PIN_BUTTON));
  html += ",\"light\":";
  html += (analogRead(A0));  
  html += "}";
  server.send(200, "text/html", html);
}

void on_change_color() {
  int value;
  byte r, g, b;
  if(get_value_by_key("r", value))  r = value;
  if(get_value_by_key("g", value))  g = value;
  if(get_value_by_key("b", value))  b = value;    
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
  int freq = random(110,1100);
  play_note(freq);
  delay(60);
  play_note(0);
  server.send(200, "text/html", "{\"result\":1}");
}

void demo_webserver() {
  static bool initialized = false;
  if(!initialized) {
    Serial.print("start ap...");
    String ap_name = get_ap_name();
    WiFi.softAP(ap_name.c_str());
    WiFi.mode(WIFI_AP);
    
    server.on("/",   on_homepage);    
    server.on("/js", on_status);
    server.on("/cc", on_change_color);
    server.begin();
    
    Serial.println("ok.");
    initialized = true;
  }

  server.handleClient();
}

void loop() {
  switch(demo_index) {
  
  case 0:
    demo_tune();
    break;
    
  case 1:
    demo_blink(255, 0, 0);
    demo_blink(0, 255, 0);
    demo_blink(0, 0, 255);
    break;

  case 2:
    demo_blink(255, 255, 0);
    demo_blink(255, 0, 255);
    demo_blink(0, 255, 255);
    break;
      
  case 3:
    demo_wheel();  
    break;
    
  case 4:
    demo_light_sensor();
    break;
 
  default:
    demo_webserver();
    break;
  }   
  
  if(button_clicked) {
    demo_index ++;
    button_clicked = false;
    play_note(0);
    pixel.setPixelColor(0, 0);
    pixel.show();
    delay(50); // to prevent 
  }
}

void button_handler() {
  button_clicked = true;
}

uint32_t wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

char dec2hex(byte dec) {
  if(dec<10) return '0'+dec;
  else return 'A'+(dec-10);
}

String get_ap_name() {
  static String ap_name = "";
  if(!ap_name.length()) {
    byte mac[6];
    WiFi.macAddress(mac);
    ap_name = "SW_";
    for(byte i=3;i<6;i++) {
      ap_name += dec2hex((mac[i]>>4)&0x0F);
      ap_name += dec2hex(mac[i]&0x0F);
    }
  }
  return ap_name;
}

bool get_value_by_key(const char* key, int& val) {
  if(server.hasArg(key)) {
    val = server.arg(key).toInt();   
    return true;
  } else {
    return false;
  }
}

