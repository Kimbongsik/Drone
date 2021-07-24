void setup() {
  Serial1.begin(115200);

  initMotorSpeed();
}

void loop() {
  controlMotorSpeed();
}

#define THROTTLE_MAX 255
#define THROTTLE_MIN 0
#define THROTTLE_INI 5

int throttle = THROTTLE_MIN;

int motorA_pin = 6;
int motorB_pin = 10;
int motorC_pin = 9;
int motorD_pin = 5;

void initMotorSpeed() {
  analogWrite(motorA_pin, THROTTLE_INI); delay(1000);
  analogWrite(motorB_pin, THROTTLE_INI); delay(1000);
  analogWrite(motorC_pin, THROTTLE_INI); delay(1000);
  analogWrite(motorD_pin, THROTTLE_INI); delay(1000);

}

void controlMotorSpeed() {
  checkMspPacket();
  updateMotorSpeed();
}


//ENUM은 뭐임??

enum {
  HEAD1,  HEAD2,  HEAD3,  DATASIZE, CMD,
  ROLL,   PITCH,  YAW,    THROTTLE,
  AUX,    CRC,    PACKETSIZE,

};
uint8_t mspPacket[PACKETSIZE];

void checkMspPacket() {
  static uint32_t cnt;

  if (Serial.available() > 0) {
    while (Serial1.available() > 0) {
      uint8_t mspData = Serial1.read();
      if (mspData == '$') cnt = HEAD1;
      else cnt++;

      mspPacket[cnt] = mspData;

      if (cnt == CRC) {
        if (mspPacket[CMD] == 150) {
          throttle = mspPacket[THROTTLE];
        }
      }
    }
  }
}


void updateMotorSpeed() {
  analogWrite(motorA_pin, throttle);
  analogWrite(motorB_pin, throttle);
  analogWrite(motorC_pin, throttle);
  analogWrite(motorD_pin, throttle);

//  motor horizontal spin test
//  analogWrite(motorA_pin, throttle);
//  analogWrite(motorB_pin, THROTTLE_MIN);
//  analogWrite(motorC_pin, throttle);
//  analogWrite(motorD_pin, THOTTLE_MIN);
}
