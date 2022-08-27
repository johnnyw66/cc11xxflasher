# cc11xxflasher

Bought a Yard Stick 1 (YS1) without the rfCat firmware being installed?

If you have a Raspberry Pi - this utility will flash the cc1111 hex source.

I stand on the shoulders of Giants
---

Thank you to *Aaron Christophel* for his github ESP_CC_Flasher project. https://github.com/atc1441/ESP_CC_Flasher

Most of the source is from his project with the exception of Intel Hex file handling being supported instead of binary firmware files
(Courtesey of Stuart Cording https://github.com/codinghead/Intel-HEX-Class)

My Pin numbering convention
---
Connect the following pins  - (Raspberry Pi 40 Pin Header) to your Yard Stick 1. Either on P1 or the Pogo Pads found on the back of the YS1.

The square on the inner row of P1 - I refer to as Pin 1.  Pins 1 to 7 (left to right) are on the inner row.
Pin 8 is opposite Pin 1. Pins 8 to 14 (left to right) are on the outer row.


RPi(40 Pin)|nomenclature| Yard Stick 1 (14 Pin P1) 
-------|-------|-----
Pin 39| GND	|5  
Pin 38| DD   |1
Pin 36| DC   |4
Pin 35| RST  |3
Pin 1|  3.3V |8 (or 9)

![Home brew pogo programming device with Pi Zero](/images/YS1_PiZero_Programmer.jpg)
![Home brew pogo programming device with Pi Zero](/images/YS1_Pogo_Pins_P1.jpg)


Make sure you have 'WiringPi' and gcc installed on your Pi. Download this git repo and run
**./bld.sh rpi** to compiler the source.

(Note: **bld.sh** without any options will compile the source with dummy IO calls)

To Run
---

**./bin/flasher RfCatYS1.hex**



