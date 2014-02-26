#include <AltSoftSerial.h>

//Arduino Robot Control
//on MAC: /dev/tty.usbmodem641

#include <ArduinoRobot.h>
#include <utility/RobotTextManager.h> 

AltSoftSerial robotSerial(3,4);

uint8_t inBuf[6];
char textBuf[20];

const int p3 = TKD3;
const int p4 = TKD4;
const int p5 = TKD5;

int pin = TKD5;

void setup() {
  Robot.begin();
  Robot.beginTFT();
  robotSerial.begin(76800);
  textManager.setMargin(5,5);
  textManager.writeText(0,0,"HEL.LO");

}

void loop() 
{
  //Robot.digitalWrite(pin, HIGH);
  //delay(300);
  //Robot.digitalWrite(pin, LOW);


/*  sprintf(textBuf, "P4:%d", digitalRead(p4));
  textManager.writeText(1,0,textBuf);
  
  sprintf(textBuf, "P5:%d", digitalRead(p5));
  textManager.writeText(2,0,textBuf);
*/
  //textManager.writeText(3,4,"HOLLA!");
  //delay(300);

  if(robotSerial.available())
    {
      inBuf[0] = robotSerial.read();
      inBuf[1] = robotSerial.read();
      inBuf[2] = robotSerial.read();
      inBuf[3] = robotSerial.read();
      inBuf[4] = robotSerial.read();
      inBuf[5] = robotSerial.read();
      Robot.clearScreen();
      sprintf(textBuf, "SSC:%u", inBuf[0]);
      textManager.writeText(1,0,textBuf);
      inBuf[5] = 0x99;
      robotSerial.write(inBuf,6);
    }

}
