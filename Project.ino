#include <ESP32Servo.h>

// Assign your actual GPIO pins here
#define servoPin  14
#define soilS 13
#define relayPin  26
#define fireS     25
#define buzzerLED 27

Servo myServo;
int pos = 0;
int step = 1;
unsigned long lastTime = 0;
unsigned long lastAlarmTime = 0;

void setup() {
  // 1. Water System
  myServo.attach(servoPin);
  myServo.write(0);
  pinMode(soilS, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Relay OFF (assuming Active Low)

  // 2. Fire System
  pinMode(fireS, INPUT);
  pinMode(buzzerLED, OUTPUT);
}

void loop() {
  // --- SYSTEM 1: WATER ---
  bool drySoil = digitalRead(soilS); 
  if (drySoil) {
    runServoSweep(15);
    digitalWrite(relayPin, 1); // Turn turbine ON
  } else {
    digitalWrite(relayPin, 0); // Turn turbine OFF
    myServo.write(0);             // Reset servo
    pos = 0;                      // Reset position variable
  }

  // --- SYSTEM 2: FIRE ---
  bool alarm = digitalRead(fireS);
  if (millis() - lastAlarmTime >= 500) {
    lastAlarmTime = millis();
    
    if (alarm) {
      // Toggle LED/Buzzer or keep HIGH
      digitalWrite(buzzerLED, !digitalRead(buzzerLED)); 
    } else {
      digitalWrite(buzzerLED, LOW);
    }
  }
}

// Simple non-blocking sweep function
void runServoSweep(int speedMs) {
  if (millis() - lastTime >= speedMs) {
    lastTime = millis();
    pos += step;
    if (pos >= 180 || pos <= 0) {
      step = -step;
    }
    myServo.write(pos);
  }
}