//Arduino BT V06 w/ Atmega168
//on MAC: dev.tty.ARDUINOBT-BluetoothSerial

uint8_t v1; // variable to receive data from the serial port
uint8_t v2; // variable to receive data from the serial port

int ledpin = 13; // LED connected to pin 48 (on-board LED)

uint8_t inBuf[6];
int idx;

void setup() {
  pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(115200);       // start serial communication at 9600bps
  v1 = 0;
  v2 = 0;
  idx = 6;
}

void loop() {
  if( Serial.available() )       // if data is available to read
  {
    v2 = v1;
    v1 = Serial.read();         // read it and store it in 'val'
    if(idx < 6)
    {
      inBuf[idx++] = v1;
      if(idx==6)
        Serial.write(inBuf,6);
    }
    else if(v1 == 0xFF && v2 == 0xFF)
    {
      //command sequence start
      idx = 0;      
    }
  }


/*
  if( val == 'H' )               // if 'H' was received
  {
    digitalWrite(ledpin, HIGH);  // turn ON the LED
  } else { 
    digitalWrite(ledpin, LOW);   // otherwise turn it OFF
  }*/
  //delay(100);                    // wait 100ms for next reading
}
