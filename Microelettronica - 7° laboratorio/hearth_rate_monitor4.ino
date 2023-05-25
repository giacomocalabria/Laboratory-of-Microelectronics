//librerie per configurazione e connessione ad Adafruit
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

//connessione ad Adrafuit
#define TFT_CS 10  //chip select
#define TFT_DC 9   //data carry

//creo una istanza di Adafruit
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, -1);
// TFT_RST set to -1 to tie it to Arduino’s reset

//il segnale che arriva ad arduino va connesso a un pin analogico
int const pulsazione = A0;

//array, risoluzione schermo Adrafuit: 320x480
int array[320];

//per fare in modo che riempia l'array una sola volta, si può fare in modo migliore?
bool presi_valori == LOW;

//per riscalare l'array
int max, min, 

void setup() {
  //inizializzazione Adrafuit
  tft.begin();
  tft.setRotation(3); //Orientamento orizzontale
  tft.fillScreen(HX8357_BLACK); 

}

void loop() {
    //faccio in modo che l'array venga compilato una sola volta, compila l'array
    if (presi_valori == LOW){
      for(int i=0; i<320; i++){
        array[i]=analogRead(pulsazione);
        delay(20);
      }
      presi_valori = HIGH;
    }

    //DA QUI IN POI TUTTO VIENE CONTINUAMENTE ESEGUITO A OGNI LOOP <-- METTERE UNA FLAG DI STOP SE FASTIDIOSO
    //stampa l'array (prima del rescale)
    plotarray();

    //ri-scalo l'array in modo da visualizzarlo nella metà superiore
    max = findmax(array);
    min = findmin(array);
    rescalearray();

    delay(800); //è solo per farmi vedere che cosa c'era nello schermo durante la prima parte del programma, si può togliere

    //pulisco lo schermo
    tft.fillScreen(HX8357_BLACK); 
    //disegno il nuovo grafico (dopo il rescale)
    plotarray(array);
  }
}

//trova il max dell'array
int max = findmax(int data[]){
  int maxVal = data[0];
  for (int i = 0; i < 320; i++) {
      if (data[i] > maxVal) {
         maxVal = data[i];
      }
  }
}

//trova il minimo dell'array
int min = findmin(int data[]){
  for (int i = 0; i < 320; i++) {
    int minVal = data[0];
    if (data[i] < minVal) {
         minVal = myArray[i];
      }
  }
}

//riscala i valori dell'array (LAVORA CON VARIABILI GLOBALI)
void rescalearray(){
  for (int i = 0; i < 320; i++) {
      //map(value, fromLow, fromHigh, toLow, toHigh)
      // value: the number to map.  fromLow: the lower bound of the value’s current range. fromHigh: the upper bound of the value’s current range. 
      // toLow: the lower bound of the value’s target range. toHigh: the upper bound of the value’s target range.
      array[i] = map(array[i], min, max, 0, 160); //metà schermo è 160
      }
}
void plotarray()
  for (int i = 0; i < 320; i++) {
    //tft.drawLine(x0, y0, x1, y1, color)
      //x0:coordinata x punto di partenza
      //y0:coordinata y punto di partenza
      //x1:coordinata x punto di arrivo
      //y1:coordinata y punto di arrivo
      //cosa succede all'inizio? da dove parte la linea??
      tft.drawLine(i-1,array[i-1],i,array[i]); //lo dovrebbe fare automaticamente nella metà superiore dello schermo
      }