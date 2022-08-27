# cc11xxflasher

Bought a Yard Stick 1 (YS1) without the rfCat firmware being installed?

If you have a Raspberry Pi - this utility will flash the c11111 source.

Connect the following pins  - (Raspberry Pi 40 Pin Header) to your Yard Stick 1. Either on P1 or the Pogo Pads found on the back of the YS1.

My Pin numbering convention
---

The square on the inner row of P1 - I refer to as Pin 1.  Pins 1 to 7 (left to right) are on the inner row.
Pin 8 is opposite Pin 1. Pins 8 to 14 (left to right) are on the outer row.


RPi|xxx| Yard Stick 1 
-------| -------|-----
(40 Pin)|yyy|(14 Pin P1)
-------| -------|-----
Pin 39| GND	|5  
Pin 38| DD   |1
Pin 36| DC   |4
Pin 35| RST  |3
Pin 1|  3.3V |8 (or 9)

![SAP2 Inspired Project](/images/alusub.jpg)
