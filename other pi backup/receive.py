#!/usr/bin/python
from gpiozero import Motor
import sys
import socket
import math

raw_joystick_center_x = 32768
raw_joystick_center_y = 32768
#raw_joystick_x_offset = -71
#raw_joystick_y_offset = -140
joystick_dead_zone = .25
min_wheel_speed = 0.25
max_wheel_speed = 1
network_port = 8080

# w1 = top left wheel
	# in1 = GPIO 21
	# in2 = GPIO 20
# w2 = top right wheel
	# in3 = GPIO 9
	# in4 = GPIO 25
# w3 = bottom left wheel
	# in3 = GPIO 22
	# in4 = GPIO 27
# w4 = bottom right wheel
	# in1 = GPIO 23
	# in2 = GPIO 24
def calculate_wheel_speeds(x, y):
	# Center the joystick values
	x = x - raw_joystick_center_x
	y = raw_joystick_center_y - y
#	print(x, y)
	# Normalize values
	x_norm = x / raw_joystick_center_x
	y_norm = y / raw_joystick_center_y
	# Check if joystick is within the dead zone
	if abs(x_norm) <= joystick_dead_zone:
		if abs(y_norm) <= joystick_dead_zone:
			return 0, 0, 0, 0
		if y_norm >= .9:
			print("Full Forward")
			return max_wheel_speed, max_wheel_speed, max_wheel_speed, max_wheel_speed
		if y_norm <= -.9:
			print("Full Reverse")
			return -max_wheel_speed, -max_wheel_speed, -max_wheel_speed, -max_wheel_speed

	if abs(y_norm) <= joystick_dead_zone:
		if x_norm >= .9:
			print("Full Right")
			return -max_wheel_speed, max_wheel_speed, max_wheel_speed, -max_wheel_speed
		if x_norm <= -.9:
			print("Full Left")
			return max_wheel_speed, -max_wheel_speed, -max_wheel_speed, max_wheel_speed

	print(x_norm, y_norm)

	# Magnitude of joystick
	hyp = math.copysign(math.sqrt(x_norm**2 + y_norm**2), y_norm)
	angled_speed = ((math.pi / 4) - ((math.pi / 2) - math.atan2(abs(y_norm) , abs(x_norm)))) / (math.pi / 4)

	# Calculate wheel speeds
	w1 = w4 = hyp * angled_speed if ((x >=0 and y >=0) or (x < 0 and y < 0)) else hyp
	w2 = w3 = hyp * angled_speed if ((x >= 0 and y < 0) or (x < 0 and y >= 0)) else hyp

	# Clamp wheel speeds to [-1, 1] and round
	return tuple(round(min(max(w, -1), 1), 3) for w in (w1, w2, w3, w4))

def main():
	w3 = Motor(27, 22)
	w4 = Motor(24, 23)
	w2 = Motor(25, 9)
	w1 = Motor(20, 21)

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.bind(("", network_port))
		s.listen(2)
		print(f"Server started on port {network_port}")
		try:
			while True:
				print("Waiting for clients")
				conn, addr = s.accept()
				with conn:
					print(f"Connection from {addr}")
					try:
						while True:
							data = conn.recv(4096)
							if data:
								d = data.decode('ascii').strip()
								lines = d.splitlines()
#								print(f"inputs: {lines}")
								w1s, w2s, w3s, w4s = calculate_wheel_speeds(int(lines[0]), int(lines[1]))
								print(f"w1: {w1s}, w2: {w2s}, w3: {w3s}, w4: {w4s}")

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
							else:
								print("client disconnected properly")
								break
					except Exception as eee:
						print(f"The client did something bad: {eee}")
		except KeyboardInterrupt:
			print("\nThis shit was stopped by YOU")
		except Exception as e:
			print(f"An error has occured mofo: {e}")
		finally:
			print("Closing the god damn connection")
			s.close() # Dont know if this is needed

		#s.connect(('10.42.0.96', 8080))
#		try:
#			while True:
#				data = s.recv(4096)
#				if data:
#					d = data.decode('ascii').strip()
#					lines = d.splitlines()
#					if len(lines):
#						print("inputs: ", lines)
#						w1s, w2s, w3s, w4s = calculate_wheel_speeds(int(lines[2]), int(lines[3]))
#						if w1s > 0:
#							w1.forward(abs(w1s))
#						elif w1s < 0:
#							w1.backward(abs(w1s))
#						else:
#							w1.stop()
#
#						if w2s > 0:
#							w2.forward(abs(w2s))
#						elif w2s < 0:
#							w2.backward(abs(w2s))
#						else:
#							w2.stop()
#
#						if w3s > 0:
#							w3.forward(abs(w3s))
#						elif w3s < 0:
#							w3.backward(abs(w3s))
#						else:
#							w3.stop()
#
#						if w4s > 0:
#							w4.forward(abs(w4s))
#						elif w4s < 0:
#							w4.backward(abs(w4s))
#						else:
#							w4.stop()
#
#						print(calculate_wheel_speeds(int(lines[2]), int(lines[3])))
#				else:
#					break;
#		except KeyboardInterrupt:
#			print("\nThis shit was stopped")
#		except Exception as e:
#			print(f"An error has occured mofo: {e}")
#		finally:
#			print("closing the god damn connection")
#			s.close()

if __name__ == "__main__":
	# First argument is name of the program
	if len(sys.argv) != 3:
		print("Missing joystick center values, using defaults")
	else:
		raw_joystick_center_x = sys.argv[1]
		raw_joystick_center_y = sys.argv[2]
	print(f"Joystick middle is ({raw_joystick_center_x}, {raw_joystick_center_y})")
	main()
