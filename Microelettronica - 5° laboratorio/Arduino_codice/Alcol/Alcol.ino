const int alcolPin = A0;

const int matrixPin[10] = {12,11,10,9,8,7,6,5,4,3};

void setup(){
    for(int i = 0; i < 10; i++){
        pinMode(matrixPin[i], OUTPUT);
        digitalWrite(matrixPin[i], LOW);
    }
    Serial.begin(9600);
}

void loop(){
    int alcolValue = analogRead(alcolPin);
    Serial.println(alcolValue);
    delay(1);
    int alcolValue2 = map(alcolValue, 940, 990, 0, 9);
    for(int i = 0; i < 10; i++){
        if(i < alcolValue2){
            digitalWrite(matrixPin[i], HIGH);
        }else{
            digitalWrite(matrixPin[i], LOW);
        }
    }
}