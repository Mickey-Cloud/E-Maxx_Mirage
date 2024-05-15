# 4/18/2024
New commands to get smooth video at 90 FPS! also, I added ffplay.exe to my path folder

For player:

```ffplay.exe -framerate 90 tcp://hdr3.local:8000 -fflags nobuffer -flags low_delay -framedrop```

For raspberry pi:

```rpicam-vid --info-text "" --level 4.2 --framerate 90 --width 1280 --height 720 --denoise cdn_off -t 0 --inline --listen -o tcp://0.0.0.0:8000```