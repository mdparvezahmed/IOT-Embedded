#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>


// Width & height for 128x32 OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


#define SOIL_PIN A0


// Create display object (I2C address 0x3C is common)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Try 0x3D if this fails
    Serial.println(F("OLED failed"));
    for (;;)
      ;  // Don't continue
  }

  display.clearDisplay();
  display.setTextSize(1);  // Size 1 = small font
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Smart Farming");
  display.display();
  delay(2000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int soil = analogRead(SOIL_PIN);

  int soilPercent = map(soil, 1023, 0, 0, 100);
  display.clearDisplay();
  display.setCursor(0, 1);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Temp:");
  display.print(t);
  display.print("C H:");
  display.print(h);
  display.print("%");
  display.display();


  display.setCursor(0, 16);
  display.print("Soil:");
  display.print(soilPercent);
  display.print("%");
  display.display();
  delay(2000);

}
