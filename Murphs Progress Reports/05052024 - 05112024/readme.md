# 5/5/2024
Got a selected motor for spinning the camera horizontally, side to side. I've got it working with two different controllers. Got them both working on arduino. Using different speeds, I was able to play a song using the servo motor. Got this working with both the A4988 stepper motor driver and the L293D chip. I will most likely use the A4988 chip as it will translate very easily to the raspberry pi as it only requires a single pwm signal for stepping and another for direction. both digital. See video for sweet music. For powering the motor, im using the same power bank i will be using for powering the pi. It is using the other USB port. 

Setup using an Arduino:
![Alt text](arduino.jpg?raw=true "Arduino Motor Driver Setup")
![Alt text](arduino_schematic.jpg?raw=true "Arduino Schematic")

Okay, I started trying to get it working on the  raspberry pi. There are a bunch of different ways to manipulate the GPIO pins of the raspberry pi. I first started with using GPIOZERO. This library is for python. Took a little while to figure out how to drive an output. To create a digital output on a pin, use ```digitalOutput = DigitalOutputDevice(GPIO#)``` where ```GPIO#``` is the number of the gpio, not the physical pin on the raspberry pi. After not getting the motor to move at all, I took a step back and hooked up an Analog discovery scope to the output pins to see if i was getting anything. I was using the physical pin number instead of the gpio pin number. Looking at this all now, I don't know how i'm gonna set the exact rotation of the servo. Using this very crude on and off pulse way is gonna be a pain. And, I still need a way to zero out the servo, set a home position for when it turns on. Gonna call it a day. Also, if motor suddenly stops working, try clicking button on powerbank

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

# 5/6/2024
Started looking at a way to set the home position of the stepper motor. I found an optical endstop used in a 3D printer. The first one I accidentally blew up. The second one I got working using the schematic in the video listed below. One resistor is connected between vcc and pin A on the optical sensor, 150 Ohms. The other resistor is between vcc and pin C on the optical sensor, 10k Ohms. Then ground connects to pin G on the optical sensor. Pin C goes high when there is something in between the two leads and goes low when there is nothing between the two leads. I plan on having the sensor connected to the main motor part and the base will have a pole like thingy to set off the sensor. Gonna start drawing up a model for this swivel mount. I started thinking about a design then realized that it needed to mount to the car somehow and I went down a rabit hole trying to find info on the Traxxas E-Maxx car. 


## Bookmarks
Optical Endstop Circuit
https://www.youtube.com/watch?app=desktop&v=1BW7TaRlfEY



# 5/7/2024
Just decided to make a flat circular platform and will figure out how to attach it to the car later. I drew up the lower part that the gear end of the stepper motor will attach to. After an hour or two, I got a rough idea and model drawn up. It took a little while to get used to using Shapr3D coming from Autodesk inventor. It actually worked really nicely. On Ipad.

model:
![Alt text](sketch.jpg?raw=true "3D model with sketch plane")
![Alt text](complete.jpg?raw=true "Complete model")


# 5/9/2024
Sent the 3D model to the Mariott library to print. Will pick up tomorrow. 