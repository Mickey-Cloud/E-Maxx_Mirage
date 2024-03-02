# 2/26/2024
got libraries installed for raspberry pi camera module 3. Got raspberry pi communicating with my computer through serial UART. Started researching different wireless protocols and figuring out how video footage is outputted. Tried to test camera by broadcasting to local port number
Got camera working, was able to take a picture and save as a jpeg. Only worked through picamera2 stuff, rpicam-hello and stuff doesn't work anymore for some reason. I started the built in python HTTP webserver that shares the home directory to localhost on port 8000. run the following command to start that python server:  python3 -m http.server
To run command in background add & to the end
use fg to bring to foreground
kill pid to terminate app
ps to view running services
jobs to view running jobs to use fg or bg on
ps -aef to see more details
top to see running stuff in real time

Yeah, I was able to see jpegs on server, had to connect pi to same network computer was on. Got a video to record using the same picamera2 library:

```
#!/usr/bin/python3

from picamera2 import Picamera2
picam2 = Picamera2()
picam2.start_and_record_video("test.mp4",duration=5,show_preview=False)
```

that hastag thing is very important. ran the program with ./test.py
for somereason, video only shows up as 4 seconds. 

Goals for Week of Spring Break
Find a suitable wireless radio module capable of streaming at least 12,144 kbps

## Useful Bookmarks:
https://www.raspberrypi.com/documentation/computers/camera_software.html#getting-started
https://github.com/raspberrypi/picamera2/blob/main/examples/capture_mjpeg.py
https://toolstud.io/video/bitrate.php?imagewidth=1920&imageheight=1080&colordepth=24&framerate=60
https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/device_guides/working_with_fem.html#ug-radio-fem
