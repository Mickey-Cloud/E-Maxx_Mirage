//connect using putty
Hostname: hdr3.local
login as: hdr
password: 1234

//The hotspot starts on reboot!!!
//Hotspot
SSID= Mikes Pi
wpa passphrase=MyP!12345

//This starts the hotspot
sudo nmcli device wifi hotspot ssid 'Mikes Pi' password 'MyP!12345'