# 7/3/2024
Im working on fixing the connection issues.
I disabled the onboard wifi and Bluetooth modules, they are damaged anyways. I then updated everything in the network manager, nmcli. I tried readsing the syslogs, they didn't help. I tthen tried using a different power source, one that definitely put out enough amps and that fixed everything. I was ablee to get the stream running while the servo was moving . As soon as the stream started, the servo got extra jittery. gonna try and fix that now.
Okay, i got the jittery gone, using pigpio instead of gpiozero
I think I've got a loose connection on the camera cause it keeps showing a blue line. these are the errors

```
[0:36:14.187157759] [1730] ERROR IPARPI cam_helper_imx708.cpp:341 Lin/Log histogram mismatch
[0:36:14.709027073] [1730] ERROR IPARPI cam_helper_imx708.cpp:273 PDAF data in unsupported format
[0:36:14.709106592] [1730] ERROR IPARPI cam_helper_imx708.cpp:341 Lin/Log histogram mismatch
[0:36:14.797965036] [1730] ERROR IPARPI cam_helper_imx708.cpp:273 PDAF data in unsupported format
[0:36:15.775219961] [1730] ERROR IPARPI cam_helper_imx708.cpp:273 PDAF data in unsupported format
[0:36:15.775277980] [1730] ERROR IPARPI cam_helper_imx708.cpp:341 Lin/Log histogram mismatch
[0:36:15.875202387] [1730] ERROR IPARPI cam_helper_imx708.cpp:273 PDAF data in unsupported format
[0:36:16.030813813] [1730] ERROR IPARPI cam_helper_imx708.cpp:273 PDAF data in unsupported format
[0:36:16.158928832] [1730] ERROR IPARPI cam_helper_imx708.cpp:273 PDAF data in unsupported format
```

todo, get better power sourcez

okay on restart, you gotta run ```sudo pigpiod``` to run and servo stuff

# 7/5/2024
Alright, gotta make sure the computer connected to the pi has the connection as private and not public, spent a long time looking at wireshark logs to find this. Servo is more smooth than it was, it moves with the headset, up and down, pretty smooth.