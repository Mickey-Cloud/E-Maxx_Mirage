# 3/17/2024
Have started trying to setup the raspberry pi as an accesspoint
Started following the tutorial in the last bookmarks readme
Had issues with /etc/dhcpcd.conf file not existing. 
Ran sudo apt update and sudo apt upgrade. Lots of libraries were out of date
Can't plug raspberry pi into usb power while also trying to connect to it through serial uart
Use separate power supply. Usb power might not have enough juice, amps. 
apparently the rasberry pi os i installed doesn't come with dhcpcd library
i installed it with sudo apt install dhcpcd5

# 3/20/2024
Decided to switch to a peer to peer network instead of a local area network. The computer only needs to connect to the raspberry pi.



## Useful Bookmarks
https://vaibhavji.medium.com/turn-your-raspberrypi-into-a-wifi-router-5ade510601de
https://cdn-learn.adafruit.com/downloads/pdf/setting-up-a-raspberry-pi-as-a-wifi-access-point.pdf
https://raspberrypi.stackexchange.com/questions/37920/how-do-i-set-up-networking-wifi-static-ip-address-on-raspbian-raspberry-pi-os/37921#37921
https://pimylifeup.com/raspberry-pi-wireless-access-point/
https://www.raspberrypi.com/documentation/computers/configuration.html