#!/usr/bin/python

from gpiozero.pins.pigpio import PiGPIOFactory
from gpiozero import OutputDevice
from gpiozero import LED
from time import sleep
import sys

print(sys.path)

factory = PiGPIOFactory()
l1 = LED(23, pin_factory=factory)
l2 = LED(18, pin_factory=factory)
l3 = LED(15, pin_factory=factory)
l4 = LED(14, pin_factory=factory)
motor = OutputDevice(25, pin_factory=factory)
motor.off()
while True:
	l1.on()
	l2.on()
	l3.on()
	l4.on()
	sleep(1)
	l1.off()
	l2.off()
	l3.off()
	l4.off()
	sleep(1)
