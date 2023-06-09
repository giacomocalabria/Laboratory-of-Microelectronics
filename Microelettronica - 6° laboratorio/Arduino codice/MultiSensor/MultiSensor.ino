#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

#define TEMP_DEV_ID 0x48
#define LIGHT_DEV_ID 0x39

#define HUMIDITY_DEV_PIN A1
#define TEMP_PIN A0

#define TFT_CS 10
#define TFT_DC 9

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, -1); 
// TFT_RST set to -1 to tie it to Arduino's reset

#define buttonPin 2

bool pulsante_precedente_alto = false;
bool stateButton = LOW;

int stato = 0;
int stato_precedente = 9;
float temeperatura_precedente_analog;

void setup(){
    analogReadResolution(12);
    Wire.begin();

    // Configurazione del sensore di temperatura digitale DS1621
    Wire.beginTransmission(TEMP_DEV_ID);
    Wire.write(0xAC);
    Wire.write(0x02);
    Wire.endTransmission();

    Wire.beginTransmission(TEMP_DEV_ID);
    Wire.write(0xEE);
    Wire.endTransmission();

    // Configurazione del sensore di luce digitale TSL2561
    Wire.beginTransmission(LIGHT_DEV_ID);
    Wire.write(0x00);
    Wire.write(0x03);
    Wire.endTransmission();

    Wire.beginTransmission(LIGHT_DEV_ID);
    Wire.write(0x81);
    Wire.write(0x02);
    Wire.endTransmission();

    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(HX8357_BLACK);
    tft.setTextSize(5);

    attachInterrupt(digitalPinToInterrupt(2),change_state,RISING);
}

void change_state(){
  stato++;
  if(stato >= 4)
    stato = 0;
}

void loop(){
    switch(stato){
        case 0:{
            if (stato != stato_precedente) {
              tft.fillScreen(HX8357_BLACK);
              tft.setCursor(30,60);
              tft.println("Temperatura 1");
            }
            float temp = AnalogTemperature(TEMP_PIN);
            String txt = String(temp);
            tft.setCursor(60,120);
            tft.fillRect(60,120,480,320, HX8357_BLACK);
            tft.println(txt + " C");
            stato_precedente = 0;
        }
        break;
        case 1:{
            if (stato != stato_precedente) {
              tft.fillScreen(HX8357_BLACK);
              tft.setCursor(30,60);
              tft.println("Temperatura 2");
            }
            float temp = DigitalTemperature();
            String txt = String(temp);
            tft.setCursor(60,120);
            tft.fillRect(60,120,480,320, HX8357_BLACK);
            tft.println(txt + " C");
            stato_precedente = 1;
        }
        break;
        case 2:{
            if(stato != stato_precedente) {
              tft.fillScreen(HX8357_BLACK);
              tft.setCursor(30,60);
              tft.println("Luminanza");
            }
        
            int lux = DigitalLight();
            String txt = String(lux);
            tft.setCursor(60,120);
            tft.fillRect(60,120,480,320, HX8357_BLACK);
            tft.println(txt + " lux");
            stato_precedente = 2;
        }
        break;
        case 3:{
            if (stato != stato_precedente) {
              tft.fillScreen(HX8357_BLACK);
              tft.setCursor(30,60);
              tft.println("Humidity");
            }
            float hum = AnalogHumidity(HUMIDITY_DEV_PIN);
            String txt = String(hum);
            tft.setCursor(60,120);
            tft.fillRect(60,120,480,320, HX8357_BLACK);
            tft.println(txt + " %");
            stato_precedente = 3;
        }
    }
    delay(500);
}



/*
    Lettura della temperatura dal sensore analogico TMP36
*/

float AnalogTemperature(int pin) {
  float analogValue = analogRead(pin);
  float temperature = ((analogValue * (3.3/4095.0)) - 0.5) / 0.01;  //OK
  return temperature;
}

/*
    Lettura della temperatura dal sensore digitale di temperatura DS1621
*/

float DigitalTemperature(){
    int firstByte;
    int secondByte;
    float temp = 0;

    Wire.beginTransmission(TEMP_DEV_ID);
    Wire.write(0xAA); // Temperature register   
    Wire.endTransmission();
    Wire.requestFrom(TEMP_DEV_ID, 2); // request 2 bytes from slave device

    firstByte = Wire.read(); // read first byte
    secondByte = Wire.read(); // read second byte

    temp = firstByte;

    if(secondByte){
        temp += 0.5; 
    }

    return temp;
}

/*
    Lettura dal sensore di umidità analogico HIH-5030-001, Honeywell
*/

float AnalogHumidity(int pin) {
    float analogValue = analogRead(pin);
    float rhvoltage = (analogValue/4095.0)*3.3; // Usiamo DAC a 12 bit -> 4096 valori
    float umidita = ((rhvoltage/3.3)-0.1515)/0.00636; // Formula dal datasheet del sensore di umidità analogico 
    umidita = umidita/(1.0546-0.00216*AnalogTemperature(A0)); // Correzione temperatura umidità relativa (formula dal datasheet)
    return umidita;
}

/*
    Lettura dal sensore di luce digitale TSL2561
*/

int DigitalLight(){
    byte firstByte, secondByte;
    int lux = 0;

    Wire.beginTransmission(LIGHT_DEV_ID);
    Wire.write(0x8C); // Temperature register
    Wire.endTransmission();
    Wire.requestFrom(LIGHT_DEV_ID, 1);

    firstByte = Wire.read(); // read first byte

    Wire.beginTransmission(LIGHT_DEV_ID);
    Wire.write(0x8D); // Temperature register
    Wire.endTransmission();
    Wire.requestFrom(LIGHT_DEV_ID, 1);

    secondByte = Wire.read(); // read second byte

    lux = 256 * int(secondByte) + int(firstByte); // convert the two bytes to int
    return lux;
}
