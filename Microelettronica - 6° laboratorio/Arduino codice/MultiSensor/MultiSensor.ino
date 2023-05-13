#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>
#include <SPI.h>
#include <Wire.h>

#define DEV_ID 0x48
#define DEV_ID2 0x39

#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST, TFT_CLK, TFT_RST, TFT_MISO);

void setup(){
    analogReadResolution(12);

    Serial.begin(9600);

    Wire.begin();

    // *** Configurazione del sensore di temperatura digitale DS1621 ***
    Wire.beginTransmission(DEV_ID);
    Wire.write(0xAC);
    Wire.write(0x02);
    Wire.endTransmission();

    Wire.beginTransmission(DEV_ID);
    Wire.write(0xEE);
    Wire.endTransmission();

    // *** Configurazione del sensore di luce digitale TSL2561 ***
    Wire.beginTransmission(DEV_ID2);
    Wire.write(0x00);
    Wire.write(0x03);
    Wire.endTransmission();

    Wire.beginTransmission(DEV_ID2);
    Wire.write(0x81);
    Wire.write(0x02);
    Wire.endTransmission();

}

void loop() {

}



/*
    Lettura della temperatura dal sensore analogico TMP36
*/

int AnalogTemperature(int pin) {
    float analogValue = analogRead(pin);
    float temperatura = (analogValue - 155) *330.0/4095.0; // Usiamo DAC a 12 bit -> 4096 valori
    return temperatura;
}

/*
    Lettura della temperatura dal sensore digitale di temperatura DS1621
*/

int DigitalTemperature(){
    int firstByte;
    int secondByte;
    float temp = 0;

    Wire.beginTransmission(DEV_ID);
    Wire.write(0xAA); // Temperature register   
    Wire.endTransmission();
    Wire.requestFrom(DEV_ID, 2); // request 2 bytes from slave device

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

int AnalogHumidity(int pin) {
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

    Wire.beginTransmission(DEV_ID2);
    Wire.write(0x8C); // Temperature register
    Wire.endTransmission();
    Wire.requestFrom(DEV_ID2, 1);

    firstByte = Wire.read(); // read first byte

    Wire.beginTransmission(DEV_ID2);
    Wire.write(0x8D); // Temperature register
    Wire.endTransmission();
    Wire.requestFrom(DEV_ID2, 1);

    secondByte = Wire.read(); // read second byte

    lux = 256 * int(secondByte) + int(firstByte); // convert the two bytes to int
    return lux;
}