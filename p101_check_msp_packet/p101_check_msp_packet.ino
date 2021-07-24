void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop() {
  checkMsppacket();
}

enum {
  HEAD1,  HEAD2,  HEAD3,  DATASIZE, CMD,
  ROLL, PITCH,  YAW,  TROTTLE,
  AUX,  CRC,  PACKETSIZE,

};
uint8_t mspPacket[PACKETSIZE];

void checkMsppacket() {
  static uint32_t cnt;


  if(Serial1.available() > 0) {
    while(Serial1.available()> 0) {
      uint8_t mspData = Serial1.read();

      if(mspData == '$')  cnt = HEAD1;
      else  cnt++;

      mspPacket[cnt] = mspData;

      if(cnt == CRC)  printMspPacket();
      
      }
    }
  }

 void printMspPacket()  {
  Serial.print((char)mspPacket[HEAD1]);
  Serial.print((char)mspPacket[HEAD2]);
  Serial.print((char)mspPacket[HEAD3]);
  Serial.print(mspPacket[DATASIZE]);
  Serial.print(' ');
  Serial.print(mspPacket[CMD]);
  Serial.print('\t');
  Serial.print("R:");
  Serial.print(mspPacket[ROLL]);
  Serial.print('\t');
  Serial.print("P:");
  Serial.print(mspPacket[PITCH]);
  Serial.print('\t');
  Serial.print("Y:");
  Serial.print(mspPacket[YAW]);
  Serial.print('\t');
  Serial.print("T:");
  Serial.print(mspPacket[TROTTLE]);
  Serial.print('\t');
  Serial.print(mspPacket[AUX]);
  Serial.print(' ');
  Serial.print(mspPacket[CRC]);
  Serial.print('\n');
  }
