#!/home/hdr7/Documents/virtualshit2/bin/python3

import nmcli
from time import sleep
from gpiozero import LED
from gpiozero.pins.pigpio import PiGPIOFactory

#print("test")
#print(nmcli.device.show(ifname = "wlan0")["GENERAL.STATE"])

factory = PiGPIOFactory()

led = LED(23, pin_factory=factory)

while "connected" not in nmcli.device.show(ifname = "wlan0")["GENERAL.STATE"]:
	sleep(1)

led.on()
