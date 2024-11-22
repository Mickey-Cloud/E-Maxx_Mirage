#!/usr/bin/python
from gpiozero import Motor
from time import sleep

w2 = Motor(27, 22)
w1 = Motor(24, 23)
w3 = Motor(25, 9)
w4 = Motor(20, 21)

w1.forward(speed = 0.25)
w2.forward(speed = 0.25)
w3.forward(speed = 0.25)
w4.forward(speed = 0.25)

sleep(3)

w1.stop()
w2.stop()
w3.stop()
w4.stop()

