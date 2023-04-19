#define Fotodiodo A0
#define LED 12
int lightvalue=0;


void setup() {
  pinMode(Fotodiodo,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  lightvalue=(long)(analogRead(Fotodiodo)*255)/1023;
  Serial.println(lightvalue);
  analogWrite(LED, 255 - (lightvalue*3));
  // put your main code here, to run repeatedly:

}
