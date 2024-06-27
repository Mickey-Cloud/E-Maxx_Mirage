#!/usr/bin/python

import socket
import sys
from time import sleep
from stepper import Stepper

def main():
	currentPos = 0
	step_motor = Stepper(motor_pins = [17, 18, 22, 23])
	step_motor.set_speed(300)
	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.connect(('10.42.0.96', 8080))
		try:
			while True:
				data = s.recv(1024)
				if data:
					#rotation = round(float(data.decode().strip().split()[1]) * (200 / 360))
					#steps_to_move = rotation - currentPos

					#if abs(steps_to_move) > 100:  # Correcting for overflow if needed
				#		steps_to_move = steps_to_move - 200 if steps_to_move > 0 else steps_to_move + 200
#
#					step_motor.step(-1 * steps_to_move)
#					currentPos = rotation

					#print("Received: ", rotation)
				else:
					break;
		except KeyboardInterrupt:
			print("\nProgram terminated by user.")
		except Exception as e:
			print(f"An error occurred: {e}")
		finally:
			print("Closing connection.")
			s.close()

if __name__ == "__main__":
	main()
