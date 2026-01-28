#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Pin definitions
const int tempPin = A0;      // LM35
const int turbidityPin = A1;
const int buzzerPin = 8;
const int relayPin = 9;

// Thresholds
const float TEMP_LIMIT = 35.0;     // °C
const int TURBID_LIMIT = 600;      // Adjust in Proteus

void setup() {
  lcd.begin(16, 2);

  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(relayPin, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Water Quality");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read LM35
  int tempValue = analogRead(tempPin);
  float voltage = tempValue * (5.0 / 1023.0);
  float temperature = voltage * 100;   // LM35 scale

  // Read turbidity
  int turbidity = analogRead(turbidityPin);

  // Display values
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Turb:");
  lcd.print(turbidity);
  lcd.print("   ");

  // Water quality logic
  if (temperature > TEMP_LIMIT || turbidity > TURBID_LIMIT) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(relayPin, HIGH);   // Cut / control water
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
  }

  delay(1000);
}