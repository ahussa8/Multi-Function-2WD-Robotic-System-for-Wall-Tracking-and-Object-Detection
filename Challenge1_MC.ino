/*
Team 3: M.C.
Abbas Hussain & Nadia Carr
Challenge 1  
References:
  https://docs.arduino.cc/tutorials/motor-shield-rev3/msr3-controlling-dc-motor/
*/

// === Libraries ===
#include <Servo.h>
#include "NewPing.h"

// === Sensor Pins ===
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 400

// === Motor Pins ===
// Left Motor (Channel A)
#define dirPinL 12
#define pwmPinL 3
#define brakePinL 9

// Right Motor (Channel B)
#define dirPinR 13
#define pwmPinR 11
#define brakePinR 8

// === Sensor Setup ===
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// === Control Parameters ===
#define target 40
#define turndelay 650

// === Booleans ===
bool turn = false;

void setup() {
  Serial.begin(9600);

  // Left motor
  pinMode(dirPinL, OUTPUT);
  pinMode(pwmPinL, OUTPUT);
  pinMode(brakePinL, OUTPUT);

  // Right motor
  pinMode(dirPinR, OUTPUT);
  pinMode(pwmPinR, OUTPUT);
  pinMode(brakePinR, OUTPUT);
}

void loop() {

  int count = 0;  
  int dist = sonar.convert_cm(sonar.ping_median());   // sensor filtering

  for (int i = 0; i < 1000; i++) {  // intially going forward
    if (dist > target) {
      count++;                      // Counts time until goal is reached for return
      digitalWrite(dirPinL, HIGH);
      digitalWrite(dirPinR, LOW);

      digitalWrite(brakePinL, LOW);
      digitalWrite(brakePinR, LOW);

      analogWrite(pwmPinL, 120);
      analogWrite(pwmPinR, 128);

      dist = sonar.convert_cm(sonar.ping_median());
      delay(100);      
    } else {      // goal is reached
      turn = true;
      i = 10000;
    }
  }
  // U turn then go back to start
  if (turn == true) {
    digitalWrite(brakePinL, HIGH);
    digitalWrite(brakePinR, HIGH);
    delay(1000);

    // U turn to the right
    digitalWrite(dirPinL, LOW);
    digitalWrite(dirPinR, LOW);

    //release breaks
    digitalWrite(brakePinL, LOW);
    digitalWrite(brakePinR, LOW);

    //set work duty for the motor
    analogWrite(pwmPinL, 90);
    analogWrite(pwmPinR, 90);
    delay(turndelay);

    // pause
    digitalWrite(brakePinL, HIGH);
    digitalWrite(brakePinR, HIGH);
    delay(1000);

    // Goes back towards start for the same amount of time as it took to get to the goal
    for (int j = 0; j < count+1; j++) {   
      digitalWrite(dirPinL, HIGH);
      digitalWrite(dirPinR, LOW);

      digitalWrite(brakePinL, LOW);
      digitalWrite(brakePinR, LOW);

      analogWrite(pwmPinL, 120);
      analogWrite(pwmPinR, 125);

      dist = sonar.convert_cm(sonar.ping_median());
      delay(100); 
    }
  }
  // STOP
  digitalWrite(brakePinL, HIGH);
  digitalWrite(brakePinR, HIGH);
  delay(10000);
}
