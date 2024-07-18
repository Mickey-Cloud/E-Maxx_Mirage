# Steering Wheel Code Changelog

# 4/28/2024
 Before today steering wheel code just reads inputs and displays the values in the terminal. After work today the steering wheel code now can interrperet data from the wheel and correclty assign a value to a potentiometer. There are 3 speed levels 25 percent 50 percent and full speed. The program defaults to 25 percent. The user can use the left paddle to set to 25 right to 50 and xbox button to full speed. The steering can also be changed by pressing a for normal steering. b for 50 percent steering meaning the user only has to turn the wheel 50 percent for full steering effect and y for 25 percent steering. Currently these values are printed to the terminal and are not actually transmitted through i2c yet.

 # 4/29/2024
 Today I implemented the I2C code into the steering test code. You can now control the transmitter using the steering wheel. There is still some fiddling with the transmitter to get it to work properly. The car still moves too quickly and will need more adjusting. This was tested using a new wiring method of using some 4 100kohm potentiometers to limit voltage. This did help with granularity. 

 I also began working on a new board schematic that uses this new design and also will have headers to directly interface with the gpio pins on the raspberry pi 3. Will continue to work on this throughtout the week.

 # 5/3/2024
 Finalized board desing. Sent board design to PCB way waiting on quote and ETA for new board. I will also add the 12v to 5v power supply so that the raspberry pi 3 can be powered using the same power cord that the transmitter is using.

 update the power supply works now the transmitter and raspberry pi share a power supply

 # 5/7/2024
 Turns out PCBway is going to be expensive and slow to provide our board. Made the decision to order 3 boards from OSH Park and solder ourselves. Should be possible to use components already obtained but I may purchse some potentiometers. Our PCB should be After Dark so they will look like this

  ![alt text](<After Dark-1.jpg>) 
  
  which is sick. Later this week I plan on doing some tests with radio interference. I also started the Bill of materials so that we can keep track of expenses.

  # 5/8/2024
  Today I spent hours trying to figure how how to control the force feedback on the steering wheel. Turns out I needed to update the linux kernal. Once updated I was finally able to use a command to move the wheel.

  https://www.kernel.org/doc/html/v4.13/input/ff.html

  This website supplies documentation on how to write a program to control the rumble. I will write the program later but now I have confirmation that force feedback will work. I was able to supply constant force as well as rumble and a spring like motion which pushes the wheel back to its resting state.

  # 5/13/2024
  Started writing force feedback code. My test code is in ForceFeedbackTest.c. Currently the program should start force feedback and enable a spring effect. I do not know if it currently works as I have not had time to run to the lab yet but I will try to get to the lab before our group meets on wednesday.

  Looks like I did have time to make into the lab later in the day. I combined the code for both steering and force feedback into a new file called SteerandForce.c. This new program should maintain all the funcitonality of steering before with the added force feedback. The code still needs to be cleaned up a lot. The force feedback functionality consists of 4 different effects. Effect 0 is a spring effect which plays whenever the car is moving and will change in intensity depending on the speed of the car. I will need to tweak this as it is not perfect yet. Effect 1 is a damping effect wich is active when the car is still. Effect 2 is a light rumble which plays when the user selects the second speed mode. Effect 3 is a strong rumble which plays when the user selects the max speed mode. Values will need to be adjusted but baseline functionality is basically complete. I plan on showing the team as well as Ken on wednesday.

  # 5/23/2024
  Started refining driving and have an ETA on new board. I plan on working on refining the driving experience as well as soldering the new board next week. 

  # 5/28/2024
  Sad day board blew up again. The fire was cool though. It was discouraging and sad that the third design does not work. I believe it was shorted between SDA and GND. However we did continuity tests and it should have worked. Kyla is going to attempt to solder another one to see if we can get it to work. I will work on designing a simplified new version 4. This one will be super simple and will basically act as a breadboard that models our other circuit exactly. ![alt text](<Version3_soldered board blown up-1.jpg>)

  # 5/29/2024
  I have finished designing a super simple revision 4. This design will simply connect two of the adafruit breakout boards with 4 extra potentiometers. This was the simplest design I could come up with as it uses all known working parts as well as models the circuit on our working breadboard exactly. I am currently waiting for other people to check my work and will hopefully have it ordered by the end of the week. Fingers crossed this is the last board we need to make.
  ![alt text](rev4_design-1.png)

  # 5/30/2024
Just ordered Rev4 after making some slight changes to the design. I ordered it in purple to hopefully get the boards quicker.
![alt text](<rev4 final design-1.png>)

# 6/3/2024
Began work on 3d design. So far I have just an outline of the back of the transmitter. I will need more measurements to complete the design.


# 6/4/2024
Kyla and I tried another v3 and got some success. It worked for a short period of time but quickly stopped working. We are going to start 3d designing the enclosure while we wait for v4 to come in the mail. We plan on having designs in two weeks.

# 6/6/2024
Started work on the 3d Print enclosure. I have no 3d modelling experience but I wanted to make all of this by scratch. I have started by making postes and a little holder for the raspberry pi. I only want  the usb ports to be accessible.

![alt text](<Starting 3D Enclosure.png>)

I will work on this more this weekend and get some hard measurements. I expect my rev 4 board to come sometime mid next week.

# 6/10/2024
Rev 4 finally came in the mail today.
![alt text](<Rev 4 board.jpg>)
I didn't have the potentiometers to test today but I did use my old digital potentiometers and performed a voltage test on the new board and it looks promising. So far I was able to prove that I can communicate using the raspberry pi to commnicate and change the voltage properly. I used a 1v test voltage. We are meeting wednesday to discuss the camera system and we also plan on adding the voltage regulator potentiometers and we should be able to have a complete board and steering control by wednesday! You can see my test with the DS3502's below.

![alt text](<Rev 4 Voltage test.jpg>)

# 6/12/2024
The rev 4 board woks great! I will start working on the enclosure but it works great!
![alt text](REV_4_FInal.jpg)

# 6/28//2024
I am now back from my vacation and have working on creating a better 3d model that fits the existing transmitter. This is it currently.
![alt text](<3d Enclosure better.png>) I plan on working on it more this weekend.

# 7/2/2024
Today I printed my test design and it turns out I was way off on the dimensions.
![alt text](IMG_1518.png)
I have already begun working on a rev 2 that I am checking all dimensions for. So far it is much cleaner than the first design.
![alt text](<3D enclosure rev2 partial.png>)
I will finish working on this and will hopefully have a new one printed later this week or next week.

# 7/4/2024
Finished my new design today you can see the pictures of it here. I am waiting to get some confirmation measurements before I print it.
![alt text](<Enclosure rev 2 complete front.png>)
![alt text](<Enclosure rev 2 complete side.png>)
![alt text](<Enclosure rev 2 complete back.png>)

I plan to have this checked and printed soon and hopefully early next week I can actually assemble it. Once assembled I might create another piece that would clasp on the front. This is not a priority but would be nice to have.

# 7/9/2024
Today I got my new enclosure. It did not fit perfectly however it fit well enough. Honestly I might just leave it as is. I will take it apart and clean up some of the wiring to help with crosstalk but we did test it briefly and it seemed to be working. Steering worked well driving didn't but thats likely due to the driving needing to be adjusted. 
![alt text](<EnclosureREV3Front.jpg>)
![alt text](<EnclosureREV3Back.jpg>)

I am going to look into creating a new enclosure to make it perfect but I will first focus on making the driving experience better. I was able to make the pi boot the program automatically or at least a think so.

