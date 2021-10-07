#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define PIN_BUTTON 0
#define PIN_LED   15
#define PIN_LT_EN 16

ESP8266WebServer server(80);

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

#include "html_index.h"
void on_homepage() {
  String html = FPSTR(html_index);
  server.send(200, "text/html", html);
}

int r, g, b;

void random_led() {
  r = random(0, 64);
  g = random(0, 64);
  b = random(0, 64);
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
}

void on_status() {
  random_led(); // change LED color upon calling on_status
  String html = "";
  html += "{\"button\":";
  html += (1-digitalRead(PIN_BUTTON));
  html += ",\"light\":";
  html += (analogRead(A0));
  html += ",\"led\":\"(";
  html += r;
  html += ",";
  html += g;
  html += ",";
  html += b;
  html += ")\"}";

  server.send(200, "text/html", html);
} 

void setup(void){
  pixel.begin();
  pixel.show();
  
  pinMode(PIN_LT_EN, OUTPUT);
  digitalWrite(PIN_LT_EN, HIGH);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(get_ap_name().c_str());

  server.on("/", on_homepage);
  server.on("/js", on_status);
  
  server.begin();
}
 
void loop(void){
  server.handleClient();
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
