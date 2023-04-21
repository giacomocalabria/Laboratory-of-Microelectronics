int RedLedPin = 12; // Red LED is connected to digital pin 12
int GreenLedPin = 11; // Green LED is connected to digital pin 11
int BlueLedPin = 10;  // Blue LED is connected to digital pin 10

int PotPin = A0; // Potentiometer for RGB control is connected to analog pin A0
int LuxPin = A2; // Potentiometer for brightness control is connected to analog pin A0  

int RedLedBrightness = 0; // Red LED brightness
int GreenLedBrightness = 0; // Green LED brightness
int BlueLedBrightness = 0; // Blue LED brightness

int Brightness = 0;

int K = 0.7478;

void setup(){
    pinMode(RedLedPin, OUTPUT); // Set Red LED pin as output
    pinMode(GreenLedPin, OUTPUT);   // Set Green LED pin as output
    pinMode(BlueLedPin, OUTPUT);    // Set Blue LED pin as output
    Serial.begin(9600);
}

void loop(){
    int PotValue = analogRead(PotPin); // Read potentiometer value

    if(PotValue == 0){
        RedLedBrightness = 255;
        GreenLedBrightness = 0;
        BlueLedBrightness = 0;
    } 
    
    
    else if(PotValue < 341){
        RedLedBrightness = 255 - PotValue*0.7478;
        GreenLedBrightness = 0;
        BlueLedBrightness = PotValue*0.7478;
    } 
    
    
    else if(PotValue < 682){
        RedLedBrightness = 0;
        GreenLedBrightness = PotValue*0.7478 - 255;
        BlueLedBrightness = 510 - PotValue*0.7478;
    } 
    
    
    else if(PotValue < 1023){
        RedLedBrightness = PotValue*0.7478 - 510;
        GreenLedBrightness = 765 - PotValue*0.7478;
        BlueLedBrightness = 0;
    } 
    
    
    else {
        RedLedBrightness = 255;
        GreenLedBrightness = 0;
        BlueLedBrightness = 0;
    }

    int LuxValue = analogRead(LuxPin); // Read potentiometer value

    Brightness = map(LuxValue, 0, 1023, 0, 100); // Scale brightness to LuxValue

    RedLedBrightness = RedLedBrightness * Brightness /100;
    GreenLedBrightness = GreenLedBrightness * Brightness /100;
    BlueLedBrightness =  BlueLedBrightness * Brightness /100;

    // Set LED brightness
    analogWrite(RedLedPin, RedLedBrightness); 
    analogWrite(GreenLedPin, GreenLedBrightness);
    analogWrite(BlueLedPin, BlueLedBrightness);

    /*Serial.print("Valore potenziometro rgb ");
    Serial.println(PotValue);
    Serial.print("Valore potenziometro lux ");
    Serial.println(Brightness);
    Serial.print("RED: ");
    Serial.println(RedLedBrightness);
    Serial.print("GREEN: ");
    Serial.println(GreenLedBrightness);
    Serial.print("BLUE: ");
    Serial.println(BlueLedBrightness);*/
    delay(1);
    
}