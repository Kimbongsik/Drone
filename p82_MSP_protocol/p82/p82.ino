void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200); //프로세싱과의 연결을 위해 시리얼을 사용
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t userInput;
  if(Serial1.available() > 0 ){
    userInput = Serial1.read();


    Serial.println((char)userInput);
    }
}
