int RedLedPin = 12; // Red LED is connected to digital pin 12
int GreenLedPin = 11; // Green LED is connected to digital pin 11
int BlueLedPin = 10;  // Blue LED is connected to digital pin 10

int PotPin = A0; // Potentiometer for RGB control is connected to analog pin A0
int LuxPin = A1; // Potentiometer for brightness control is connected to analog pin A0  

int RedLedBrightness = 0; // Red LED brightness
int GreenLedBrightness = 0; // Green LED brightness
int BlueLedBrightness = 0; // Blue LED brightness

int K = 0.75;

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
    } else if(PotValue < 341){
        RedLedBrightness = 255 - PotValue*K;
        GreenLedBrightness = 0;
        BlueLedBrightness = PotValue*K;
    } else if(PotValue < 682){
        RedLedBrightness = 0;
        GreenLedBrightness = 512 - PotValue*K;
        BlueLedBrightness = PotValue*K - 255;
    } else if(PotValue < 1023){
        RedLedBrightness = PotValue*K - 512;
        GreenLedBrightness = 765 - PotValue*K;
        BlueLedBrightness = 0;
    } else {
        RedLedBrightness = 255;
        GreenLedBrightness = 0;
        BlueLedBrightness = 0;
    }

    int LuxValue = analogRead(LuxPin); // Read potentiometer value

    Brightness = Brightness * LuxValue / 1023; // Scale brightness to LuxValue

    // Set LED brightness
    analogWrite(RedLedPin, RedLedBrightness * Brightness); 
    analogWrite(GreenLedPin, GreenLedBrightness * Brightness);
    analogWrite(BlueLedPin, BlueLedBrightness * Brightness);

    if(Serial.available()){
        Serial.print("RED: ");
        Serial.println(RedLedBrightness);
        Serial.print("GREEN: ");
        Serial.println(GreenLedBrightness);
        Serial.print("BLUE: ");
        Serial.println(BlueLedBrightness);
        delay(1);
    }
}