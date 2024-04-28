#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define DEV_PATH "/dev/input/event1" // Replace X with the event number of your controller

//instantiate variables
//default to full steering
    static int steerRange = 65535 ;
    static int steerOffset = 0;
    static int steerValue;
//default to 25 percent accelertion
    static int accelerateRange = 1275;
    static int accelerateOffset = 39;
    static int reverseOffset = -38;
    static int accelerateValue;

/**
* This method takes button presses and determines which steermode to use.
* @param value is the button that was pressed
*/
void changeSteerMode(int value){
switch(value){

    //button A was pressed set to standard steer
    case 288:
        steerRange = 65535;
        steerOffset = 0;
        printf("Steer Mode changed to standard\n");
    break;
    //button B was pressed set steering to 50 percent
    case 289:
        steerRange = 32767;
        steerOffset = 64;
        printf("steer Mode changed to 50 percent\n");
    break;
    //button y was pressed set steering to 25 percent
    case 291:
        steerRange = 16383;
        steerOffset = 191;
        printf("steer Mode changed to 25 percent\n");
    break;

}
}

/**
* Detects button presses and sets correct values to change the acceleration mode.
* @param value is the button pressed.
*/
void changeAccelrateMode(int value){
switch(value){
    //xbox button pressed full Speed
    case 298:
        accelerateRange = 510;
        accelerateOffset = 1;
        reverseOffset = 0;
        printf("Full Acceleration\n");
    break;
    //right paddle shifter pressed limit speed to 50 percent
    case 292:
        accelerateRange = 1020;
        accelerateOffset = 33;
        reverseOffset = -32;
        printf("Acceleration limited to 50 percent\n");
    break;
    //left paddle shifter pressed limit speed to 25 percent
    case 293:
        accelerateRange = 1275;
        accelerateOffset = 39;
        reverseOffset = -38;
        printf("Acceleration limited to 25 percent\n");
    break;

}
}

int main() {
    int fd;

    struct input_event ev;

    // Open the event device
    fd = open(DEV_PATH, O_RDONLY);
    if (fd < 0) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }


    // Read input events
    while (1) {
        if (read(fd, &ev, sizeof(ev)) < 0) {
            perror("Error reading event");
            exit(EXIT_FAILURE);
        }

        // Check if the event is a button press
        if (ev.type == EV_KEY && ev.value == 1) {
            printf("Button %d pressed\n", ev.code);
            changeSteerMode(ev.code);
            changeAccelrateMode(ev.code);
        }

        // Check if the event is an absolute axis event (such as a trigger or stick movement)
        if (ev.type == EV_ABS) {
            if (ev.code == ABS_Z) { // Brake Pressed
                printf("Brake pressed reading value: %d\n", ev.value);
                 accelerateValue = (float)ev.value / accelerateRange * 127;
                accelerateValue -= reverseOffset;
                
                if(accelerateValue > 127){
                    accelerateValue = 127;
                }
                else if (accelerateValue < 0 ){
                    accelerateValue = 0;
                }
                printf("accelerateValue: %d\n",accelerateValue);
            }
            if (ev.code == ABS_RZ) { // Clutch pressed
                printf("clutch pressed reading value: %d\n", ev.value);
            }
            if (ev.code == ABS_X) { // Steering Wheel input
                printf("Steering wheel moved reading value: %d\n", ev.value);
                steerValue = (float)ev.value / steerRange * 127;
                steerValue -= steerOffset;
                
                if(steerValue > 127){
                    steerValue = 127;
                }
                else if (steerValue < 0 ){
                    steerValue = 0;
                }
                printf("steerValue: %d\n",steerValue);

            }
            if (ev.code == ABS_Y) { // Accelerator Pressed
                printf("Gas pressed reading value: %d\n", ev.value);
                accelerateValue = (float)ev.value / accelerateRange * 127;
                accelerateValue = 127 - accelerateValue;
                accelerateValue -= accelerateOffset;
                
                if(accelerateValue > 127){
                    accelerateValue = 127;
                }
                else if (accelerateValue < 0 ){
                    accelerateValue = 0;
                }
                printf("accelerateValue: %d\n",accelerateValue);
            }
        }
    

    }

    // Close the device
    close(fd);

    return 0;
}