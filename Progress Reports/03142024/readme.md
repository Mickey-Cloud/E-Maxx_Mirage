# 3/14/2024
Moved away from using a wireless 2.4 GHz radio transciever. The affordable radio control modules were not capable of meeting our speed needs. We've now started researching wifi. We are going to try setting up the Raspberry Pi as a local network access point. The hostapd software needs to be installed, it will create the access point. We may not need the dhcpcd library, we don't need to continuosly automatically assign dynamic IP addresses. We should only need two static IP addresses. One for the Raspberry Pi and one for the control computer. We are probably going to have to use a external wifi dongle designed for a large antenna. 

## Useful Bookmarks:
https://forums.raspberrypi.com/viewtopic.php?t=357335
https://raspberrypi-guide.github.io/networking/create-wireless-access-point
https://forums.raspberrypi.com/viewtopic.php?t=323215
https://forums.raspberrypi.com/viewtopic.php?t=271865