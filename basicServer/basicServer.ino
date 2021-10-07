#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define PIN_BUTTON 0
#define PIN_BUZZER  13
#define PIN_LED   15
#define PIN_LT_EN 16

ESP8266WebServer server(80);

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

void on_homepage() {
  server.send(200, "text/html", "<h1>Hello from SquareWear Wifi!</h1>");
}

void on_led() {
  int r = random(0, 64);
  int g = random(0, 64);
  int b = random(0, 64);
  pixel.setPixelColor(0, pixel.Color(r, g, b));
  pixel.show();
  
  String html = "<h1>Current LED color (";
  html += r;
  html += ",";
  html += g;
  html += ",";
  html += b;
  html += ")</h1>";
  server.send(200, "text/html", html);
}

void on_status() {
  String html = "";
  html += "{\"button\":";
  html += (1-digitalRead(PIN_BUTTON));
  html += ",\"light\":";
  html += (analogRead(A0));  
  html += "}";
  server.send(200, "text/html", html);
} 

void on_sound(){
  if(digitalRead(PIN_BUTTON) == 1){
    analogWrite(PIN_BUZZER, random(10, 200));
  }
}

void setup(void){
  pixel.begin();
  pixel.show();

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LT_EN, OUTPUT);
  digitalWrite(PIN_LT_EN, HIGH);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(get_ap_name().c_str());

  server.on("/", on_homepage);
  server.on("/js", on_status);
  server.on("/led", on_led);
  server.on("/sound", on_sound);
  
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
