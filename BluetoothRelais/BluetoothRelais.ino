//Arduino BT V06 w/ Atmega168
//on MAC: dev.tty.ARDUINOBT-BluetoothSerial

#include <Wire.h>


uint8_t v1; // variable to receive data from the serial port
uint8_t v2; // variable to receive data from the serial port

int ledpin = 13; // LED connected to pin 48 (on-board LED)

uint8_t btBuf[6];
uint8_t i2cBuf[6];

int idx;

void setup() {
  //pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(115200);

  Wire.begin(2);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  v1 = 0;
  v2 = 0;
  idx = 6;
  btBuf[5] = 0x88;
}

void loop() {
  //Serial.write(".\n");
  
  if(Serial.available())
  {
    v2 = v1;
    v1 = Serial.read();
    if(idx < 6)
    {
      btBuf[idx++] = v1;
      if(idx==6)
      {
        Serial.write(i2cBuf,6);
      }
    }
    else if(v1 == 0xFF && v2 == 0xFF)
    {
      //command sequence start
      idx = 0;      
    }
  }
  
  //delay(200);
}

void requestEvent()
{
  //Serial.write("reqE\n");
  Wire.write(btBuf,6);
}

void receiveEvent(int howMany)
{
  Serial.write("recE\n");
  int i = 0;
  while(Wire.available()) // loop through all but the last
  {
          i2cBuf[i++] = Wire.read();
  }
}

