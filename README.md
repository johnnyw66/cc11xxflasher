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


Updating Firmware - (CCbootloader preinstalled) - a reminder
---
If you flash the YS1 with a CCbootloader - you can then use your own USB rather than this home brew Rpi solution to install further updates


````
rfcat --bootloader --force -S 
rfcat_bootloader /dev/RFCAT_BL_YS1 erase_all
rfcat_bootloader /dev/RFCAT_BL_YS1 download RfCatYS1CCBootloader-201231.hex
rfcat_bootloader /dev/RFCAT_BL_YS1 verify bins/RfCatYS1CCBootloader-201231.hex && rfcat_bootloader /dev/RFCAT_BL_YS1 run
````

Starting from scratch.
---

Use a CC11xx flasher hardware (such as GreatFET, GoodFET,CCDEBUGER or G1WVNFET) to install CCBootloader onto your device
For the Yard Stick 1 (YS1) this would be 

https://github.com/atlas0fd00m/rfcat/blob/master/firmware/CCBootloader/CCBootloader-rfcat-ys1.hex

For G1WVNFET (the flash software I ported described in this repo), run the command

./bin/flasher CCBootloader-rfcat-ys1.hex

If this is flashed successfully - both LEDs will come light up on your YS1. This means the device is in bootloader mode
ready for the RfCat software to be flashed.

Download the latest RFCAT image from 

https://github.com/atlas0fd00m/rfcat/releases

There are two types of hex files - ones which can be flashed with the FET or CCDEBUGER type hardware or one which
can be flashed using your own USB port. The Bootloader versions are named RfCat{HARDWARE}CCBootloader.hex.
For example: RfCat*YS1*CCBootloader.hex

rfcat_bootloader /dev/cu.usbmodem erase_all
rfcat_bootloader /dev/cu.usbmodem download RfCatYS1CCBootloader.hex
rfcat_bootloader /dev/cu.usbmodem verify bins/RfCatYS1CCBootloader.hex && rfcat_bootloader /dev/cu.usbmodem run

The finally command 'run' will turn the LEDs off - and your device is now running *rfcat*


For more updates - proceed the sequence of 'rfcat_bootloader' commands with the command

rfcat --bootloader --force -S 

This will force the YS1 to be ready to except *rfcat_bootloader* commands so that you can download and verify updated firmware
over your USB port.
 
 
