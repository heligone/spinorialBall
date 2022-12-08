# spinorialBall

A device to visualize spin 1/2 rotations

![spinorialBall](https://user-images.githubusercontent.com/16895004/206495339-edc98185-f493-4057-80ba-8c59ff78b98a.jpg)

## Introduction

The spinorial ball is LED gyro-Ball powered by an internal battery, whose faces change colors when it is rotated.

You need to turn it twice 360°, so 720°, around any axis so that the configuration gets back to itself.
Turn it once and it becomes the "opposite" of itself (When you consider colors on chromatic wheel) !

The Mathematical machinery is detailed in an ARXIV article "The spinorial ball : a device to visualize 1/2-spin rotations"

## Details

It is made of :
- a 3D printed frame divided in two halves of a truncated icoshedron
- 32 adressable multicolor LEDs (WS2812E)
- Adafruit Feather 32u4 basic proto controller (And an additionnal featherwing Proto board receiving the LED stirp connector)
- Adafruit Bosch BNO055 9 DOF inertial measurment unit
- a 3.7 V 1,1 Wh liPo Battery

![openBall (Small)](https://user-images.githubusercontent.com/16895004/206501316-1a81fdc9-b1c8-4d71-a87c-10f33dc51906.jpg)

## Electronics

The controller board is connected to the gyroscope via its 4 pins : 
- Power
- Ground
- SCA pin 3
- SCL pin 2

Its is connected to the LED strip via and additional FeatherWing  proto board interface card which holds only a connector for the led strip
- Power
- Ground
- Data pin 12

![electronics (Small)](https://user-images.githubusercontent.com/16895004/206514295-dd579211-e71b-4bf9-922e-89a014369af1.jpg)

![electronics assemble (Small)](https://user-images.githubusercontent.com/16895004/206514355-350c4eee-dbb4-4966-b806-77fcb258ef06.jpg)

## Printable frame

It is a truncated icosahedron (More commonly called footbal) assembled like a 3D puzzle From 32 pieces : 
- 20 Hexagons
- 12 Pentagons

From https://www.thingiverse.com/thing:2998199

A hole is digged inside each of the 32 pieces to allow for LED placement.

![truncatedIcosahedron (Small)](https://user-images.githubusercontent.com/16895004/206514382-efd9a7dd-20b6-4837-b7e5-bccffe0437c5.jpg)


## License


The Arduino code was written by Samuel BERNARD-BERNARDET and is licensed under GNU GPL.

Soccer ball (Truncated icosahedron) assembly by Mattias_Selin is licensed under the Creative Commons - Attribution - Non-Commercial - Share Alike license.

