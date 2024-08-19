#!/usr/bin/python

import sys
from time import sleep
from stepper import Stepper

if __name__ == "__main__":

	if len(sys.argv) > 1:
		speed = int(sys.argv[1])
	else:
		speed = 100

	step_motor = Stepper(number_of_steps = int(sys.argv[2]), motor_pins = [17, 18, 22, 23])
	step_motor.set_speed(speed)
	step_motor.step(20)
