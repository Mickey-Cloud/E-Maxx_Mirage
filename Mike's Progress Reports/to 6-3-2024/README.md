## Arduino Setup
For now I am just streaming the camera to the computer with the command
~~~
rpicam-vid --info-text "" --level 4.2 --framerate 30 --width 1280 --height 720 --denoise cdn_off -t 0 --inline --listen -o tcp://0.0.0.0:8000
~~~

This allows my computer to connect with the raspberry pi camera and I don't have to make sure the local wifi and the peer to peer is set up correctly.

## Unity Project
Switched over to another branch but am now working within murphys nothing repo because I wanted to work within the same project. After much research and testing into useing ffmpeg.autogen with ffmpeg I have decided that it is no longer possible and have told my team there is a blocker on that. Murphy caught that and has created a workaround to using ffmpeg to get the camera stream within unity. However with some of my other plans for how I would like to edit the scene I will need to get FFmpeg working with unity. Now that Murphy has set that up I am looking to build a custom native C++ plugin that can run the ffmpeg code. To that end I have created a dll that is currently connecting and working so I am now able to use the c++ code to edit the unity application. 

I thought this would be a lot harder than it is which is why i've been looking to use a ffmpeg library but none existed for free. However, since murphy toook this weight off my sholder I've been looking into this and it doesn't seem that bad.

The real trick will be to see how I can get the ffmpeg code working :)

# Helpful Links
setup C++ Native plugin- https://www.youtube.com/watch?v=qljLhXfVt78&list=PLTsECvXbzBWo7IgwtQoDesWjkIrSkWBH3&index=1

Affect a texture with a C++ plugin - https://www.youtube.com/watch?v=C6V1f86x058

C++ real time processing with FFmpeg - https://www.youtube.com/playlist?list=PLKucWgGjAuTbobNC28EaR9lbGQTVyD9IS
