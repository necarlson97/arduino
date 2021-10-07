#include <Adafruit_NeoPixel.h>

#define PIN_BUTTON   0
#define PIN_BUZZER  13
#define PIN_LED     15
#define PIN_LT_EN   16  // light sensor enable

// create pixel object
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);



void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED,    OUTPUT);
  pinMode(PIN_LT_EN,  OUTPUT);

  digitalWrite(PIN_BUZZER, 0);
  digitalWrite(PIN_LT_EN,  1);

  Serial.begin(9600);

  pixel.begin();
  pixel.setBrightness(100);
}

void loop() {
  // put your main code here, to run repeatedly:

  //going up
  int i = 1;
  int x = 1;
  while(i<40){
    i++;
      if(i%x == 0){
        x++;
        i=0;
      }
      
      analogWrite(PIN_BUZZER, 512);
      analogWriteFreq(440-(i*10));
    
      pixel.setPixelColor(0, 0, 200-i, 0);
      pixel.show();
      delay(5); //Note duration (miliseconds)

      analogWrite(PIN_BUZZER, 0);
      delay(i); // Rest duration (milisecods)

      //Serial.print("Rest duration: ");
      Serial.println(x);
      Serial.println(i);
      
  }

  
  // Restart indicator
  pixel.setPixelColor(0, 225, 0, 0);
  pixel.show();
  delay(250);
  
}

