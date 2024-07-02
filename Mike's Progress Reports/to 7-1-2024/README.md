## Unity Project
I have setup the c++ plugin for unity. It still needs quite a bit of work, like a reset button to get the connection in the game to reset and not have it crash or have weird errors. I need to get the disable functionality to work on it as well so I can destroy the current stream going in. Those are my next steps but the basic setup has been done.

The steps to get it working went as follows.
1. get a visual studio project setup to create a dll that can run as a native plugin for unity. 

    --this was a little bit more of a hassle than I had been hoping it would be it took me absolutely forever to get it all running and setup correctly and the plugin only builds for windows desktop VR, I could probably build it for other platforms but at the moment that is all it supports.--

I followed the setup C++ Native Plugin video to get the initial setup done, the I used vcpkg to be my package manager and used that to install ffmpeg into the C++ plugin. It took me a couple hours and multiple different videos to figure out exactly how to do this but then it was as simple as writing vcpkg add port ffmpeg after I had gotten vcpkg installed.

Which was stupid because I should have just written that and not done as much research as I did and just tried that because I did a ton of internet searches to figure out how to import it correctly and was unable to find any good sources and then I said whatever and went for it and once I ran the build the first time it brought in ffmpeg and instantly started working. I was so pissed. Also the main code for the C++ plugin was from a Unity post from a unity member, 
https://github.com/keijiro/TextureUpdateExample.
I first got this working in unity and then imported ffmep and started working with videos.

2. once the project was setup I stated writing the code to get the video to run. I stated with a static file and followed the video below C++ real time processing with FFmpeg series.

This was time consuming as well and took a while to get it working however It was a lot more progress and quicker progress than what I had been doing previously so I felt a lot of success. Many of the errors I had came from needing the dimensions of the texture I was writing to in unity to match the texture that the videos were outputting.

There was also a weird issue of when I converted the video to RGBA data for the display it rotates it 90 degrees. I'm still working on this issue a bit but if I cannot figure out how to do it in code I can always just rotate the plane the texture is on. Which will probably be easier to do.

3. Once I got it working with a static video I then had to get it to read from a TCP stream, again I took a couple of days researching this and trying to figure out how I wanted to connect to the tcp port, but then it was as easy as a couple of lines of code and changing the filename to the port I wanted it to listen on.

Luckily all the code for reading the video worked just the same on this as it did on a static stream and from there I got a live camera video streaming into Unity.


# Useful code snipets
These next three lines were used to stream video over TCP
This line streams a video file

```ffmpeg -re -i test.mp4 -f mpegts tcp://127.0.0.1:8000\?listen```

this line shows how to find all the devices on your computer compatible with ffmpeg and came from this website https://www.bogotobogo.com/VideoStreaming/ffmpeg_webcam_capture_Windows.php

```ffmpeg -list_devices true -f dshow -i dummy```

this line shows how to get a cameras options from your computer for ffmpeg

```ffmpeg -f dshow -list_options true -i video="Surface Camera Front"```

this next line will stream that camera over TCP

```ffmpeg -f dshow -s 1280x720 -r 30 -vcodec mjpeg -i video="Surface Camera Front" -f mpegts tcp://127.0.0.1:8000\?listen```

this next line can be used to play that stream

```ffplay.exe tcp://127.0.0.1:8000 -fflags nobuffer -flags low_delay -framedrop```

With all this you might be able to recreate what I did a bit easier than it was for me to be able to create it in the first place.

# Helpful Links
setup C++ Native plugin- https://www.youtube.com/watch?v=qljLhXfVt78&list=PLTsECvXbzBWo7IgwtQoDesWjkIrSkWBH3&index=1

Affect a texture with a C++ plugin - https://www.youtube.com/watch?v=C6V1f86x058

C++ real time processing with FFmpeg - https://www.youtube.com/playlist?list=PLKucWgGjAuTbobNC28EaR9lbGQTVyD9IS

how to stream a camera over ffmpeg https://www.bogotobogo.com/VideoStreaming/ffmpeg_webcam_capture_Windows.php