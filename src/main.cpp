#include <Arduino.h>
#define PIN_ULTRASONIC 9

#define LED_RED_1 2
#define LED_RED_2 3
#define LED_YELLOW_1 4
#define LED_YELLOW_2 5
#define LED_GREEN_1 6
#define LED_GREEN_2 7
#define LED_GREEN_3 8

#define DISTANCE_RED 100
#define DISTANCE_YELLOW 150
#define DISTANCE_GREEN 200

double getDistance() {
  // Send a short low-high-low pulse to trigger the sensor (a "ping")
  pinMode(PIN_ULTRASONIC, OUTPUT);
  digitalWrite(PIN_ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_ULTRASONIC, HIGH);
  delayMicroseconds(5);
  digitalWrite(PIN_ULTRASONIC, LOW);

  // Switch the ultrasonic pin to input to read the incoming pulse
  pinMode(PIN_ULTRASONIC, INPUT);

  // PulseIn function measures the time in microseconds until we get a HIGH signal
  unsigned long duration = pulseIn(PIN_ULTRASONIC, HIGH);

  // Return the distance (duration/2) / 29.1 gives distance in cm
  return duration / 58.0;
}

void setLEDs(int red, int yellow, int green) {
  // Set the state of the LEDs
  digitalWrite(LED_RED_1, red);
  digitalWrite(LED_RED_2, red);
  digitalWrite(LED_YELLOW_1, yellow);
  digitalWrite(LED_YELLOW_2, yellow);
  digitalWrite(LED_GREEN_1, green);
  digitalWrite(LED_GREEN_2, green);
  digitalWrite(LED_GREEN_3, green);
}

void setup() {
  // Set the LED pins as outputs
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_YELLOW_1, OUTPUT);
  pinMode(LED_YELLOW_2, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_GREEN_2, OUTPUT);
  pinMode(LED_GREEN_3, OUTPUT);

  // Initialize serial communication at 9600 baud for debugging
  Serial.begin(9600);
}

void loop() {
  // Fetch the current distance
  double distance = getDistance();

  // Print the distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Determine the LED state based on the distance
  if (distance > DISTANCE_GREEN) {
    // All LEDs off
    setLEDs(LOW, LOW, LOW);
  } else if (distance > DISTANCE_YELLOW) {
    // Green LEDs on
    setLEDs(LOW, LOW, HIGH);
  } else if (distance > DISTANCE_RED) {
    // Yellow LEDs on
    setLEDs(LOW, HIGH, LOW);
  } else {
    // Red LEDs on
    setLEDs(HIGH, LOW, LOW);
  }

  // Short delay before next loop
  delay(50);
}
