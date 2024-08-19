#!/usr/bin/python

from gpiozero.pins.pigpio import PiGPIOFactory
from gpiozero import OutputDevice
from time import sleep

factory = PiGPIOFactory()
step = OutputDevice(7, pin_factory=factory)
dir = OutputDevice(8, pin_factory=factory)
enable = OutputDevice(25, pin_factory=factory)

dir.off()
enable.on()

while True:
	step.on()
	sleep(0.0005)
	step.off()
	sleep(0.0005)

