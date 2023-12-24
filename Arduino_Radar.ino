#include <Servo.h>

const int trigPin = 7;
const int echoPin = 8;
long duration;
int distance;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(3);
}

void loop() {
  // Sweep the servo motor from 15 to 165 degrees
  for (int angle = 15; angle <= 165; angle++) {
    moveServo(angle);
    delay(30);
    printDistance(angle);
  }

  // Sweep the servo motor back from 165 to 15 degrees
  for (int angle = 165; angle > 15; angle--) {
    moveServo(angle);
    delay(30);
    printDistance(angle);
  }
}

void moveServo(int angle) {
  myServo.write(angle);
}

void printDistance(int angle) {
  distance = calculateDistance();
  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.println(".");
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

