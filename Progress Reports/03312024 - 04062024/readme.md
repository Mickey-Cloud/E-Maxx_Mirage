# 3/31/2024
I've finally got a video stream working that can be viewed through a web browswer. Completely wireless!  
Also fixed the issue with hostapd not working after restart. Problem was hostapd.service was being started before its depdencies started. I added a delay to its service file located at: 
```
/etc/systemd/system/multi-user.target.wants/hostapd.service
```
After saving, its contents looked like this:
```
[Unit]
Description=Access point and authentication server for Wi-Fi and Ethernet
Documentation=man:hostapd(8)
After=network.target

[Service]
Type=forking
PIDFile=/run/hostapd.pid
Restart=on-failure
RestartSec=2
Environment=DAEMON_CONF=/etc/hostapd/hostapd.conf
EnvironmentFile=-/etc/default/hostapd
ExecStart=/usr/sbin/hostapd -B -P /run/hostapd.pid -B $DAEMON_OPTS ${DAEMON_CONF}

ADDED LINE
ExecStartPre=/bin/sleep 15

[Install]
WantedBy=multi-user.target
```
Also had an issue where the raspberry pi camera module wasn't being detected. I had to disable legacy camera support in raspi-config (make sure to run as root, also, it might have been enabling it that fixed it, I can't rememeber, hell, maybe this didn't do anything cause I was changing all sorts of things trying to get it to show up). Then in the "/boot/config.txt" file, I commented out the line that had: ```start_x=1``` and added this line instead: ```camera_auto_detect=1``` That got the camera working finally. Was able to test it by running the ```libcamera-still``` command. Also, note, its not rpicam for this raspberry pi for some reason. Its libcamera. I think I must have downloaded an older version of Raspberry Pi OS. 

I was unable to get picamera2 streaming stuff to work. Well it ran, I just didn't figure out how to view the streamed footage. I tried using VLC, didn't work. I wasn't doing something right. Maybe I was using a reserved port number.

To login to raspberry pi over wifi ssh using windows terminal (powershell), use ```ssh hdr@hdr.local``` and enter password: "1234". Also, rememeber to disconnect and VPN's first
Wifi ssid: HDR
Wifi password: shit_9#*

I got to figure out more about video encoding, streaming, tcp, udp, rtp, rtsp, hostnames. 

## Working code
This was the mjpeg_server.py example from the picamera2 python library
```
#!/usr/bin/python3

# Mostly copied from https://picamera.readthedocs.io/en/release-1.13/recipes2.html
# Run this script, then point a web browser at http:<this-ip-address>:8000
# Note: needs simplejpeg to be installed (pip3 install simplejpeg).

import io
import logging
import socketserver
from http import server
from threading import Condition

from picamera2 import Picamera2
from picamera2.encoders import JpegEncoder
from picamera2.outputs import FileOutput

PAGE = """\
<html>
<head>
<title>picamera2 MJPEG streaming demo</title>
</head>
<body>
<h1>Picamera2 MJPEG Streaming Demo</h1>
<img src="stream.mjpg" width="640" height="480" />
</body>
</html>
"""


class StreamingOutput(io.BufferedIOBase):
    def __init__(self):
        self.frame = None
        self.condition = Condition()

    def write(self, buf):
        with self.condition:
            self.frame = buf
            self.condition.notify_all()


class StreamingHandler(server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.send_response(301)
            self.send_header('Location', '/index.html')
            self.end_headers()
        elif self.path == '/index.html':
            content = PAGE.encode('utf-8')
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.send_header('Content-Length', len(content))
            self.end_headers()
            self.wfile.write(content)
        elif self.path == '/stream.mjpg':
            self.send_response(200)
            self.send_header('Age', 0)
            self.send_header('Cache-Control', 'no-cache, private')
            self.send_header('Pragma', 'no-cache')
            self.send_header('Content-Type', 'multipart/x-mixed-replace; boundary=FRAME')
            self.end_headers()
            try:
                while True:
                    with output.condition:
                        output.condition.wait()
                        frame = output.frame
                    self.wfile.write(b'--FRAME\r\n')
                    self.send_header('Content-Type', 'image/jpeg')
                    self.send_header('Content-Length', len(frame))
                    self.end_headers()
                    self.wfile.write(frame)
                    self.wfile.write(b'\r\n')
            except Exception as e:
                logging.warning(
                    'Removed streaming client %s: %s',
                    self.client_address, str(e))
        else:
            self.send_error(404)
            self.end_headers()


class StreamingServer(socketserver.ThreadingMixIn, server.HTTPServer):
    allow_reuse_address = True
    daemon_threads = True


picam2 = Picamera2()
picam2.configure(picam2.create_video_configuration(main={"size": (640, 480)}))
output = StreamingOutput()
picam2.start_recording(JpegEncoder(), FileOutput(output))

try:
    address = ('hdr.local', 8000)
    server = StreamingServer(address, StreamingHandler)
    server.serve_forever()
finally:
    picam2.stop_recording()
```
Then, to view the live footage actually working, go to hdr.local:8000

## Bookmarks that I keep losing
Broadcast SSID on Reboot fix:
https://forums.raspberrypi.com/viewtopic.php?t=234145

Camera fix:
https://forums.raspberrypi.com/viewtopic.php?t=348870

picamera2 examples:
https://github.com/raspberrypi/picamera2/blob/main/examples

Official raspberry pi documentation libcamera and rpicam apps
https://www.raspberrypi.com/documentation/computers/camera_software.html#introducing-the-raspberry-pi-cameras

picamera2 documentation
https://datasheets.raspberrypi.com/camera/picamera2-manual.pdf