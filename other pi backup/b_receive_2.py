#!/usr/bin/python
from gpiozero import Motor
import sys
import socket
import math

joystick_center_x = 512
joystick_center_y = 512
joystick_dead_zone = .25
min_wheel_speed = 0.25
max_wheel_speed = 1

# w1 = top left wheel
# w2 = top right wheel
# w3 = bottom left wheel
# w4 = bottom right wheel
def calculate_wheel_speeds(x, y):
	# Center the joystick values
	x = x - joystick_center_x
	y = joystick_center_y - y

	# Normalize values
	x_norm = x / joystick_center_x
	y_norm = y / joystick_center_y

	# Magnitude of joystick
	hyp = (abs(y_norm) / y_norm) * math.sqrt(x_norm**2 + y_norm**2)

	if abs(x_norm) <= joystick_dead_zone and abs(y_norm) <= joystick_dead_zone:
		return 0, 0, 0, 0

    #print("peepee", (abs(y_norm) / y_norm) * (hyp * (((math.pi / 4) - ((math.pi / 2) - math.atan2(abs(y_norm) , abs(x_norm)))) / (math.pi / 4))))
    #print("poopoo", ((abs(y_norm) / y_norm) * hyp))

	w1, w2, w3, w4 = hyp, hyp, hyp, hyp
	angled_speed = ((math.pi / 4) - ((math.pi / 2) - math.atan2(abs(y_norm) , abs(x_norm)))) / (math.pi / 4)

	if x >= 0:
		w1 *= angled_speed
		w4 *= angled_speed
		if y < 0:
			w1, w4 = hyp, hyp
			w2 *= angled_speed
			w3 *= angled_speed
	else:
		w1 *= angled_speed
		w4 *= angled_speed
		if y >= 0:
			w1, w4 = hyp, hyp
			w2 *= angled_speed
			w3 *= angled_speed

	return round(min(max(w1, -1), 1),3), round(min(max(w2, -1), 1), 3), round(min(max(w3, -1), 1), 3), round(min(max(w4,-1), 1),3)

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
							w1.forward(abs(w1s))
						elif w1s < 0:
							w1.backward(abs(w1s))
						else:
							w1.stop()

						if w2s > 0:
							w2.forward(abs(w2s))
						elif w2s < 0:
							w2.backward(abs(w2s))
						else:
							w2.stop()

						if w3s > 0:
							w3.forward(abs(w3s))
						elif w3s < 0:
							w3.backward(abs(w3s))
						else:
							w3.stop()

						if w4s > 0:
							w4.forward(abs(w4s))
						elif w4s < 0:
							w4.backward(abs(w4s))
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
