# The spinorial ball

A device to visualize 1/2 spin rotations

![spinorialBall](https://user-images.githubusercontent.com/16895004/206495339-edc98185-f493-4057-80ba-8c59ff78b98a.jpg)

## Introduction

The spinorial ball is a LED football containing an electronic 3D gyroscope, powered by an internal battery, whose faces change colors when it is rotated.

You need to turn it twice 360°, so 720°, around any axis so that the configuration gets back to itself.
Turn it once and it becomes the "opposite" of itself (When you consider colors on chromatic wheel) !

The mathematical machinery and physical explanations are detailed in "The spinorial ball: a macroscopic object of spin-1/2".

## Details

It is made of :
- a 3D printed frame divided in two halves of a truncated icosahedron
- 32 addressable multicolor LEDs (WS2812E)
- Arduino compatible Adafruit Feather 32u4 basic proto controller (And an additional featherwing Proto board receiving the LED strip connector)
- Adafruit Bosch BNO055 9 DOF inertial measurement unit
- a 3.7 V 1,1 Wh liPo Battery

![openBall (Small)](https://user-images.githubusercontent.com/16895004/206501316-1a81fdc9-b1c8-4d71-a87c-10f33dc51906.jpg)

## Electronics

The controller board is connected to the gyroscope via its 4 pins : 
- Power
- Ground
- SCA pin 3
- SCL pin 2

It is connected to the LED strip via an additional FeatherWing  proto board interface card which holds only a connector for the led strip
- Power
- Ground
- Data pin 12

![electronics (Small)](https://user-images.githubusercontent.com/16895004/206514295-dd579211-e71b-4bf9-922e-89a014369af1.jpg)

The third board contains only a connector to the LED strip.

![electronics assemble (Small)](https://user-images.githubusercontent.com/16895004/206514355-350c4eee-dbb4-4966-b806-77fcb258ef06.jpg)

## Printable frame

It is a truncated icosahedron assembled like a 3D puzzle from 32 hollow pieces : 
- 20 Hexagons
- 12 Pentagons

The geometric 3D print STL files come from https://www.thingiverse.com/thing:2998199

A hole is dug inside each of the 32 pieces to allow for LED placement.

![truncatedIcosahedron (Small)](https://user-images.githubusercontent.com/16895004/206514382-efd9a7dd-20b6-4837-b7e5-bccffe0437c5.jpg)

## Usage

Plug the battery.

The gyroscope will calibrate while LEDs are flashing red.

Then the gyroscope will initialize its initial position while LEDs are flashing green.

Then the initial state is displayed : red pentagons, hexagons off.

This correspond to the |up> state.

Close the ball and ... let's play :)

https://user-images.githubusercontent.com/16895004/206660205-fc275f0b-c983-40f3-bc5c-f4d4d745dbe4.mp4


## Online

There is an online version to play with : 

https://dotwave.org/spinorialBall

There is also a smartphone version : 

https://dotwave.org/spinorialPhone

And you can get yourself one ready made :

https://www.spinorialball.com

## License


The Arduino code was written by Samuel BERNARD-BERNARDET and is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported (CC BY-NC 3.0)

Soccer ball (Truncated icosahedron) assembly by Mattias_Selin is licensed under the Creative Commons - Attribution - Non-Commercial - Share Alike license.

The online version is based on an app by David DUMAS  : https://www.dumas.io/luxball

