#!/usr/bin/python

#import RPi.GPIO as GPIO
from gpiozero.pins.pigpio import PiGPIOFactory
from gpiozero import AngularServo
from time import sleep

factory = PiGPIOFactory()

#servo = Servo(17)
servo = AngularServo(14, min_angle = 0, max_angle = 180, min_pulse_width = 0.0005, max_pulse_width = 0.0024, pin_factory=factory)
serv2 = AngularServo(15, min_angle = 0, max_angle = 180, min_pulse_width = 0.00055, max_pulse_width = 0.00233, pin_factory=factory)

#GPIO.setmode(GPIO.BOARD)
#GPIO.setup(11, GPIO.OUT)
#p = GPIO.PWM(11, 50)
#p.start(0)

try:
	while True:
		servo.angle = 10
		sleep(3)
		servo.angle = 170
		sleep(3)
		serv2.angle = 10
		sleep(3)
		serv2.angle = 170
		#p.ChangeDutyCycle(3)
		#sleep(1)
		#p.ChangeDutyCycle(12)
		#sleep(1)
		#servo.value = -1
		#sleep(2)
		#servo.value = 1
		#sleep(2)
except KeyboardInterrupt:
	print("Program stopped")
