#define BUTTON 2
#define LED 12

uint8_t button_state = LOW;
uint8_t reading = LOW;
uint8_t flag_read = LOW;

uint64_t read_time = 0;

int ledState = 0;
int buttonState;       
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;

void setup() 
{
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);

  analogWrite(LED, 0);
}

void loop() 
{

  int reading = digitalRead(BUTTON);
  if (reading != lastButtonState) 
  {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (reading != buttonState) 
    {
      buttonState = reading;
      if (buttonState == HIGH) 
      {
        ledState = !ledState;
        flag_read = HIGH;
      }
    }
  }
  lastButtonState = reading;

  switch(ledState)
  {
    case HIGH:
      if (flag_read)
      {
        flag_read = LOW;
        for (int i = 0; i < 256; i++)
        {        
          analogWrite(LED, i);
          delay(8);
        }
      }
    break;


    case LOW:
       if (flag_read)
       {
         flag_read = LOW;
         for (int i = 0; i < 256; i++)
         {        
           analogWrite(LED, 255-i);
           delay(8);
         }
       }
    break;


    default:

    break;
  }
  
}
