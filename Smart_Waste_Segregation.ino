/*
 * Smart Waste Segregation System (S^3)
 * 
 * Description: An automated waste-sorting embedded system. 
 * An HC-SR04 ultrasonic sensor detects incoming waste in the hopper. 
 * An LJ12A3 inductive proximity sensor checks for metal.
 * A moisture sensor checks for wet/organic matter.
 * An MG996R servo motor routes the waste to the correct bin (Metal, Wet, or Dry).
 */

#include <Servo.h>

// Define Hardware Pins
const int trigPin = 9;           // HC-SR04 Trigger
const int echoPin = 10;          // HC-SR04 Echo
const int proximitySensor = 4;   // LJ12A3 Inductive Metal Sensor (Digital Input)
const int moistureSensor = A0;   // Soil/Rain Sensor (Analog Input)
const int servoPin = 6;          // MG996R Servo Motor

Servo sortingServo;

// Define System Thresholds
const int objectDetectionDistance = 15; // cm threshold to trigger scanning
const int wetWasteThreshold = 600;      // Analog threshold for moisture

// Servo Angles for Bins
const int binDry = 45;
const int binMetal = 90;
const int binWet = 135;
const int homePosition = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(proximitySensor, INPUT);
  pinMode(moistureSensor, INPUT);
  
  sortingServo.attach(servoPin);
  sortingServo.write(homePosition); // Initialize servo to default position
  
  Serial.println("System Initialized: S^3 Ready for Waste Scanning.");
}

void loop() {
  // 1. Check for incoming waste using Ultrasonic Sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Convert to cm
  
  // 2. If an object is detected in the hopper, begin classification
  if (distance > 0 && distance < objectDetectionDistance) {
    Serial.println("Object Detected. Initiating Scan...");
    delay(1000); // Allow object to settle on sensors
    
    // Read Material Sensors
    int isMetal = digitalRead(proximitySensor);
    int moistureLevel = analogRead(moistureSensor);
    
    // 3. Classification Logic & Actuation
    if (isMetal == LOW) { 
      // Inductive sensors typically pull LOW when metal is detected
      Serial.println("Classification: METAL. Routing to Metal Bin.");
      sortingServo.write(binMetal);
    } 
    else if (moistureLevel < wetWasteThreshold) {
      Serial.println("Classification: WET/ORGANIC. Routing to Wet Bin.");
      sortingServo.write(binWet);
    } 
    else {
      Serial.println("Classification: DRY. Routing to Dry Bin.");
      sortingServo.write(binDry);
    }
    
    // Hold position to allow waste to drop, then reset
    delay(3000);
    sortingServo.write(homePosition);
    Serial.println("System Reset. Waiting for next object...");
  }
  
  delay(500); // Short delay before next ultrasonic ping
}
