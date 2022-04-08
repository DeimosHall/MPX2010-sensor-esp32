#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define sensor 33
double voltage = 0, pressure = 0;

void setup() {
  pinMode(sensor,INPUT);
  Serial.begin(115200);
  Serial.println("Connection started");

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
}

void loop() {
  voltage = analogRead(sensor) * 3.3 / 4095;
  pressure = voltage * 10 / 3.3;
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 0);
  display.println("Pressure");
  display.display();

  display.setCursor(15, 30);
  display.println(pressure);
  display.display();
  
  display.setCursor(80, 30);
  display.println("kPa");
  display.display();
  delay(100);
}
