// LM35 + Relay Control
const int TEMP_PIN = A0;  // LM35 Vout
const int RELAY_PIN = 12;  // Relay module
const int LED = 13;

// Temperature threshold
const float T_ON = 25.0;  // °C: turn relay ON above this
const int SAMPLES = 10;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // ensure relay OFF initially
  analogWrite(LED, LOW);
  Serial.begin(9600);
}

void loop() {
  // --- Average ADC readings ---
  long acc = 0;
  for (int i = 0; i < SAMPLES; i++) {
    acc += analogRead(TEMP_PIN);
    delay(5);
  }
  float raw = acc / (float)SAMPLES;
  // Serial.println(raw);

  // --- Convert to Celsius ---
  float voltage = raw * (5.0 / 1023.0);  // ADC to volts
  float tempC = voltage * 100.0;         // LM35: 10mV/°C

  // --- Relay control ---
  if (tempC >= T_ON) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn relay ON
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn relay OFF
    digitalWrite(LED, LOW);
  }

  // --- Debug ---
  Serial.print("Temp: ");
  Serial.print(tempC, 1);
  Serial.print(" °C | Relay: ");
  Serial.println(tempC >= T_ON ? "ON" : "OFF");

  delay(200);
}
