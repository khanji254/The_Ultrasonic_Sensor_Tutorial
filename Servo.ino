#include <Servo.h>

Servo myServo;  // Create a servo object

void setup() {
  myServo.attach(9);  // Attach the servo to pin 9
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);  // Move the servo to the current angle
    delay(15);  // Adjust the delay for the desired speed
  }

  delay(1000);  // Pause at the end of the sweep

  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);  // Move the servo to the current angle
    delay(15);  // Adjust the delay for the desired speed
  }

  delay(1000);  // Pause at the end of the sweep
}
