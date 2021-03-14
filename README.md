# socialPlant

Hi and welcome this nice project about the social plant! Here you will learn all about how to create a social plant using a nodeMCU and the arduino IDE.

## So what do i need?

* A nodeMCU
* WIFI
* A plant
* Dotmatrix using a max7219 driver
* A computer

Ok before you start with the tutorial you first need to setup your. Development environment to do so follow these instructions:

## exmplain the hardware

So what is the hardware what we are actually using? and where doe all the pins etc stand for?

This information can be found here:

### ESP 8266 NodeMCU V2
The NodeMCU is our development board. Basically our brain for the project and this will have ours code. The chip that really matters on this board is the ESP 8266. This Microchip packs wifi and has a processor of 80MHZ. It has a memory of 32 KiB. Has 16 GPIO pins and is uesd in allot of IOT projects.

### Soil Moisture Sensor Module
This is the sensor that will detect how much moisture is inside your soil. The cool thing about these they have and analog output and a digital output. And you can later the digital output when it should turn the 0 to 1. 
On the image you van see the pinnout.

### Dotmatrix MAX7219
Basically you have here a 8*8 Matrix LED strip that is beeing instructed by the MAX7219 chip. Why we are using the MAX7219 this helps us allot in addressing all the LEDS on the matrixs instead of creating a complete programme for that on its own. 
