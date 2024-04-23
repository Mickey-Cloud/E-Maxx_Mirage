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
Also had an issue where the raspberry pi camera module wasn't being detected. I had to disable legacy camera support in raspi-config (make sure to run as root, also, it might have been enabling it that fixed it, I can't rememeber, maybe this didn't do anything cause I was changing all sorts of things trying to get it to show up). Then in the "/boot/config.txt" file, I commented out the line that had: ```start_x=1``` and added this line instead: ```camera_auto_detect=1``` That got the camera working finally. Was able to test it by running the ```libcamera-still``` command. Also, note, its not rpicam for this raspberry pi for some reason. Its libcamera. I think I must have downloaded an older version of Raspberry Pi OS. 

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

# 4/1/2024
Started researching turning 2d camera footage into 3d footage for VR. Started downloading unity. Setup a testing unity vr default project. I got my headset hooked up to it. The headset is an htc vive pro, with steam base station 2.0s. I was able to run the default scene, walk around, manipulate objects. I got a very simple script working on an empty game object. Made a skybox display that displayed a camera hooked up to my computer. Got a very very crude version of what we want working. Will upload the unity project code once I further develop it. Its a three gig folder, big. All  i had to do to run the game was have the vr headset connected with steam vr running. It worked seamlessly basically.

## Might be useful Bookmarks
https://www.reddit.com/r/virtualreality/comments/1bioyfi/how_to_feed_a_usb_camera_directly_to_a_specific/
https://community.theta360.guide/t/stream-ricoh-theta-to-unity-skybox/4812
https://www.stereolabs.com/products/zed-2
https://www.youtube.com/watch?v=VVznFTIDsUg
https://github.com/dirtshell/amelia_viewer
https://www.sitepoint.com/streaming-a-raspberry-pi-camera-into-vr-with-javascript/

# 4/3/2024
I acquired a raspberry pi 4 yesterday and got it to stream 720p footage over wifi. It does seem to have a delay though still. The raspberry pi 4 should be faster than the three, I found a forum post talking about how the raspberry pi 3 couldn't output the cameras specified 720p100 mode. I think the main cause  for the delay right now is the encoder. The way i currently understand it, raw data comes from the camera, goes through an encoder to create images, which then gets turned into a specific video format. I right clicked on the stream in the browser and clicked save. It kept downloading until i stopped the stream. I opened it in vlc and it showed an image then immediately closed. it was of file type .mjpg.

I got a single command to stream over rtsp using libcamera. 
```
libcamera-vid --info-text "" --level 4.2 --framerate 100 --width 1080 --height 720 -t 0 --inline -o - | cvlc  stream:///dev/stdin --sout '#rtp{sdp=rtsp://:8554/stream1}' :demux=h264
```

I was able to view it in vlc by connecting to a network stream using the url: "rtsp://hdr.local:8554/stream1"
it was choppy and very delayed but pretty good resolution. I suspect that because I'm using libcamera instead of raspivid that everything is outdated. Also, after switching to the raspberry pi 4 without re loading the os, im guessing settings are still manually set to raspberry pi 3 specs. Im gonna redo the os and make sure its fully updated. I will be using a different sd card to avoid losing all progress. Oh, also, there is a note  in the official rasspberry pi camera documentation that says the following: "On a Pi 4, you can overclock the GPU to improve performance by adding gpu_freq=550 or higher in /boot/firmware/config.txt. See the overclocking documentation for further details."

Note, i had to  turn off the share this network option in my laptops wifi adapter then turn it back on for it  to successfully connect to the pi. I also used a usb ethernet adaptere to  get it to work. 

Okay, fresh install notes: Turn off VPN while trying to connect to raspberry pi through ethernet, biggest thing to first do is just install the raspberry pi os using the handy software they provide. Change the hostname, setup the username and password, setup timezone, then enable ssh, all in the raspberry pi installerconfig. Turn off, if not already off, the network sharing on laptop wifi adapter. Then turn back on and select the ethernet port that you have connected to the pi. Connect using hostname of the raspberry pi, in this case its hdr2.local. The ssh command is: ```ssh hdr2@hdr2.local``` password is "1234" again. Once that is setup and the pi is using internet from your computer, run update and upgrade. Then install the three packages in the medium article, its the most recent. In fact, just follow that tutorial. 

Okay, thats all i got to for tonight, again, the "/etc/dhcpcd.conf" file was missing. I checked the old pi version that worked and I guess that somehow had one? Maybe I just made that file too and pasted a template? im not sure yet. Then, I remebered something about the location of the file changing so i tried to find the forum post for that. One of the responses in that post said that it was now located here: "/etc/dhcp/dhclient.conf". I checked that file on the old pi and it turns out, I did add the "nohook wpa_supplicant" stuff to it, however, the ip_address was different than any of the guides I rememeber seeing:
```
interface wlan0
    static ip_address=192.168.50.1/24
    nohook wpa_supplicant
```
it has .50. instead of .4.
I dont know if that matters or not. So in summary, the old working pi had the "/etc/dhcpcd.conf" file and the addition shown above to the "/etc/dhcp/dhclient.conf" file so Im not sure which one made it work. Gonna have to troubleshoot that tomorrow. I guess i could see if the dhcpcd5 package was installed on the old one, that was another reply in that post i mentioned above. Or maybe none of the stuff ive mentioned have been it and the solution is actually from this other forum post that looks all complicated, see "complicated network manager crap" in the bookmarks. 

Anyway, im tired and I gotta work early tomorrow, I left off on step 3 of that medium article guide for wireless router thinger. I have not edited the "/etc/dhcp/dhclient.conf" file yet. Goodnight yall

quick last note, there are two iptables packages or things on the new pi, because I ran this command from a different guide first, on accident: ```sudo apt install hostapd dnsmasq iptables``` then I ran the command for iptable stuff mentioned in the medium guide: ```sudo DEBIAN_FRONTEND=noninteractive apt install -y netfilter-persistent iptables-persistent``` So, I guess for future installs and setups, do both commands?? 

## Bookmarks used
Overclocking the raspberry 4 gpu: https://www.raspberrypi.com/documentation/computers/config_txt.html#overclocking

Guide for setting up ssh over ethernet: https://medium.com/@jrcharney/connect-your-raspberry-pi-to-your-computer-via-ethernet-4564e1e68922

Medium guide to follow for setting up raspberry pi as access point: https://vaibhavji.medium.com/turn-your-raspberrypi-into-a-wifi-router-5ade510601de

Forum post about missing /etc/dhcpcd.conf file: https://raspberrypi.stackexchange.com/questions/123897/etc-dhcpcd-conf-missing-on-rasbian

complicated network manager crap: https://raspberrypi.stackexchange.com/questions/37920/how-do-i-set-up-networking-wifi-static-ip-address-on-raspbian-raspberry-pi-os/37921#37921
