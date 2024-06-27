#!/usr/bin/python

import socket
import sys
import serial
from time import sleep
from stepper import Stepper
from gpiozero import AngularServo

def main():
	ser = serial.Serial('/dev/serial0', baudrate = 115200, parity = serial.PARITY_NONE, stopbits = serial.STOPBITS_ONE, bytesize = serial.EIGHTBITS, timeout = 1)
#	currentPos = 0
#	step_motor = Stepper(number_of_steps = 200, motor_pins = [17, 18, 22, 23])
#	step_motor.set_speed(100)

#	servo = AngularServo(27, min_angle = 0, max_angle = 180, min_pulse_width = 0.0005, max_pulse_width = 0.0024)
#	min = 10 # Servo min to prevent lock up of servo
#	max = 170 # likewise
#	servo.angle = 90
#	viewMin = 100 # In raw received "unity" terms
#	viewMax = 260 # see above

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.connect(('10.42.0.96', 8080))
		try:
			while True:
				data = s.recv(2048)
				if data:
					d = data.decode()
					ser.write(bytes(d, 'ascii'))
					print(d)
#					sleep(1)

#					up = round(float(d.strip().split()[0]))
#					if up >= 270 and up <= 360:
#						temp = up - 270
#						if temp < min:
#							servo.angle = min
#						else:
#							servo.angle = temp
#					elif up >= 0 and up <= 90:
#						temp = up + 90
#						if temp > max:
#							servo.angle = max
#						else:
#							servo.angle = temp
#					elif up > 90 and up <= 180:
#						servo.angle = max
#					else:
#						servo.angle = min

#					rotation = round(float(d.strip().split()[1]) * (200 / 360))
#					steps_to_move = rotation - currentPos

#					if abs(steps_to_move) > 100:  # Correcting for overflow if needed
#						steps_to_move = steps_to_move - 200 if steps_to_move > 0 else steps_to_move + 200

#					step_motor.step(-1 * steps_to_move)
#					currentPos = rotation

					#print("Received: ", up)
#				else:
#					break;

		except KeyboardInterrupt:
			print("\nProgram terminated by user.")
		except Exception as e:
			print(f"An error occurred: {e}")
		finally:
			print("Closing connection.")
			s.close()

if __name__ == "__main__":
	main()
