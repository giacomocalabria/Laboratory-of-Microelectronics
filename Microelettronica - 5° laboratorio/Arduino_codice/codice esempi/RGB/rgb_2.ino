#define POT A0
#define BRIGHTNESS A1
#define RED 12
#define GREEN 11
#define BLUE 10
#define K1 0.7478005865102

int RedValue=0;
int GreenValue=0;
int BlueValue=0;


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
  uint32_t read_pot = analogRead(POT);
  const float max_brightness = (float)analogRead(BRIGHTNESS)/1023;
  if(read_pot<=341)
  {
    RedValue= 255-(K1*read_pot);
    BlueValue=(K1*read_pot);
    analogWrite(RED, RedValue*max_brightness);
    analogWrite(BLUE,BlueValue*max_brightness);
    Serial.print("RED: ");
    Serial.println(RedValue);
    Serial.print("BLUE: ");
    Serial.println(BlueValue);
  }
  if((read_pot>341) && (read_pot<=682))
  {
    BlueValue=512-(K1*read_pot);
    GreenValue=((K1*read_pot)-255);
    analogWrite(BLUE, BlueValue*max_brightness);
    analogWrite(GREEN,GreenValue*max_brightness);
  }
  if((read_pot>682) && (read_pot<=1023))
  {
    GreenValue=765-(K1*read_pot);
    RedValue=(K1*read_pot)-512;
    analogWrite(GREEN, GreenValue*max_brightness);
    analogWrite(RED,RedValue*max_brightness);
  }
  delay(1);
}
