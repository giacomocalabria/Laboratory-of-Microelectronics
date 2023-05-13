#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>

// Pin per il sensore TMP36
const int temperaturePin = A0;

// Definisce i colori
#define BLUE   0x001F
#define GREEN  0x07E0
#define RED    0xF800
#define BLACK  0x0000
#define WHITE  0xFFFF

// Definisce i limiti della colorbar e le posizioni del cursore
#define MIN_TEMP 20.0
#define MAX_TEMP 30.0
#define COLORBAR_X 30
#define COLORBAR_Y 200
#define COLORBAR_WIDTH 280
#define CURSOR_SIZE 10

// Inizializza il display TFT
#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
  Serial.begin(9600);
  
  // Inizializza il display TFT
  tft.begin();
  tft.setRotation(1);
  
  // Disegna la colorbar
  tft.fillRect(COLORBAR_X, COLORBAR_Y, COLORBAR_WIDTH, CURSOR_SIZE, BLUE);
  tft.fillRect(COLORBAR_X, COLORBAR_Y, COLORBAR_WIDTH / 2, CURSOR_SIZE, GREEN);
  tft.fillRect(COLORBAR_X + COLORBAR_WIDTH / 2, COLORBAR_Y, COLORBAR_WIDTH / 2, CURSOR_SIZE, RED);
  
  // Scrive i valori delle temperature estreme
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(COLORBAR_X, COLORBAR_Y + CURSOR_SIZE);
  tft.print(MIN_TEMP);
  tft.setCursor(COLORBAR_X + COLORBAR_WIDTH - 20, COLORBAR_Y + CURSOR_SIZE);
  tft.print(MAX_TEMP);
}

void loop() {
  // Legge il valore della temperatura
  int sensorValue = analogRead(temperaturePin);
  
  // Converte il valore analogico in gradi Celsius
  float voltage = sensorValue * 3.3 / 4095; // Converte in tensione (3.3V è la tensione di riferimento)
  float temperature = (voltage - 0.5) * 100; // Converte in gradi Celsius (il sensore fornisce 10mV/°C)
  
  // Limita la temperatura tra i valori minimi e massimi
  temperature = constrain(temperature, MIN_TEMP, MAX_TEMP);
  
  // Calcola la posizione del cursore sulla colorbar
  int cursorPosition = map(temperature, MIN_TEMP, MAX_TEMP, COLORBAR_X, COLORBAR_X + COLORBAR_WIDTH - CURSOR_SIZE);
  
  // Pulisce l'area del cursore
  tft.fillRect(COLORBAR_X, COLORBAR_Y + CURSOR_SIZE + 5, COLORBAR_WIDTH, 20, BLACK);
  
  // Disegna il cursore
  tft.fillRect(cursorPosition, COLORBAR_Y + CURSOR_SIZE + 5, CURSOR_SIZE, 20, WHITE);

  // Scrive il valore della temperatura
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.setTextColor(WHITE);
  tft.print("Temperatura: ");
}
