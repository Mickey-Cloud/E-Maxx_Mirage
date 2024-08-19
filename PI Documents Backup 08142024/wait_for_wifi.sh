#!/bin/bash

sudo pigpiod
sudo pinctrl set 23 op
sudo pinctrl set 23 dl
status=$(sudo nmcli -f GENERAL.STATE con show Hotspot)
echo $status
while ! grep -q activated <<<"$status";
do
	status=$(sudo nmcli -f GENERAL.STATE con show Hotspot)
done
sudo pinctrl set 23 dh
