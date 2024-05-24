# 4/9/2024
Was able to ssh into raspberry pi 4 over lan first try. Looking at the medium article now, I don't remember doing any ip masquerading. I've got an annoying issue where everytime i go to a different window from the ssh terminal, i lose connection to the raspberry pi. OH MY GOD, i finally found the exact tutorial I used: "https://github.com/t2age/wl-p2p-wifi/tree/master/tutorial/tuto1"

What I did:
added to "/etc/dhcp/dhclient.conf":
```
interface wlan0  
static ip_address=192.168.50.1/24  
nohook wpa_supplicant  
```

created file "/etc/hostapd/hostapd.conf" and added (note, I did this before the unmask and enable commands, this file might exist if these commands are run first):
```
interface=wlan0
driver=nl80211
hw_mode=g
channel=6
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
ssid=HDR2
wpa_passphrase=shit_9#*
```

ran the following commands (like i said earlier, this should probably before editing the hostapd.conf file): 
```
sudo systemctl unmask hostapd.service
sudo systemctl enable hostapd.service
```

I opened "/etc/default/hostapd" and changed ```#DAEMON_CONF=""``` to ```DAEMON_CONF="/etc/hostapd/hostapd.conf"``` (make sure to uncomment by removing #)

check the file "/etc/init.d/hostapd" and make sure this the DAEMON_CONF line is uncommented and has this: ```DAEMON_CONF=/etc/hostapd/hostapd.conf```

Then I started the hostapd service: ```sudo service hostapd start``` and restarted the pi


Okay, now, after rebooting, no ssid shows up but when i run ```sudo systemctl status hostapd``` it says running. AHHH HAAA! After stopping hostapd and restarting, using these commands:
```
sudo systemctl stop hostapd
sudo systemctl restart hostapd
```
HDR2 now shows up!! So its the problem we were having with the raspberry pi 3, hostapd is starting too early while the system is booting so we just need to add a delay! 
Also, it kept disconnecting from ssh due to the ethernet port on my laptop because a ethernet to usb adapater worked great and didn't disconnect once.

# 4/12/2024
Got the delay in and the ssid shows up raspberry pi startup. Had too many issues using the hostapd package so i called it a night

# 4/13/2024
Decide to restart again completely, I wiped the pi and updated everything. Okay, just looking at the raspberry pi documentation main page, I found an updated way to turn the pi into an accesspoint. Took less than 30 minutes. I wasted all that time trying to do the same thing using outdated packages meant for an older version of raspberry pi os. I feel stupid. Also, I hooked up another wireless adapter to my laptop so I can be connected to the pi and the internet at the same time.

Got the camera stream working! Still seems just as delayed. Alright, I added the following lines to "/boot/firmware/config.txt": ```force_turbo=1```

I guess that hotspot command doesn't start the access point back up on restart:
oh yeah, that original command was:
```sudo nmcli device wifi hotspot ssid HDR3 password shit_9#*```

Okay, i think i enabled autostart and set the priority of the hostpot network to 100, gonna try rebooting now. YAY! it works, also, with another network adapter on my laptop, it just auto connected to HDR3   

Still got lag after the force turbo setting. Oof, the chip is getting pretty hot, i should put a heatsink on it. I dont have one with me right now and im at a coffee shop so i put one of my metal dnd dice on it, lol.    

I added the following line to the "/boot/firmware/config.txt" file: ```gpu_freq=550```

I got it working now with tcp instead of rtsp. Use the following two commands:
On pi:
```rpicam-vid --info-text "" --level 4.2 --framerate 100 --width 1080 --height 720 --denoise cdn_off -t 0 --inline --listen -o tcp://0.0.0.0:8000```

In vlc:
```tcp/h264://hdr3.local:8000```

I adjusted some settings in vlc to make it faster. According to the pi stream output, its outputting 100fps pretty good, heres a snapshot:
```
#1758 (100.18 fps) exp 9540.00 ag 5.57 dg 1.03
#1759 (100.17 fps) exp 9540.00 ag 5.57 dg 1.03
#1760 (100.10 fps) exp 9540.00 ag 5.57 dg 1.03
#1761 (100.24 fps) exp 9540.00 ag 5.63 dg 1.03
#1762 (100.16 fps) exp 9540.00 ag 5.63 dg 1.03
#1763 (100.19 fps) exp 9540.00 ag 5.63 dg 1.03
#1764 (100.12 fps) exp 9540.00 ag 5.63 dg 1.03
#1765 (100.22 fps) exp 9540.00 ag 5.63 dg 1.03
#1766 (100.17 fps) exp 9540.00 ag 5.63 dg 1.03
#1767 (100.11 fps) exp 9540.00 ag 5.63 dg 1.03
#1768 (100.20 fps) exp 9540.00 ag 5.63 dg 1.03
#1769 (100.21 fps) exp 9540.00 ag 5.57 dg 1.03
#1770 (100.17 fps) exp 9540.00 ag 5.57 dg 1.03
#1771 (100.17 fps) exp 9540.00 ag 5.57 dg 1.03
#1772 (100.08 fps) exp 9540.00 ag 5.57 dg 1.03
#1773 (100.26 fps) exp 9540.00 ag 5.57 dg 1.03
#1774 (100.17 fps) exp 9540.00 ag 5.57 dg 1.03
#1775 (100.19 fps) exp 9540.00 ag 5.57 dg 1.03
#1776 (100.16 fps) exp 9540.00 ag 5.57 dg 1.03
#1777 (100.16 fps) exp 9540.00 ag 5.57 dg 1.03
#1778 (100.19 fps) exp 9540.00 ag 5.57 dg 1.03
#1779 (100.17 fps) exp 9540.00 ag 5.57 dg 1.03
#1780 (100.16 fps) exp 9540.00 ag 5.57 dg 1.03
#1781 (100.18 fps) exp 9540.00 ag 5.63 dg 1.03
#1782 (100.14 fps) exp 9540.00 ag 5.63 dg 1.03
#1783 (100.21 fps) exp 9540.00 ag 5.63 dg 1.03
#1784 (100.16 fps) exp 9540.00 ag 5.63 dg 1.03
#1785 (100.18 fps) exp 9540.00 ag 5.63 dg 1.03
#1786 (100.18 fps) exp 9540.00 ag 5.63 dg 1.03
#1787 (100.17 fps) exp 9540.00 ag 5.63 dg 1.03
#1788 (100.17 fps) exp 9540.00 ag 5.63 dg 1.03
#1789 (100.17 fps) exp 9540.00 ag 5.57 dg 1.03
#1790 (100.17 fps) exp 9540.00 ag 5.57 dg 1.03
```

I believe VLC is the bottleneck here, I'm trying OBS now

Holy toleto!! I was using the wrong resolution. Its working good now. 720p is not 1080 by 720, its 1280 by 720, im stupid.

so heres the command for the pi:

```rpicam-vid --info-text "" --level 4.2 --framerate 100 --width 1280 --height 720 --denoise cdn_off -t 0 --inline --listen -o tcp://0.0.0.0:8000```

im gonna try making it faster, oh yeah, giving up on OBS for now. Im trying to find a way to measure latency in vlc. It is much faster than what it was


Ive tried using ffplay, seems faster: 

```.\ffplay.exe tcp://hdr3.local:8000 -fflags nobuffer -flags low_delay -framedrop```

also got udp working:

picommand, 10.42.0.96 is the ip address of my laptop that the raspberry pi assigned:
```rpicam-vid --info-text "" --level 4.2 --framerate 90 --width 1280 --height 720 --denoise cdn_off -t 0 --inline -o udp://10.42.0.96:8000```

ffplay command, 10.42.0.1 is the gateway address of the raspberry pi, for some reason, using 10.42.0.96 also worked:
```.\ffplay.exe udp://10.42.0.1:8000 -fflags nobuffer -flags low_delay -framedrop```

Both of these worked, however, ffplay showed that it was locked at 25fps. ffplay had a lower latency though than vlc. Still can't get vlc to connect using udp. 

try and find a way to measure fps necxt time for ffplay

TLDR: use these commands for the fastest current stream:

Raspberry pi:

```rpicam-vid --info-text "" --level 4.2 --framerate 90 --width 1280 --height 720 --denoise cdn_off -t 0 --inline --listen -o tcp://0.0.0.0:8000```

FFPlay, be in same folder as ffplay.exe

```.\ffplay.exe udp://@:8000 -fflags nobuffer -flags low_delay -framedrop```

FFPlay stats:
![Alt text](ffplay.jpg?raw=true "FFPlay Statistics")

![Alt text](vlc_codec.jpg?raw=true "VLC Codec Info")

![Alt text](vlc_statistics.jpg?raw=true "VLC Statistics")

## Useful bookmarks:
Turn on autostart for hotspot:
https://www.raspberrypi.com/tutorials/host-a-hotel-wifi-hotspot/#:~:text=Configure%20hotspot%20network&text=When%20your%20Raspberry%20Pi%20boots,higher%20than%20any%20other%20connection.

Force turbo:
https://www.raspberrypi.com/documentation/computers/config_txt.html#force_turbo

wireless hotspot: 
https://www.raspberrypi.com/documentation/computers/configuration.html#host-a-wireless-network-on-your-raspberry-pi

TCP setup:
https://forums.raspberrypi.com/viewtopic.php?t=350676

ffplay download link for windows:
https://github.com/BtbN/FFmpeg-Builds/releases

