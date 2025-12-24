# The Klipper Console

The Klipper console is an 8 key (9 if you count the encoder) macropad with an OLED display and several LEDs designed to attach to the side of my Ender 3 (V2). As some of you may know, adding klipper and ender 3 renders the normal built in LCD useless, meaning I have to use my computer or other web capable device to access the GUI and actually control the printer. This is annoying because I can't do that while being right in front of the printer. This design adds some basic control and information by using the RP2040 as the MCU to collect all the data and show the print status through the chain of LEDs as a progress bar plus the LCD to show time remaining. It communicates with the Raspverry Pi board running klipper through the USB C connection and another script running on the Pi recieves the data and sends the HTTP requests to the Moonraker system to run the resulting GCODE commands.

## Features:
- Running Chase of LEDs shows progress visually
- 128x32 OLED Display
- EC11 Rotary encoder to easilly move the axis or change temperatures
- 9 Keys to send custom GCODE commands and macros

## CAD Model:
The PCB with the componenets simply drops in vertically into the Top part of the case. The bottom then slides in from underneath from the top and then screws in using the M3 bolts and heat inserts attached to the Top part. Hook 1 and Hook 2 are used to attach to the printer. The RPi support and Buttom Hook serve as an attachment method for the Raspverry Pi so that it is held close to the MCU and main design and doesn't hang around loosely. The Encoder cap can be printed also for a better aesthetic instead of just the bare EC11 knob. And finally I have also added some pieces meant to be acrylic covers for the LCD, Board display cutout and LEDs (I am aware Acrylic is not allowed but Orpheuspad's design has acrylic and I will add it myself after finishing the Blueprint project or I can just remove it if needed. But a frosted acrylic for the LEDs would look absolutely WILD):

<img src=KlipperConsole/Pictures/ExplodedView1.png alt="Schematic" width="500"/> 

And here are the assembled views:

<img src=KlipperConsole/Pictures/AngledView2.png alt="Schematic" width="500"/>
<img src=KlipperConsole/Pictures/AngledView3.png alt="Schematic" width="800"/>
<img src=KlipperConsole/Pictures/TopView.png alt="Schematic" width="300"/>

Designed in Fusion

## PCB
And this is my PCB. A bit difficult to include everything under 100mm but I managed to do it and got it to 65x100mm. Normal two layer PCB with copper ground areas:

<img src=KlipperConsole/Pictures/PCBTopView.png alt="PCB View" width="300"/> <img src=KlipperConsole/Pictures/PCBRenderedView.png alt="PCB Rendered View" width="300"/> 

And the Schematic:

<img src=KlipperConsole/Pictures/Schematic.png alt="Schematic" width="800"/>


## Firmware Overview
The macropad iteself is programmed in Arduino IDE using C and the neccessary libraries for using all the componenets. It then also talks through serial through the USB to the RPi. The RPi also has a python script that read the serial data from the RP2040 and does transmits it to Moonraker. Currently I have the basic communication between the two MCU's setup and the functionality of all the components in code.

<img src=assets/bongocat.png alt="Bongo Cat" width="300"/>

I'm excited to build it and add as many feautures, GCODE commands and Marcos as possible to my new printer Console.

## BOM:
I have included a .csv with the BOM list but here it is anyways.

- x9 1N4148
- x1 OLED_128X32_0.91INCH_ I2C
- x8 CHERRY MX
- x1 Seeed XIAO RP2040
- x16 SK6812MINI-E
- x1 EC11B-V-T
- x8 Blank DSA Keycaps
- x3 M3x16mm screws
- x3 M3x5mx4mm heatset inserts
