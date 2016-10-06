# arduino_garage_ping
Test program for parking assist lights.  This uses an Atmega328P AVR microcontroller (or full Arduino) and two HC-SR04 ultrasonic distanse sensors to make ranging tests on car position and then lights up a series of LEDs to provide feedback to the driver.  The LEDs could be replaced with relays controlling a mini stoplight, or a mini stoplight could be built for the purpose.

Created by: Davis Whittaker on 1 Oct 2016.

Last Modified: 3 Oct 2016: Added flashing red lights for distances less than 8". Removed use of pins to control power to the sensors.
