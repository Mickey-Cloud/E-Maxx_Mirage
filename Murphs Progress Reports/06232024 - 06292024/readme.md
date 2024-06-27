# 6/24/2024
Okay, the big issue with my back up version of moving the camera incase nick's gimbal doesn't work is that it is super jittery and clinky. The driver im using to move the stepper motor is a simple H-bridge, it doesn't allow for microstepping. I've got a different microcontroller, one meant for a 3d printer and I got that working with the stepper. 

# 6/26/2024
Just worked on stuff for nicks gimbal, I synced up my laptop and compmuter unity projects, just made em up to date with the repository. I made a separate python file just for nicks gimbal:
```
#!/usr/bin/python

import socket
import sys
import serial
import re
from time import sleep
from stepper import Stepper
from gpiozero import AngularServo

ser = serial.Serial('/dev/serial0', baudrate = 115200, parity = serial.PARITY_NONE, stopbits = serial.STOPBITS_ONE, bytesize = serial.EIGHTBITS, timeout = 1) 

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(('10.42.0.96', 8080))
        try:
                while True:
                        data = s.recv(2048)
                        if data:
                                d = data.decode('ascii')
                                uni = data.decode('unicode_escape')
                                ser.write(bytes(d, 'ascii'))
                                print(repr(uni))
#                               sleep(1)

        except KeyboardInterrupt:
                print("\nProgram terminated by user.")
        except Exception as e:
                print(f"An error occurred: {e}")
        finally:
                print("Closing connection.")
                s.close()
```

Last time me and nick met, we were having an issue where when a negative camera value was sent over tcp from the computer to the pi, the pi would take that and output a double zero valu. Say the current position of the camera in unity is angled at -30 degrees in the x (pitch) direction. It would transmit: "P-30.0000\r" and that would show up on the pi as "P00" which broke nicks thing. I don't know if i did anything to fix the issue, my code shouldn't have been sending any negative values over. I think mikes automation code was messing things up, i was also in the wrong unity scene when i was testing with nick, and there may have been a shoddy connection to the pis uart. idk. I changed one thing in the python receive code, i just passed in the ascii encoding to overide the default utf-8 in the decode funcion 
```d = data.decode('ascii')``` 
instead of what it was before: 
```d = data.decode()```
That might have been it? Ive tested it all here now and it all seems to be working, I read the uart tx on the pi using a logic analyzer and a serial ttl usb thingy in putty. all seemed good. The logic anaylzer actually worked perfectly, i was suprised no data was lost with it cause I've had bad luck with the digielent analog discovery before. 

Heres the received data on the raspberry pi coming straight from unity over TCP:
![Alt text](pi.jpg?raw=true "Raspberry pi end")

And heres what the analog discovery 2 logic anaylizer captured on the raspberry pis uart tx pin:
![Alt text](discovery.jpg?raw=true "Logic anaylzer end")

Oh yeah, all work done today was at my computer with the vr headset connected. Tomorrow when i meet up with nick, im gonna just manually scrub the rotation values of the camera game object in unity to mimick headmovement from the vr headset. Make sure to use the EMPTY scene file, not the other jibberish one. Oh, also, disable the tracked pose driver (input system) component of the camera gameobject before enabling the testmove script.