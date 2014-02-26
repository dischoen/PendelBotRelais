//Arduino BT V06 w/ Atmega168
//on MAC: dev.tty.ARDUINOBT-BluetoothSerial

#include <SoftwareSerial.h>

SoftwareSerial robotSerial(10,11);

uint8_t v1; // variable to receive data from the serial port
uint8_t v2; // variable to receive data from the serial port

int ledpin = 13; // LED connected to pin 48 (on-board LED)

uint8_t inBuf[6];

int idx;

void setup() {
  pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(115200);

  robotSerial.begin(76800);
  v1 = 0;
  v2 = 0;
  idx = 6;
}

void loop() {
  if(Serial.available())
  {
    v2 = v1;
    v1 = Serial.read();
    if(idx < 6)
    {
      inBuf[idx++] = v1;
      if(idx==6)
      {
        robotSerial.write(inBuf,6);
        if(robotSerial.available())
        {
          inBuf[0] = robotSerial.read();
          inBuf[1] = robotSerial.read();
          inBuf[2] = robotSerial.read();
          inBuf[3] = robotSerial.read();
          inBuf[4] = robotSerial.read();
          inBuf[5] = robotSerial.read();
         }
        Serial.write(inBuf,6);
      }
    }
    else if(v1 == 0xFF && v2 == 0xFF)
    {
      //command sequence start
      idx = 0;      
    }
  }
}
