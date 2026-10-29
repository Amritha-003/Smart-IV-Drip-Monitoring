/*
  Smart IV Drip Monitoring — Arduino prototype
  Hardware demo only; not a certified medical device.

  Example wiring:
  - Analog light/level sensor output -> A0
  - Alert LED -> D7 through a suitable resistor
  - Buzzer -> D8 (use a driver transistor if required by your buzzer)
  
  Calibrate LOW_LEVEL_THRESHOLD for your sensor and setup.
  This prototype detects a change in sensor reading; it does not measure
  medical-grade flow or guarantee that an IV bag is empty.
*/

const int sensorPin = A0;
const int ledPin = 7;
const int buzzerPin = 8;

// Adjust after testing your sensor. Readings are typically 0–1023.
const int LOW_LEVEL_THRESHOLD = 400;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.print("Sensor reading: ");
  Serial.println(sensorValue);

  // Depending on sensor orientation, you may need to reverse this comparison.
  bool lowLevelDetected = sensorValue < LOW_LEVEL_THRESHOLD;

  if (lowLevelDetected) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);
    Serial.println("ALERT: Low-level condition detected");
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    Serial.println("Status: Normal sensor reading");
  }

  delay(500);
}
