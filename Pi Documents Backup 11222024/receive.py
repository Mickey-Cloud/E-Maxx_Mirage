#!/usr/bin/python

import socket
import sys
import serial
from time import sleep
from gpiozero import AngularServo
from gpiozero.pins.pigpio import PiGPIOFactory
from gpiozero import OutputDevice

factory = PiGPIOFactory()
#enable = OutputDevice(25, pin_factory=factory)

def main():
#	currentPos = 0
#	steps = 3200
#	step = OutputDevice(7, pin_factory=factory)
#	dir = OutputDevice(8, pin_factory=factory)
#	enable.on()

	pitch_servo = AngularServo(14, min_angle = 0, max_angle = 180, min_pulse_width = 0.0005, max_pulse_width = 0.0024, pin_factory=factory)
	yaw_servo = AngularServo(15, min_angle = 0, max_angle = 180, min_pulse_width = 0.00055, max_pulse_width = 0.00233, pin_factory=factory)
	min = 10 # Servo min to prevent lock up of servo
	max = 170 # likewise
	pitch_servo.angle = 90
	yaw_servo.angle = 90
	viewMin = 100 # In raw received "unity" terms
	viewMax = 260 # see above

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.connect(('10.42.0.46', 8080))
		try:
			while True:
				data = s.recv(2048)
				if data:
					d = data.decode()
					#print(d)

					# Pitch Servo
					up = round(float(d.strip().split()[0]))
					if up >= 270 and up <= 360:
						temp = up - 270
						if temp < min:
							pitch_servo.angle = min
						else:
							pitch_servo.angle = temp
					elif up >= 0 and up <= 90:
						temp = up + 90
						if temp > max:
							pitch_servo.angle = max
						else:
							pitch_servo.angle = temp
					elif up > 90 and up <= 180:
						pitch_servo.angle = max
					else:
						pitch_servo.angle = min

					# Yaw Servo
					side = round(float(d.strip().split()[1]))
					if side >= 270 and side <= 360:
						temp = side - 270
						if temp < min:
							yaw_servo.angle = min
						else:
							yaw_servo.angle = temp
					elif side >= 0 and side <= 90:
						temp = side + 90
						if temp > max:
							yaw_servo.angle = max
						else:
							yaw_servo.angle = temp
					elif side > 90 and side <= 180:
						yaw_servo.angle = max
					else:
						yaw_servo.angle = min

					# Stepper Motor
#					rotation = round(float(d.strip().split()[1]) * (steps / 360))
#					steps_to_move = rotation - currentPos

#					if abs(steps_to_move) > (steps / 2):  # Correcting for overflow if needed
#						steps_to_move = steps_to_move - steps if steps_to_move > 0 else steps_to_move + steps

#					if steps_to_move < 0:
#						dir.off()
#					else:
#						dir.on()

#					for x in range(abs(steps_to_move)):
#						step.on()
#						sleep(0.0005)
#						step.off()
#						sleep(0.0005)

					#step_motor.step(-1 * steps_to_move)
#					currentPos = rotation
				else:
					break;

		except KeyboardInterrupt:
			print("\nProgram terminated by user.")
		except Exception as e:
			print(f"An error occurred: {e}")
		finally:
#			enable.off()
			print("Closing connection.")
			s.close()

if __name__ == "__main__":
	main()
#	enable.off()
