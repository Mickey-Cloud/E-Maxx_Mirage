# 5/5/2024
Got a selected motor for spinning the camera horizontally, side to side. I've got it working with two different controllers. Got them both working on arduino. Using different speeds, I was able to play a song using the servo motor. Got this working with both the A4988 stepper motor driver and the L293D chip. I will most likely use the A4988 chip as it will translate very easily to the raspberry pi as it only requires a single pwm signal for stepping and another for direction. both digital. See video for sweet music. For powering the motor, im using the same power bank i will be using for powering the pi. It is using the other USB port. 

Setup using an Arduino:
![Alt text](arduino.jpg?raw=true "Arduino Motor Driver Setup")
![Alt text](arduino_schematic.jpg?raw=true "Arduino Schematic")

Okay, I started trying to get it working on the  raspberry pi. There are a bunch of different ways to manipulate the GPIO pins of the raspberry pi. I first started with using GPIOZERO. This library is for python. Took a little while to figure out how to drive an output. To create a digital output on a pin, use ```digitalOutput = DigitalOutputDevice(GPIO#)``` where ```GPIO#``` is the number of the gpio, not the physical pin on the raspberry pi. After not getting the motor to move at all, I took a step back and hooked up an Analog discovery scope to the output pins to see if i was getting anything. I was using the physical pin number instead of the gpio pin number. Looking at this all now, I don't know how i'm gonna set the exact rotation of the servo. Using this very crude on and off pulse way is gonna be a pain. And, I still need a way to zero out the servo, set a home position for when it turns on. Gonna call it a day.

Pins used on Raspberry Pi
![Alt text](raspberry.jpg?raw=true "Raspberry pi setup")

## Bookmarks
Using the L293D chip with gpiozero for stepper motor control
https://github.com/gpiozero/gpiozero/issues/144
https://github.com/gfabia/raspberrypi-gpiozero-stepmotor

A4988 Chip Datasheet
https://www.pololu.com/file/0J450/a4988_DMOS_microstepping_driver_with_translator.pdf

gpiozero Docs
https://gpiozero.readthedocs.io/en/latest/index.html

L293D Datasheet
https://www.ti.com/lit/ds/symlink/l293d.pdf?ts=1714891379199&ref_url=https%253A%252F%252Fwww.mouser.ca%252F