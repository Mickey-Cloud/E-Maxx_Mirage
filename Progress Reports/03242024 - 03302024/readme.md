# 3/24/2024
Completely reset the raspberry pi, it got too much of a hastle to manually install every package so we downloaded an os with all the recommended software. 14GB in size compared to less than a gig.

# 3/25/2024
Reset raspberry pi again, can't login to it headless on first start. Going through the official raspberry pi imager, I turned on ssh and set the username and password. 
```
hostname: hdr.local
username: hdr
password: 1234
```
in order to connect to the raspberry pi from ssh, my vpn needs to be turned off. Finally got connected to it through ethernet. Now I'm upgrading all the packages.

the following was put in file /etc/hostapd/hostapd.conf
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
ssid=HDR
wpa_passphrase=shit_9#*
```

Hey, I successfully got it working, a wifi network with an SSID of HDR shows up now.
I've got my computer connected to the wifi network. It connected using dhcp. But i went in and manually configured my ip settings to the following:
```
IPv4: manual
ip address: 192.168.50.50
subnet mask: 255.255.255.0
gateway: 192.168.50.1
preferred dns: 0.0.0.0
```

I tried connecting to hdr.local using ssh in putty and it worked! I can connect to it over wifi now!
Oh, note, i disabled the ethernet adapter on my laptop before connecting to the pi, didn't want to create a loop.
There is an issue with the raspberry pi rebooting and the ssid not showing up.