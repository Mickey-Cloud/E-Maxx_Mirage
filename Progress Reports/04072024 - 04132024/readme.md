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