#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define i2_adrr 0x3c
#define columns 128
#define rows 64
const int btn_1 = 27;
bool etat = false;

Adafruit_SSD1306 display(columns, rows, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, i2_adrr)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  pinMode(btn_1, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(btn_1) == LOW) {
    etat = !etat;
  }
  if (etat == true) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("le btn est appuyer");
    display.display();
      } else {
    display.stopscroll();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 30);
    display.print("le btn pas appuyer");
    display.display();
  }
}
