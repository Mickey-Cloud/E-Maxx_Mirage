#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <pthread.h> // Include the pthread library for mutex support

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
//I2C communication values
	int file_i2c;
    int file_i2c1;
	unsigned char buffer[60] = {0};
    int CurrentSteer;
    int CurrentDrive;

//mutex lock
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to acquire the lock
void acquire_lock() {
    pthread_mutex_lock(&buffer_mutex);
}

// Function to release the lock
void release_lock() {
    pthread_mutex_unlock(&buffer_mutex);
}

    /**
    *connects to the digital potentiometers
    */
void connectI2c(){
	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return;
	}
    //open bus for second device
    	if ((file_i2c1 = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return;
	}
	
	int addr = 0x28;          //<<<<<The I2C address of the slave
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave 1.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return;
	}
    	 addr = 0x29;          //<<<<<The I2C address of the second slave
	if (ioctl(file_i2c1, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave 2.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return;
	}
    }

/**
* write to the digital potentiometer
*/
void writeI2c(int device, int length, int data){
    acquire_lock();
    printf("Attempt to write.\n");
    buffer[0] = 0x00;
    buffer[1] = data;

    //checks to see if its already written if written then it will exit and not write
    if(device == file_i2c && data == CurrentSteer){
        return;
    }
        if(device == file_i2c1 && data == CurrentDrive){
        return;
    }
    //write data
	if (write(device, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{

		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
        
    }
    else{
        printf("Transmitted: 0x%x%x\n", buffer[0],buffer[1]);
        if(device== file_i2c){
            CurrentSteer = data;
        }
        else if(device==file_i2c1){
            CurrentDrive = data;
        }
    }
    ioctl(device, I2C_RDWR, 0);
    release_lock();

    }
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
        steerOffset = -64;
        printf("steer Mode changed to 50 percent\n");
    break;
    //button y was pressed set steering to 25 percent
    case 291:
        steerRange = 16383;
        steerOffset = -191;
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
        connectI2c();
        //initialize starting conditions
        //pot 1 set to 2.5v
        writeI2c(file_i2c,2,63);
        //set pot 2 tto 2.5v
        writeI2c(file_i2c1,2,63);

    // Open the event device
    fd = open(DEV_PATH, O_RDONLY);
    if (fd < 0) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }


    // Read input events
    while (1) {
        //usleep(10000);
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
                writeI2c(file_i2c1,2,accelerateValue);
            }
            if (ev.code == ABS_RZ) { // Clutch pressed
                printf("clutch pressed reading value: %d\n", ev.value);
            }
            if (ev.code == ABS_X) { // Steering Wheel input
                printf("Steering wheel moved reading value: %d\n", ev.value);
                steerValue = (float)ev.value / steerRange * 127;
                steerValue = 127 - steerValue;
                steerValue -= steerOffset;
                
                if(steerValue > 127){
                    steerValue = 127;
                }
                else if (steerValue < 0 ){
                    steerValue = 0;
                }
                printf("steerValue: %d\n",steerValue);
            writeI2c(file_i2c,2,steerValue);


            }
            if (ev.code == ABS_Y) { // Accelerator Pressed
                printf("Gas pressed reading value: %d\n", ev.value);
                accelerateValue = (float)ev.value / accelerateRange * 127;
                accelerateValue = 127 - accelerateValue;
                accelerateValue -= accelerateOffset;
                
                if(accelerateValue > 66){
                    accelerateValue = 66;
                }
                else if (accelerateValue < 0 ){
                    accelerateValue = 0;
                }
                printf("accelerateValue: %d\n",accelerateValue);
                writeI2c(file_i2c1,2,accelerateValue);
            }
        }
    

    }

    // Close the device
    close(fd);

    return 0;
}