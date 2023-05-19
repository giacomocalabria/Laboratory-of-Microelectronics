#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

#define TFT_CS 10
#define TFT_DC 9

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC,-1); 
// TFT_RST set to -1 to tie it to Arduino's reset

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(HX8357_BLACK);
  tft.setTextColor(HX8357_BLUE);
  tft.setTextSize(5);
  tft.println("**Arduino  DUE**");
  tft.println(" ");
  tft.setTextColor(HX8357_GREEN);
  tft.println("  Display LCD");
  tft.println("   e sensori");
  tft.println(" ");
  tft.setTextColor(HX8357_RED);
  tft.println("  -Gruppo A6-  ");
  tft.setTextColor(HX8357_WHITE);
  tft.println(" ");
  tft.println("Giacomo, Daniele");

}

void loop() {
  // put your main code here, to run repeatedly:

}
