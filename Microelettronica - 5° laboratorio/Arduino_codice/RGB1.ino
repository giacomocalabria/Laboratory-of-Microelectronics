int RedLedPin = 12; // Red LED is connected to digital pin 12
int GreenLedPin = 11; // Green LED is connected to digital pin 11
int BlueLedPin = 10;  // Blue LED is connected to digital pin 10

void setup(){
    pinMode(RedLedPin, OUTPUT); // Set Red LED pin as output
    pinMode(GreenLedPin, OUTPUT);   // Set Green LED pin as output
    pinMode(BlueLedPin, OUTPUT);    // Set Blue LED pin as output
    
    digitalWrite(RedLedPin, HIGH); // Turn on Red LED
    digitalWrite(GreenLedPin, HIGH); // Turn on Green LED
    digitalWrite(BlueLedPin, HIGH); // Turn on Blue LED
}

void loop(){
}