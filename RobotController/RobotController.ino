//Arduino Robot Control
//on MAC: /dev/tty.usbmodem641

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>
#include <utility/RobotTextManager.h> 

uint8_t inBuf[6];

char textBuf1[30];
char textBuf2[30];
char textBuf3[30];


int line = 0;
int16_t left, right;

int i=0; 

void setup() {
  Wire.begin();
  Robot.begin();
  Robot.beginTFT();
  textManager.setMargin(5,5);
  textManager.writeText(0,0,"HEL.LO");
}

void loop() 
{
  i=0;
  Wire.requestFrom(2,6);
  while(Wire.available())
  {
    inBuf[i++] = Wire.read();
  }
  
  left  = inBuf[1] ? inBuf[2] - 256 : inBuf[2];
  right = inBuf[3] ? inBuf[4] - 256 : inBuf[4];
 
 
  sprintf(textBuf1, "%d:%02x %02x%02x %02x%02x %02x", i,
    inBuf[0], inBuf[1], inBuf[2], inBuf[3], inBuf[4], inBuf[5]);
  sprintf(textBuf2, "left :%4d %d", left, inBuf[2]);
  sprintf(textBuf3, "right:%4d %d", right,inBuf[4]);
  
  
  Robot.motorsWrite(left, right);
    
  Robot.clearScreen();
  
  textManager.writeText(1,0,textBuf1);
  textManager.writeText(2,0,textBuf2);
  textManager.writeText(3,0,textBuf3);

  delay(20);
}
