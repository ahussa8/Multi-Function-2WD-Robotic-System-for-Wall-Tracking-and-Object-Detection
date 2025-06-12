/*
Team 3: M.C.
Abbas Hussain & Nadia Carr
Challenge 2 (w/IR Receiver)
References:
  Given document for using IR receiver w/Rev3 Motor shield 
  https://docs.arduino.cc/tutorials/motor-shield-rev3/msr3-controlling-dc-motor/ 
  https://projecthub.arduino.cc/tmekinyan/playing-popular-songs-with-arduino-and-a-buzzer-546f4a
  https://github.com/hibit-dev/buzzer#readme  
*/

// === Libraries ===
#include "IRLremote.h"  
#include "pitches.h"    // For passive buzzer songs

// === IR protocol ===
CNec irrecv; 

// === Sensor Pins ===
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 500  // cm

// === IR & Buzzer Pins ===
#define pinIR 2
#define BUZZER_PIN 5

// === Motor Pins ===
// Left Motor (Channel A)
#define dirPinL 12
#define pwmPinL 3
#define brakePinL 9

// Right Motor (Channel B)
#define dirPinR 13
#define pwmPinR 11
#define brakePinR 8

// === Control Parameters ===
#define MOVE_SPEED    90
#define TURN_DELAY    200

void setup() {
  Serial.begin(9600);

  pinMode(dirPinL, OUTPUT);
  pinMode(pwmPinL, OUTPUT);
  pinMode(brakePinL, OUTPUT);

  pinMode(dirPinR, OUTPUT);
  pinMode(pwmPinR, OUTPUT);
  pinMode(brakePinR, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  // === For Passive Buzzer Tunes ===
  while (!Serial);
  Serial.begin(9600); //note -- IRL code has 115200 baud rate
  Serial.println(F("Startup"));

 // Start reading the remote. PinInterrupt or PinChangeInterrupt* will automatically be selected
  if (!irrecv.begin(pinIR))
  Serial.println(F("You did not choose a valid pin.")); 

}

void loop() {
 // Check if new IR protocol data is available
 if (irrecv.available()) {
  translateIR(); //method to decode remote press
 }
}

// === UDFs ===
// Decodes remote press
void translateIR() {
  // Get the new data from the remote
  auto data = irrecv.read(); 
  //map the IR code to the remote key
  switch (data.command){
    case 0x45: Serial.println("POWER"); break;
    case 0x47: Serial.println("FUNC/STOP"); break;
    case 0x46: Serial.println("VOL+");            // forward
      forward();
      break;
    case 0x44: Serial.println("FAST BACK");       // left
      left();
      break;
    case 0x40: Serial.println("PAUSE");           // stop
      stop();
      break;    
    case 0x43: Serial.println("FAST FORWARD");    // right
      right();
      break;
    case 0x07: Serial.println("DOWN"); break;
    case 0x15: Serial.println("VOL-");            // backwards
      horn();
      backward();
      break;
    case 0x09: Serial.println("UP"); break;
    case 0x19: Serial.println("EQ");              // horn honk honk
      horn();
      break;
    case 0x0D: Serial.println("ST/REPT"); break;
    case 0x16: Serial.println("0");               // nokia
      nokia();
      break;
    case 0x0C: Serial.println("1");               // pacman        
      pacman();
      break;
    case 0x18: Serial.println("2"); 
      yoshi();
      break;
    case 0x5E: Serial.println("3"); break;
    case 0x08: Serial.println("4"); break;
    case 0x1C: Serial.println("5"); break;
    case 0x5A: Serial.println("6"); break;
    case 0x42: Serial.println("7"); break;
    case 0x52: Serial.println("8"); break;
    case 0x4A: Serial.println("9"); break;
    default:  
      Serial.println(" other button ");
  }// End Case
  delay(400); // Do not get immediate repeat
} 

// Both motors forwards
void forward() {
  
  digitalWrite(dirPinL, HIGH);
  digitalWrite(dirPinR, LOW); 

  analogWrite(pwmPinL, MOVE_SPEED);  
  analogWrite(pwmPinR, MOVE_SPEED+8);

  digitalWrite(brakePinL, LOW);
  digitalWrite(brakePinR, LOW);
}

// Both motors backwards
void backward() {

  digitalWrite(dirPinL, LOW);
  digitalWrite(dirPinR, HIGH); 

  analogWrite(pwmPinL, MOVE_SPEED);  
  analogWrite(pwmPinR, MOVE_SPEED+5);

  digitalWrite(brakePinL, LOW);
  digitalWrite(brakePinR, LOW);

}

// Turns to the left
void left() {

  digitalWrite(brakePinL, LOW);
  digitalWrite(brakePinR, LOW);

  digitalWrite(dirPinL, LOW);
  digitalWrite(dirPinR, LOW);

  analogWrite(pwmPinL, MOVE_SPEED);
  analogWrite(pwmPinR, MOVE_SPEED);

  delay(TURN_DELAY);
  stop();
}

// Turns to the right
void right() {
  digitalWrite(brakePinL, LOW);
  digitalWrite(brakePinR, LOW);

  digitalWrite(dirPinL, HIGH);
  digitalWrite(dirPinR, HIGH);

  analogWrite(pwmPinL, MOVE_SPEED);
  analogWrite(pwmPinR, MOVE_SPEED);

  delay(TURN_DELAY);
  stop();
}

// Stops both motors
void stop() {
  digitalWrite(brakePinL, HIGH);
  digitalWrite(brakePinR, HIGH);
}

// honk honk
void horn() {

  tone(BUZZER_PIN, NOTE_E3, 75);

  delay(200);
  
  noTone(BUZZER_PIN);

  tone(BUZZER_PIN, NOTE_E3, 100);

  delay(200);
  
  noTone(BUZZER_PIN);
                                                                                                                                                     
}

// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// https://github.com/hibit-dev/buzzer/blob/master/src/other/nokia/nokia.ino 
// -------------------------------------------------

void nokia() {    // 0

  int melodynokia[] = {
    NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_GS4, 
    NOTE_CS5, NOTE_B4, NOTE_D4, NOTE_E4, 
    NOTE_B4, NOTE_A4, NOTE_CS4, NOTE_E4,
    NOTE_A4
  };

  int durationsnokia[] = {
    8, 8, 4, 4,
    8, 8, 4, 4,
    8, 8, 4, 4,
    2
  };

  int size = sizeof(durationsnokia) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durationsnokia[note];
    tone(BUZZER_PIN, melodynokia[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}

// -------------------------------------------------
// Copyright (c) 2022 HiBit <https://www.hibit.dev>
// https://github.com/hibit-dev/buzzer/blob/master/src/games/tetris/tetris.ino 
// -------------------------------------------------

void pacman() {   // 1

  int melodypacman[] = {
    NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5,
    NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_C5,
    NOTE_C6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_G6, NOTE_E6,
    
    NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,
    NOTE_FS5, NOTE_DS5, NOTE_DS5, NOTE_E5, NOTE_F5,
    NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_B5
  };

  int durationspacman[] = {
    16, 16, 16, 16,
    32, 16, 8, 16,
    16, 16, 16, 32, 16, 8,
    
    16, 16, 16, 16, 32,
    16, 8, 32, 32, 32,
    32, 32, 32, 32, 32, 16, 8
  };

  int size = sizeof(durationspacman) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durationspacman[note];
    tone(BUZZER_PIN, melodypacman[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}

// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// https://github.com/hibit-dev/buzzer/blob/master/src/games/yoshis_island/yoshis_island.ino 
// -------------------------------------------------

void yoshi() {    // 2
  
  int melodyyoshi[] = {
    NOTE_C5, NOTE_GS4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_F5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_FS5, NOTE_D5, NOTE_A5,
    NOTE_A5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_C6, NOTE_A5,
    NOTE_C5, NOTE_A5, NOTE_F5
  };

  int durationsyoshi[] = {
    6, 6, 6, 6, 6, 6, 2,
    6, 6, 6, 6, 6, 2,
    6, 6, 6, 6, 6, 3,
    6, 6, 1
  };

  int size = sizeof(durationsyoshi) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durationsyoshi[note];
    tone(BUZZER_PIN, melodyyoshi[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}


