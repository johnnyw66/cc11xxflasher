# cc11xxflasher PiFET

Do you have a Yard Stick 1 (YS1) without the rfCat firmware? I paid good money for a YS1 which was advertised as having rfCat installed.
My intial problem was that the device was not even enumerating on the OS USB stack - (I should have tested this before installing the Python libraries!) - a sure
indicator that I didn't get what I paid for. More worringly I found that my supplier was not the only one selling these 'empty' devices. 

On Discord I found another buyer had bought one from another recommended supplier which also turn out to be a pup. The only way of getting the device back to life was to buy a flash programmer another £50 to £120. WTF! Since I only needed to flash the firmware once, buying one of the programmers (GoodFET, GreatFET, TI-CCDebugger) was going to be expensive. I've seen *bit-bashing* programmers for programming Arduinos built from Arduinos before. Could I build something similar using spares from my workshop? After some research I managed to come up with some source for ESP32 microcontrollers which I had plenty in stock. However, I found developing for these processors clunky and tiresome and so decided to port the software to run on my one of my Rapberry Pi Zeros. 
The other, albeit minor problem with the ESP version, is that it only supported binary files. Most firmware updates for the YS1 came in the HEX format.
My C skills are very rusty - but I did have 20+ years C/C++ in the games industry. It took less than a couple of hours to get the port completed. 

I decided to name this port.. *PiFet*!

Parts Needed
---

If you have a Raspberry Pi - this utility will flash the firmware for the YS1's cc1111 device from an intel hex source.
After building a programming prong from pogo pins* and buying a £50 'Helping Hand Clamp'* - 'What!!???' - I finally had something that could flash the YS1 CC1111 chip.
I argued that at I could use the clamp for other projects - so at least I saved some money. It took me 2 hours to build the pogo prong. 

*Sourcingmap 33Pcs P125B Dia 2mm Length 33mm Spring Test Probes Testing Pins - Amazon UK

*Helping Hands with Big Magnet Base, Soldering Third Hand with 6 PCB Pillars Circuit Board Holder and 5 Flexible Metal Arms Heavy Duty Base for Repair/Resoldering/Hobby/Crafts - Amazon UK



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

You can double check you have wired up to the correct pins by cross checking with marked pads on the back of the board.



RPi(40 Pin)|Nomenclature| Yard Stick 1 (14 Pin P1) 
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

Use a CC11xx flasher hardware (such as GreatFET, GoodFET, CCDEBUGER or PiFET) to install CCBootloader onto your device
For the Yard Stick 1 (YS1) this would be 

https://github.com/atlas0fd00m/rfcat/blob/master/firmware/CCBootloader/CCBootloader-rfcat-ys1.hex

For PiFET (the flash software I ported described in this repo), run the command

./bin/flasher CCBootloader-rfcat-ys1.hex

If this is flashed successfully - both LEDs will light up on your YS1. This means the device is in bootloader mode
and ready for the RfCat software to be flashed using *rfcat_bootloader* commands.

Download the latest RFCAT image from 

https://github.com/atlas0fd00m/rfcat/releases

There are two types of hex files - ones which can be flashed with the FET or CCDEBUGER type hardware or one which
can be flashed using your own USB port. The Bootloader versions are named RfCat{HARDWARE}CCBootloader.hex.
For example: RfCat*YS1*CCBootloader.hex

````
rfcat_bootloader /dev/cu.usbmodem erase_all
rfcat_bootloader /dev/cu.usbmodem download RfCatYS1CCBootloader.hex
rfcat_bootloader /dev/cu.usbmodem verify RfCatYS1CCBootloader.hex && rfcat_bootloader /dev/cu.usbmodem run
````
You'll need to find the name of your 'bootloader' serial device under your OS. Simply do a 'ls -l /dev/\*' before and after 
plugging in your YS1 (in CCBootloader mode) into your USB port. On my MAC OS X - this was /dev/cu.usbmodem.


The final *rfcat_bootloader* command 'run' will turn the LEDs off - and your device should now be running *rfcat*


Once CCBootloader is installed future updates can be initiated with the rfcat command 

*rfcat --bootloader --force -S*

This will force the YS1 to accept *rfcat_bootloader* commands (erase_all, download, verify and run) through the USB port.

 
 
