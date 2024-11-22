#!/usr/bin/python
from gpiozero import Motor
import sys
import socket
import math

def calculate_wheel_speeds(x, y):
	dead_zone = 100;
	# Center Position
	center_x = 512
	center_y = 512

	# Center the joystick values
	x = x - center_x
	y = center_y - y

	# Normalize values
	x_norm = x / center_x
	y_norm = y / center_y

	# Max speed that will be used to set duty cycle
	max_speed = 100

	# Magnitude of joystick
	hyp = math.sqrt(x_norm**2 + y_norm**2)

	w1 = 0 # Top left
	w2 = 0 # Top right
	w3 = 0 # Bottom left
	w4 = 0 # Bottom right

	if abs(x) <= dead_zone and abs(y) <= dead_zone:
		return w1, w2, w3, w4

	if x >= 0:
		w1 = max_speed * hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan(y_norm / (0.01 if x_norm == 0 else x_norm)))) / (math.pi / 4))
		w2 = max_speed * hyp
		w3 = max_speed * hyp
		w4 = max_speed * hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan(y_norm / (0.01 if x_norm == 0 else x_norm)))) / (math.pi / 4))
		if y < 0:
			w1 = -1 * max_speed * hyp
			w2 = -1 * max_speed * hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan((-1 * y_norm) / (0.01 if x_norm == 0 else x_norm)))) / (math.pi / 4))
			w3 = -1 * max_speed * hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan((-1 * y_norm) / (0.01 if x_norm == 0 else x_norm)))) / (math.pi / 4))
			w4 = -1 * max_speed * hyp
	else:
		w1 = -1 * max_speed * hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan(y_norm / (0.01 if x_norm == 0 else x_norm)))) / (math.pi / 4))
		w2 = -1 * max_speed * hyp
		w3 = -1 * max_speed * hyp
		w4 = -1 * max_speed * hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan(y_norm / (0.01 if x_norm == 0 else x_norm)))) / (math.pi / 4))
		if y >= 0:
			w1 = max_speed * hyp
			w2 = max_speed * hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan(y_norm / (-0.01 if x_norm == 0 else (-1 * x_norm))))) / (math.pi / 4))
			w3 = max_speed * hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan(y_norm / (-0.01 if x_norm == 0 else (-1 * x_norm))))) / (math.pi / 4))
			w4 = max_speed * hyp

	return min(max(int(w1), -1 * max_speed), max_speed), min(max(int(w2), -1 * max_speed), max_speed), min(max(int(w3), -1 * max_speed), max_speed), min(max(int(w4),-1 * max_speed), max_speed)

def main():
	w2 = Motor(27, 22)
	w1 = Motor(24, 23)
	w3 = Motor(25, 9)
	w4 = Motor(20, 21)

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.connect(('10.42.0.126', 8080))
		try:
			while True:
				data = s.recv(4096)
				if data:
					d = data.decode('ascii').strip()
					lines = d.splitlines()
					if len(lines):
#						print("inputs: ", lines)
						w1s, w2s, w3s, w4s = calculate_wheel_speeds(int(lines[2]), int(lines[3]))
						if w1s > 0:
							w1.forward(abs(w1s) / 100)
						elif w1s < 0:
							w1.backward(abs(w1s) / 100)
						else:
							w1.stop()

						if w2s > 0:
							w2.forward(abs(w2s) / 100)
						elif w2s < 0:
							w2.backward(abs(w2s) / 100)
						else:
							w2.stop()

						if w3s > 0:
							w3.forward(abs(w3s) / 100)
						elif w3s < 0:
							w3.backward(abs(w3s) / 100)
						else:
							w3.stop()

						if w4s > 0:
							w4.forward(abs(w4s) / 100)
						elif w4s < 0:
							w4.backward(abs(w4s) / 100)
						else:
							w4.stop()

						print(calculate_wheel_speeds(int(lines[2]), int(lines[3])))
				else:
					break;
		except KeyboardInterrupt:
			print("\nThis shit was stopped")
		except Exception as e:
			print(f"An error has occured mofo: {e}")
		finally:
			print("closing the god damn connection")
			s.close()
if __name__ == "__main__":
	main()
