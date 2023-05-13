#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>
#include <SPI.h>

#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST, TFT_CLK, TFT_RST, TFT_MISO);

#define buttonPin 2

int buttonState = HIGH;
int lastButtonState = HIGH;

unsigned long startTime = 0;
unsigned long elapsedTime = 0;

int stato = 0;

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(HX8357_BLACK);
  tft.setTextColor(HX8357_WHITE);
  tft.setTextSize(2);
  
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  switch (stato) {
    case 0:
      if (buttonState == LOW && lastButtonState == HIGH) {
        // Button pressed, start measuring time
        stato = 1;
        startTime = millis();
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(50, 100);
        tft.print("Press to Start");
      }
      break;
      
    case 1:
      if (buttonState == HIGH && lastButtonState == LOW) {
        // Button released, stop measuring time
        stato = 2;
        elapsedTime = millis() - startTime;
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(50, 100);
        tft.print("Release to Stop");
      }
      break;
      
    case 2:
      if (buttonState == LOW && lastButtonState == HIGH) {
        // Button pressed, reset timer and go back to state 0
        stato = 0;
        tft.fillScreen(HX8357_BLACK);
        tft.setCursor(50, 100);
        tft.print("Press to Reset");
      }
      break;
  }
  
  lastButtonState = buttonState;
  
  if (stato == 1) {
    // Update timer display every 50ms
    unsigned long currentTime = millis();
    if (currentTime - startTime >= 50) {
      startTime = currentTime;
      updateTimerDisplay();
    }
  }
}

void updateTimerDisplay() {
  unsigned long centiseconds = (millis() - startTime) / 10;
  unsigned long seconds = centiseconds / 100;
  centiseconds %= 100;
  
  tft.fillScreen(HX8357_BLACK);
  tft.setCursor(100, 100);
  tft.print(String(seconds));
  tft.print(".");
  if (centiseconds < 10) {
    tft.print("0");
  }
  tft.print(String(centiseconds));
}
