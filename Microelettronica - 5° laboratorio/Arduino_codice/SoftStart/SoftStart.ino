const int buttonPin = 2; // the number of the pushbutton pin
const int ledPin =  12; // the number of the LED pin

bool buttonState = HIGH; // variable for reading the pushbutton status
int lastButtonState = LOW; // variable for storing the last button state

int timeToFade = 2000; // time in milliseconds to fade from min to max brightness

void setup() {
    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
    // initialize the LED state as low
    analogWrite(ledPin,0);
    Serial.begin(9600);
}

void loop(){
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    Serial.println(buttonState);
    delay(5);
    if(buttonState){ // check if the pushbutton is pressed.
        // if it is, the buttonState is HIGH:
        if (lastButtonState == LOW){
            // turn LED on:
            fade_in(timeToFade);
            lastButtonState = HIGH;
        } else {
            // turn LED off:
            fade_out(timeToFade);
            lastButtonState = LOW;
        }
    }
}

void fade_in(int timeToFade){
    int ledBrightness = 0;
    for (int i = 0; i <= 255; i++) {
        ledBrightness = i;
        analogWrite(ledPin, ledBrightness);
        delay(timeToFade / 255);
    }
}

void fade_out(int timeToFade){
    int ledBrightness = 255;
     for (int i = 255; i >= 0; i--) {
        ledBrightness = i;
        analogWrite(ledPin, ledBrightness);
        delay(timeToFade / 255);
    }
}