#define POT A0
#define BRIGHTNESS A1
#define RED 12
#define GREEN 11
#define BLUE 10
#define K1 0.7478005865102


void setup() 
{
  pinMode(POT, INPUT);
  pinMode(BRIGHTNESS, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  uint32_t read_pot = (long)(analogRead(POT);
  uint32_t max_brightness = (long)(analogRead(BRIGHTNESS));
  if(read_pot<=341)
  {
    analogWrite(RED, 255-(K1*read_pot));
    analogWrite(BLUE, (K1*read_pot));
  }
  if((read_pot>341) && (read_pot<=682))
  {
    analogWrite(BLUE, 512-(K1*read_pot));
    analogWrite(GREEN,(K1*read_pot)-255);
  }
  if((read_pot>682) && (read_pot<=1023))
  {
    analogWrite(GREEN, 765-(K1*read_pot));
    analogWrite(RED,(K1*read_pot)-512);
    Serial.println((K1*read_pot)-512);
  }
  delay(1);
}
