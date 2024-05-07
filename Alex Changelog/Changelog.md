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