const int ledPin =  13; // the number of the LED pin
const int sensorPin = A0; // the number of the light sensor pin

int edge = 100; 

void setup(){
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}  

void loop(){
    int sensorValue = analogRead(sensorPin);
    int light = map(sensorValue, 0, 1023, 255, 15);
    analogWrite(ledPin, light); 

    Serial.print(sensorValue/1023*100);
    serial.ptintln(" %");
}