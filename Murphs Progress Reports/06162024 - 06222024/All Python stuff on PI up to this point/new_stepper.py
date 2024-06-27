#!/usr/bin/python

from gpiozero import OutputDevice
from time import sleep

step = OutputDevice(17)
dir = OutputDevice(18)
steps = 200

dir.on()
while True:
	step.on()
	sleep(0.001)
	step.off()
	sleep(0.001)

