#define AnalogInFrequency 1
#define AnalogInTempo 2
#define AnalogInDuration 0
#define DigitalOutSignal 11
#define DigitalInSwitch0 2
#define DigitalInSwitch1 3
#define DigitalInSwitch2 4
#define DigitalInSwitch3 5
#define DigitalInSwitch4 6
#define DigitalInSwitch5 7
#define DigitalInSwitch6 8
#define DigitalInSwitch7 9
#define DigitalInStartStop 10

#define DigitalOutLED 12
int steps[] = {100, 120, 140, 160, 180, 200, 220, 240};

int duration = 50;
int pitchval = 1;
int fPlayMode = true;
int lastPushedStep = -1;

int tempo = 1000;
void setup()
{

  pinMode (DigitalInSwitch0, INPUT);
  pinMode (DigitalInSwitch1, INPUT);
  pinMode (DigitalInSwitch2, INPUT);
  pinMode (DigitalInSwitch3, INPUT);
  pinMode (DigitalInSwitch4, INPUT);
  pinMode (DigitalInSwitch5, INPUT);
  pinMode (DigitalInSwitch6, INPUT);
  pinMode (DigitalInSwitch7, INPUT);
  pinMode (DigitalInStartStop, INPUT);
  pinMode (DigitalOutSignal, OUTPUT);
  pinMode (DigitalOutLED, OUTPUT);
  pinMode (AnalogInTempo, INPUT);
  pinMode (AnalogInFrequency, INPUT);
  pinMode (AnalogInDuration, INPUT);
}
void loop()
{
  // sequence
  for (int i = 0; i < 8; i++)
  {
    fPlayMode = digitalRead (DigitalInStartStop);
    digitalWrite (DigitalOutLED, HIGH);
    readSwitches();
    readPots();

    //noise
    if (fPlayMode)
    {
      freqout (steps[i], duration);
    }
    digitalWrite (DigitalOutLED, LOW);
    delay (tempo); //time between steps
  }
}
// read the current values of the pots
void readPots ()
{
  tempo = analogRead(AnalogInTempo);
  duration = analogRead(AnalogInDuration);
}
// read the current values of the switches and
// if pressed, replace the switch’s slot frequency
// by reading the frequency pot
void readSwitches()
{

  lastPushedStep = -1;
  if (digitalRead (DigitalInSwitch0) == HIGH)
  {
    steps[0] = analogRead(AnalogInFrequency);
    lastPushedStep = 1;
  }

  else if (digitalRead (DigitalInSwitch1) == HIGH)
  {
    steps[1] = analogRead(AnalogInFrequency);
    lastPushedStep = 2;
  }

  else if (digitalRead (DigitalInSwitch2) == HIGH)
  {
    steps[2] = analogRead(AnalogInFrequency);
    lastPushedStep = 3;
  }
  else if (digitalRead (DigitalInSwitch3) == HIGH)
  {
    steps[3] = analogRead(AnalogInFrequency);
    lastPushedStep = 4;
  }
  else if (digitalRead (DigitalInSwitch4) == HIGH)
  {
    steps[4] = analogRead(AnalogInFrequency);
    lastPushedStep = 5;
  }
  else if (digitalRead (DigitalInSwitch5) == HIGH)
  {
    steps[5] = analogRead(AnalogInFrequency);
    lastPushedStep = 6;
  }
  else if (digitalRead (DigitalInSwitch6) == HIGH)
  {
    steps[6] = analogRead(AnalogInFrequency);
    lastPushedStep = 7;
  }
  else if (digitalRead (DigitalInSwitch7) == HIGH)
  {
    steps[7] = analogRead(AnalogInFrequency);
    lastPushedStep = 8;
  }
}
//freqout code by Paul Badger

// freq – frequency value

// t – time duration of tone

void freqout(int freq, int t)
{
  int hperiod;
  long cycles, i;
  hperiod = (500000 / ((freq – 7) * pitchval));
  
  // calculate cycles
  cycles = ((long)freq * (long)t) / 1000;
  for (i = 0; i <= cycles; i++)
  { // play note for t ms
    digitalWrite(DigitalOutSignal, HIGH);
    delayMicroseconds(hperiod);
    digitalWrite(DigitalOutSignal, LOW);
    delayMicroseconds(hperiod - 1);
  }
}
