/*
Team 3: M.C.
Abbas Hussain & Nadia Carr
Challenge 3A
References:
  https://forum.arduino.cc/t/pid-control-on-2-wheels-robot/534233/16 
  https://docs.arduino.cc/tutorials/motor-shield-rev3/msr3-controlling-dc-motor/ 
*/

// === Libraries ===
#include <Servo.h>
#include "NewPing.h"

// === PD Constants ===
#define KP  0.4   // change until it oscillates at target dist
#define KD  1.6   // change until oscillations are minimal

// === Control Parameters ===
#define TARGET_DISTANCE_CM 30.0  // Desired distance from wall (cm)
#define BASE_SPEED         70   // Nominal PWM speed (0–255)
#define MAX_SPEED          90   // Max
#define MIN_SPEED          60   // Min
#define LOOP_INTERVAL_MS   50   // Control loop interval

// === Ultrasonic Sensor Setup ===
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 300
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// === Motor Pins ===
// Left Motor (Channel A)
int dirPinL = 12;
int pwmPinL = 3;
int brakePinL = 9;

// Right Motor (Channel B)
int dirPinR = 13;
int pwmPinR = 11;
int brakePinR = 8;

// === PD State ===
float last_error = 0.0;

void setup() {

  Serial.begin(9600);

  // left motor
  pinMode(dirPinL, OUTPUT);
  pinMode(pwmPinL, OUTPUT);
  pinMode(brakePinL, OUTPUT);

  // right motor
  pinMode(dirPinR, OUTPUT);
  pinMode(pwmPinR, OUTPUT);
  pinMode(brakePinR, OUTPUT);
}

void loop() {
  
  float distance = sonar.convert_cm(sonar.ping_median()); // sensor filter

  // correction calculation
  float error = TARGET_DISTANCE_CM - distance;
  float derivative = (error - last_error) / (LOOP_INTERVAL_MS / 1000.0);
  float correction = KP * error + KD * derivative;
  last_error = error;

  // apply correction to motor speed
  int right_pwm = BASE_SPEED + correction;
  int left_pwm = (BASE_SPEED-5) - correction;

  // constrain to min and max speed
  left_pwm = constrain(left_pwm, MIN_SPEED, MAX_SPEED);
  right_pwm = constrain(right_pwm, MIN_SPEED, MAX_SPEED);

  // calls UDF to set motor speeds
  setMotorSpeeds(left_pwm, right_pwm);

  delay(LOOP_INTERVAL_MS);
}

// === UDFs ===
void setMotorSpeeds(int left_pwm, int right_pwm) {
  // Drive both motors forward
  digitalWrite(brakePinL, LOW);
  digitalWrite(dirPinL, HIGH); 
  analogWrite(pwmPinL, left_pwm);

  digitalWrite(brakePinR, LOW);
  digitalWrite(dirPinR, LOW); 
  analogWrite(pwmPinR, right_pwm);
}
