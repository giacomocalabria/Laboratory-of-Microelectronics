int seg [7]={12,11,10,9,8,7,6};
int tmp = 0;
int readTime = 0;
bool digits[10][7]{
  {1,1,1,1,1,1,0},//0
  {0,1,1,0,0,0,0},//1
  {1,1,0,1,1,0,1},//2
  {1,1,1,1,0,0,1},//3
  {0,1,1,0,0,1,1},//4
  {1,0,1,1,0,1,1},//5
  {1,0,1,1,1,1,1},//6
  {1,1,1,0,0,0,0},//7
  {1,1,1,1,1,1,1},//8
  {1,1,1,1,0,1,1}//9
};

void setup() {
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  for(int i=0;i<7;i++){
    Serial.println(i);
    digitalWrite(seg[i],digits[tmp][i]);
  }
  if((millis()-readTime)>=1000)
  {
    tmp++;
    Serial.println(tmp);
    if (tmp>9){
      tmp=0;
    }
    readTime=millis();
  }
  
  Serial.println(tmp);
}
