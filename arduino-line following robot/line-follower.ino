// C++ code
//
/*
 * Line Following Robot - Basic Version
 * Uses 2 IR sensors and conditional logic for line tracking
 * 
 * Hardware:
 * - 2 IR sensors (left and right)
 * - 2 DC motors with L298N motor driver
 * - Arduino Uno
 */

// IR Sensor Pins (Digital)
const int LEFT_SENSOR = 2;
const int RIGHT_SENSOR = 3;

// L298N Motor Driver Pins
// Left Motor
const int LEFT_MOTOR_FORWARD = 5;   // IN1
const int LEFT_MOTOR_BACKWARD = 6;  // IN2
const int LEFT_MOTOR_SPEED = 9;     // ENA (PWM)

// Right Motor
const int RIGHT_MOTOR_FORWARD = 7;  // IN3
const int RIGHT_MOTOR_BACKWARD = 8; // IN4
const int RIGHT_MOTOR_SPEED = 10;   // ENB (PWM)

// Speed Settings
const int BASE_SPEED = 150;      // Normal driving speed (0-255)
const int TURN_SPEED = 100;      // Speed when turning

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("Line Following Robot - Basic Version");
  Serial.println("Starting...");
  
  // Set IR sensor pins as inputs
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  
  // Set motor control pins as outputs
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_SPEED, OUTPUT);
  
  // Brief pause before starting
  delay(2000);
  Serial.println("GO!");
}

void loop() {
  // Read IR sensors
  // Note: IR sensors typically output LOW when detecting black line
  //       and HIGH when detecting white surface
  int leftSensor = digitalRead(LEFT_SENSOR);
  int rightSensor = digitalRead(RIGHT_SENSOR);
  
  // Debug output
  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.print(" | Right: ");
  Serial.print(rightSensor);
  Serial.print(" | Action: ");
  
  // Decision making based on sensor readings
  
  // Case 1: Both sensors on white (off the line) - Move forward
  if (leftSensor == HIGH && rightSensor == HIGH) {
    moveForward();
    Serial.println("FORWARD");
  }
  
  // Case 2: Left sensor on black, right on white - Turn right
  else if (leftSensor == LOW && rightSensor == HIGH) {
    turnRight();
    Serial.println("TURN RIGHT");
  }
  
  // Case 3: Right sensor on black, left on white - Turn left
  else if (leftSensor == HIGH && rightSensor == LOW) {
    turnLeft();
    Serial.println("TURN LEFT");
  }
  
  // Case 4: Both sensors on black (on the line or intersection) - Move forward
  else if (leftSensor == LOW && rightSensor == LOW) {
    moveForward();
    Serial.println("ON LINE - FORWARD");
  }
  
  // Small delay for stability
  delay(50);
}

// Motor Control Functions

void moveForward() {
  // Left motor forward
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  analogWrite(LEFT_MOTOR_SPEED, BASE_SPEED);
  
  // Right motor forward
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  analogWrite(RIGHT_MOTOR_SPEED, BASE_SPEED);
}

void turnLeft() {
  // Left motor slow/stop
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  analogWrite(LEFT_MOTOR_SPEED, 0);
  
  // Right motor forward at turn speed
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  analogWrite(RIGHT_MOTOR_SPEED, TURN_SPEED);
}

void turnRight() {
  // Left motor forward at turn speed
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  analogWrite(LEFT_MOTOR_SPEED, TURN_SPEED);
  
  // Right motor slow/stop
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  analogWrite(RIGHT_MOTOR_SPEED, 0);
}

void stopMotors() {
  // Stop both motors
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  analogWrite(LEFT_MOTOR_SPEED, 0);
  
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  analogWrite(RIGHT_MOTOR_SPEED, 0);
}

void moveBackward() {
  // Left motor backward
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  analogWrite(LEFT_MOTOR_SPEED, BASE_SPEED);
  
  // Right motor backward
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  analogWrite(RIGHT_MOTOR_SPEED, BASE_SPEED);
}
