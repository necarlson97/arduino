#include "pitches.h"

#define PIN_BUZZER    13

// play note at given frequency (Hz)
// if frequency is 0, turn off buzzer
void play_note(int freq) {
  if(freq>0) {
    // send square wave at freq Hz with 50% duty cycle (512/1024)
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

// these notes are macro defines in pitches.h
// they define the frequency of each note
int notes[] = {NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4};

// the duration of each note:
// 4 = quarter note, 8 = eighth note, etc.:
int durs[] = {4, 8, 8, 4, 8, 2};

void setup() {
  
  pinMode(PIN_BUZZER, OUTPUT);
  
  play_melody(notes, durs, sizeof(notes)/sizeof(int));
  
  // random seed
  randomSeed(micros());
}

void loop() {
  // generate a random note with frequency
  // between 400Hz and 2kHz
  int freq = random(400, 2000);

  // generate a random duration
  // between 50ms to 200ms
  int duration = random(50, 200);

  play_note(freq);
  delay(duration);  
}

