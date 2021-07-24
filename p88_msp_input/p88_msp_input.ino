void setup(){ 
  Serial1.begin(115200); //프로세싱과의 연결을 위해 시리얼을 사용
  Serial.begin(115200);
  
}

void loop() {
  if(Serial1.available()){
    uint8_t mspData = Serial1.read();
    Serial.print((char)mspData);
    Serial.print("\t");
    Serial.println(mspData, DEC);
    }
}
