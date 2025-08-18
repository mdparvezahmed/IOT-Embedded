// LM35 + TIP122 PWM fan control

const int TEMP_PIN = A0;    // LM35 Vout
const int PWM_PIN  = 9;     // TIP122 base 
const int LED      = 13;

// Temperature thresholds
const float T_MIN = 20.0;   // °C: fan OFF below this
const float T_MAX = 30.0;   // °C: fan FULL speed at/above this

// Averaging
const int SAMPLES = 10;

void setup() {
  pinMode(PWM_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  analogWrite(PWM_PIN, 0);  // start with fan OFF
  Serial.begin(9600);
}

void loop() {
  // --- Average ADC readings for stability ---
  long acc = 0;
  for (int i = 0; i < SAMPLES; i++) {
    acc += analogRead(TEMP_PIN);
    delay(5);
  }
  float raw = acc / (float)SAMPLES;

  // --- Convert to Celsius ---
  float voltage = raw * (5.0 / 1023.0); // ADC to volts
  float tempC = voltage * 100.0;        // LM35: 10mV/°C

  // --- Map temperature to PWM ---
  float ratio = (tempC - T_MIN) / (T_MAX - T_MIN);
  Serial.print("Speed increase ratio: ");
  Serial.println(ratio);
  if (ratio < 0) ratio = 0;
  if (ratio > 1) ratio = 1;
  int pwm = (int)(ratio * 255.0);

  // --- Apply kick-start only if above threshold ---
  if (pwm > 0) {
    if (pwm < 60) pwm = 60;
    digitalWrite(LED, HIGH);
  } else {
    pwm = 0; // force OFF below T_MIN
    digitalWrite(LED, LOW);
  }

  analogWrite(PWM_PIN, pwm);

  // --- Debugging ---
  Serial.print("Temp: ");
  Serial.print(tempC, 1);
  Serial.print(" °C | PWM: ");
  Serial.println(pwm);

  delay(200);
}
