#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 7;
const int echoPin = 8;
const int buzzerPin = 9;
const float badDistanceThreshold = 70;

LiquidCrystal_I2C lcd(0x27, 20, 4);
int state = -1;

float mm;
int newDelay;
unsigned long currentMillis;
unsigned long previousMillis = 0;  // Variable to store the last time something happened
unsigned long interval;
unsigned long prevBuzz = 0;
unsigned long currentBuzz ;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Value:");
}

float measureDistance() {
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration / 5.8; // Convert the time to millimeters
}

void updateDisplay() {
  lcd.setCursor(1, 0);
  if (state == 0) {
    lcd.print("Bad  :(");
  } else if (state == 1) {
    lcd.print("Good :)");
  }

  lcd.setCursor(7, 1);
  lcd.print(mm, 2);
}

void updateBuzz() {
  // Calculate the number of buzzes based on distance (adjust as needed)
  // Calculate the pitch based on distance (adjust as needed)
  tone(buzzerPin, 880, 500); // Adjust duration as needed
}

void loop() {
  currentMillis = millis();
  currentBuzz = millis();
  mm = measureDistance();
  Serial.print("Distance: ");
  Serial.println(mm, 2);
  updateDisplay();
  newDelay = ((mm) * 5) + 30;
  interval = map(mm, 0, badDistanceThreshold, 10, 500);

  if (mm < badDistanceThreshold) {
    state = 0; // Set to "Bad" state

    if (currentMillis - previousMillis >= interval) {
      updateBuzz();
     prevBuzz = currentBuzz; 
      previousMillis = currentMillis;  // Update the last time something happened
    }
  } else {
    state = 1; // Set to "Good" state
    delay(10);
  }
  if (currentBuzz - prevBuzz >= 100){
    noTone(buzzerPin);

  }

  delay(100);
}
