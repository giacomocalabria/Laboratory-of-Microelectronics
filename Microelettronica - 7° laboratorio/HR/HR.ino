#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

#define sensorPin A0
#define PinIR 6
#define PinRED 7
#define TFT_CS 10
#define TFT_DC 9

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC,-1); 

const int displayWidth = 480;
const int arraySize = displayWidth;
const int graphHeight = 200;
const int sampleInterval = 20;

int acquire[arraySize];

void setup(){
  Serial.begin(9600);
    pinMode(PinIR,OUTPUT);
    pinMode(PinRED,OUTPUT);
    analogReadResolution(12); // 12 bit ADC -> 4096 values

    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(HX8357_BLACK);
    tft.setTextSize(3);
    tft.setCursor(30, graphHeight);
    tft.setTextColor(HX8357_WHITE);
    tft.println("Heart Rate Monitor");
    
    digitalWrite(PinRED,HIGH);

    tft.setCursor(30, 240);
    tft.setTextColor(HX8357_WHITE);
    tft.print("Inizio misurazione ...");    delay(1000);    
    tft.print("3"); delay(1000);    
    tft.print("2"); delay(1000);    
    tft.print("1"); delay(1000);
    tft.fillRect(0, 240, displayWidth, 80, HX8357_BLACK);

    acq();
    digitalWrite(PinRED,LOW);

    tft.setCursor(30, 240);
    tft.print("Scalamento della misurazione ...");
    
    plot_array_scaled();
    tft.fillRect(0, 240, displayWidth, 80, HX8357_BLACK);

    findBPM(acquire);

    float O2 = findO2(acquire);
    tft.setCursor(30, 280);
    tft.print("O2: ");
    tft.print(O2);
}

void loop(){
}

void acq(){
    unsigned long currentMillis = 0;
    acquire[0] = analogRead(sensorPin);
    tft.fillRect(0, 0, displayWidth, graphHeight, HX8357_BLACK);
    for(int i = 1; i < arraySize; i++){
        acquire[i] = analogRead(sensorPin);
        currentMillis = millis();
        tft.drawLine(i-1,map(acquire[i-1], 1000, 4095, 0, graphHeight),i,map(acquire[i], 0, 4095, 0, graphHeight), HX8357_WHITE);
        while(millis() < currentMillis + sampleInterval);
    }
}

void plot_array_scaled(){
    rescale();
    tft.fillRect(0, 0, displayWidth, graphHeight, HX8357_BLACK);
    for(int i = 1; i < arraySize; i++){
        tft.drawLine(i-1, acquire[i-1],i,acquire[i], HX8357_WHITE);
    }
}

void rescale( ){
    int max = findmax(acquire);
    int min = findmin(acquire);

    for(int i = 0; i < arraySize; i++){
        acquire[i] = map(acquire[i], min, max, 0, graphHeight);
    }
}

int findmax(int array[]){
    int max = array[0];
    for(int i = 0; i < arraySize; i++){
        if(array[i] > max)  max = array[i];
    }
    return max;
}

int findmin(int array[]){
    int min = array[0];
    for(int i = 0; i < arraySize; i++){
        if(array[i] < min)  min = array[i];
    }
    return min;
}

int mean(int array[]){
    int sum = 0;
    for(int i = 0; i < arraySize; i++){
        sum += array[i];
    }
    return sum / arraySize;
}

int findBPM(int array[]){
    int max = findmax(array);
    Serial.print(" MAX= ");
    Serial.println(max);
    int min = findmin(array);
    Serial.print(" MIN= ");
    Serial.println(min);
    int avg = mean(array);
    Serial.print(" AVG= ");
    Serial.println(avg);
    int threshold = avg - 20;
    //int threshold = (max - min) / 1.5 + min;
    Serial.print("Soglia = ");
    Serial.println(threshold);
    Serial.print("Soglia = ");
    Serial.println((max - min) / 1.5 + min);
    int peaks = 0;
    int timeOfPeaks[arraySize/2];
    for(int i = 0; i < arraySize; i++){
        if(array[i] > threshold){
            // Serial.println("Picco");
            timeOfPeaks[peaks] = i;
            peaks++;
            i+=2;
            while(array[i] > threshold){
                i++;
            }
        }
    }
    Serial.print("Ho contato: ");
    Serial.println(peaks);

    int FirstPeaks = timeOfPeaks[0] * 20;
    int LastPeaks = timeOfPeaks[peaks-1] * 20;

    Serial.print("Intervallo tempo= ");
    Serial.println(LastPeaks - FirstPeaks);

    float bpm = peaks / ((LastPeaks - FirstPeaks)/1000.0);
    Serial.print("Battiti al secondo: ");
    Serial.println(bpm);
    int bpm2 = bpm * 60;

    Serial.print("Battiti al minuto: ");
    Serial.println(bpm2);

    tft.setCursor(30, 240);
    tft.print("BPM: ");
    tft.print(bpm2);

    threshold = map(threshold, min, max, graphHeight, 0);

    Serial.print("Soglia = ");
    Serial.println(threshold);

    tft.drawLine(0,threshold ,displayWidth,threshold ,HX8357_RED);

    return bpm;
}

float findO2(int array[]){
    int samples = 1000;
    int IR[samples];
    int RED[samples];
    digitalWrite(PinIR,HIGH);
    delay(250);
    for(int i = 0; i < samples; i++){
        IR[i] = analogRead(sensorPin);
        delay(1);
    }
    digitalWrite(PinIR,LOW);
    delay(100);
    digitalWrite(PinRED,HIGH);
    delay(250);
    for(int i = 0; i < samples; i++){
        RED[i] = analogRead(sensorPin);
        delay(1);
    }
    digitalWrite(PinRED,LOW);

    int IRmax = findmax(IR) * 3.3 / 4095;
    int IRmin = findmin(IR) * 3.3 / 4095;
    int REDmax = findmax(RED) * 3.3 / 4095;
    int REDmin = findmin(RED) * 3.3 / 4095; 

    float R = ((REDmax - REDmin)/REDmin) / ((IRmax - IRmin) / IRmin);
    Serial.println(R);
    float O2 = 97.94 + 1.15 * R;

    return O2;
}