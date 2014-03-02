PendelBotRelais
===============

This repositories contains two Arduino projects which are used for
the PendelBot, based on the Arduino Robot.

* BluetoothRelais
Runs on a Arduino Bluetooth. It reads a command from the bluetooth serial conneciton
and forwards it as an I2C slave to the Arduino Robot.

* RobotController
This applikation runs on the Arduino Robot Control board. It requests commands
from the Bluetooth relais via I2C, extracts the motor speed parameters
and applies them to the motors.
