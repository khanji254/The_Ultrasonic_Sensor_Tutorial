// Define the pins for the ultrasonic sensor
const int trigPin = 7;
const int echoPin = 8;

void setup() {
  Serial.begin(9600);  // Initialize Serial communication
  pinMode(trigPin, OUTPUT);  // Set the trigPin as an output
  pinMode(echoPin, INPUT);   // Set the echoPin as an input
}

void loop() {
  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the pulse sent by the ultrasonic sensor
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters (assuming speed of sound is 343 meters/second)
  float distanceCM = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  // Delay before the next measurement
  delay(1000);  // Adjust the delay as needed
}
