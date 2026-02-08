// C++ code
//
/*
 * Soil Moisture-Based Irrigation Controller
 * Features: Hysteresis thresholds, LED indicators, serial logging
 * 
 * Hardware Connections:
 * - Soil sensor analog output -> A0
 * - Pump relay control -> Pin 8
 * - Red LED (dry) -> Pin 12 (+ 220Ω resistor)
 * - Green LED (wet) -> Pin 11 (+ 220Ω resistor)
 * - Blue LED (pumping) -> Pin 10 (+ 220Ω resistor)
 */

// Pin definitions
const int SOIL_SENSOR_PIN = A0;    // Analog pin for soil moisture sensor
const int PUMP_PIN = 8;             // Digital pin for water pump relay
const int DRY_LED_PIN = 12;         // Red LED - soil too dry
const int WET_LED_PIN = 11;         // Green LED - soil optimal
const int PUMPING_LED_PIN = 10;     // Blue LED - pump active

// Hysteresis thresholds (adjust based on your sensor calibration)
// FOR CAPACITIVE SENSORS (TinkerCAD default): Lower = dry, Higher = wet
// FOR RESISTIVE SENSORS: Higher = dry, Lower = wet
const int DRY_THRESHOLD = 300;      // Start watering when soil is this dry (LOW value)
const int WET_THRESHOLD = 600;      // Stop watering when soil reaches this moisture (HIGH value)

// Timing constants
const unsigned long PUMP_MAX_TIME = 10000;  // Max pump runtime (10 seconds)
const unsigned long READ_INTERVAL = 2000;   // Sensor reading interval (2 seconds)

// State variables
bool isPumping = false;
unsigned long lastReadTime = 0;
unsigned long pumpStartTime = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("=== Soil Moisture Irrigation System ===");
  Serial.println("Starting up...\n");
  
  // Configure pins
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(DRY_LED_PIN, OUTPUT);
  pinMode(WET_LED_PIN, OUTPUT);
  pinMode(PUMPING_LED_PIN, OUTPUT);
  
  // Ensure pump is off at startup
  digitalWrite(PUMP_PIN, LOW);
  
  // Initial LED test
  ledTest();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Read sensor at regular intervals
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;
    
    int moistureLevel = analogRead(SOIL_SENSOR_PIN);
    
    // Log data to serial monitor
    logData(moistureLevel);
    
    // Update system state with hysteresis logic
    updateIrrigationState(moistureLevel, currentTime);
    
    // Update LED indicators
    updateLEDs(moistureLevel);
  }
  
  // Safety: Stop pump after maximum runtime
  if (isPumping && (currentTime - pumpStartTime >= PUMP_MAX_TIME)) {
    stopPump();
    Serial.println("⚠ Pump stopped: Maximum runtime reached");
  }
}

void updateIrrigationState(int moisture, unsigned long currentTime) {
  // Hysteresis logic prevents rapid on/off cycling
  // FOR CAPACITIVE: Pump ON when moisture LOW (dry), OFF when moisture HIGH (wet)
  if (!isPumping && moisture <= DRY_THRESHOLD) {
    // Soil is dry - start watering
    startPump(currentTime);
  } 
  else if (isPumping && moisture >= WET_THRESHOLD) {
    // Soil is adequately moist - stop watering
    stopPump();
  }
}

void startPump(unsigned long currentTime) {
  isPumping = true;
  pumpStartTime = currentTime;
  digitalWrite(PUMP_PIN, HIGH);
  digitalWrite(PUMPING_LED_PIN, HIGH);
  Serial.println("💧 PUMP ON - Watering started");
}

void stopPump() {
  isPumping = false;
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(PUMPING_LED_PIN, LOW);
  Serial.println("✓ PUMP OFF - Watering stopped");
}

void updateLEDs(int moisture) {
  // Blue LED: Always on when pumping (handled separately)
  // This function only controls dry/wet status LEDs
  // FOR CAPACITIVE: Low values = dry, High values = wet
  
  // Red LED: Soil too dry (LOW moisture value)
  if (moisture <= DRY_THRESHOLD) {
    digitalWrite(DRY_LED_PIN, HIGH);
    digitalWrite(WET_LED_PIN, LOW);
  }
  // Green LED: Soil at optimal moisture (HIGH moisture value)
  else if (moisture >= WET_THRESHOLD) {
    digitalWrite(DRY_LED_PIN, LOW);
    digitalWrite(WET_LED_PIN, HIGH);
  }
  // Between thresholds (hysteresis zone) - dim both
  else {
    // Could blink both LEDs slowly to indicate "in-between" state
    digitalWrite(DRY_LED_PIN, LOW);
    digitalWrite(WET_LED_PIN, LOW);
  }
}

void logData(int moisture) {
  Serial.print("Time: ");
  Serial.print(millis() / 1000);
  Serial.print("s | Moisture: ");
  Serial.print(moisture);
  Serial.print(" | Status: ");
  
  // FOR CAPACITIVE: Low = dry, High = wet
  if (moisture <= DRY_THRESHOLD) {
    Serial.print("DRY");
  } else if (moisture >= WET_THRESHOLD) {
    Serial.print("WET");
  } else {
    Serial.print("MODERATE");
  }
  
  Serial.print(" | Pump: ");
  Serial.println(isPumping ? "ON" : "OFF");
}

void ledTest() {
  // Brief LED test on startup
  Serial.println("Testing LEDs...");
  digitalWrite(DRY_LED_PIN, HIGH);
  digitalWrite(WET_LED_PIN, HIGH);
  digitalWrite(PUMPING_LED_PIN, HIGH);
  delay(500);
  digitalWrite(DRY_LED_PIN, LOW);
  digitalWrite(WET_LED_PIN, LOW);
  digitalWrite(PUMPING_LED_PIN, LOW);
  Serial.println("LED test complete\n");
}
