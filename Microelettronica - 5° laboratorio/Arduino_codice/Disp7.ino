int segPin[7] = {12,11,10,9,8,7,6}; // pins for the 7 segments

bool numbers[10][7] = {
    {1,1,1,0,1,1,1}, // 0
    {1,0,0,0,1,0,0}, // 1
    {1,1,0,1,0,1,1}, // 2
    {1,1,0,1,1,1,0}, // 3
    {1,0,1,1,1,0,0}, // 4
    {0,1,1,1,1,1,0}, // 5
    {0,1,1,1,1,1,1}, // 6
    {1,1,0,0,1,0,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,1,1,0}  // 9
};

void setup(){
    for(int i=0; i<7; i++){
        pinMode(segPin[i], OUTPUT);
    }
    Serial.begin(9600);
}

void loop(){
    for(int num = 0; num < 10; num++){
        Serial.println(num);
        for(int i=0; i<7; i++){
            digitalWrite(segPin[i], numbers[num][i]);
        }
        delay(1000);
    }
}