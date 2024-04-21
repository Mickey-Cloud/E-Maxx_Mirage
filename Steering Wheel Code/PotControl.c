#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>


	int file_i2c;
    int file_i2c1;
    sem_t sem;
	unsigned char buffer[60] = {0};

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


	void writeI2c(int device, int length){
        printf("Attempt to write.\n");
	if (write(device, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
        //int test = write(device, buffer, length);
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
    }

    }

    int main(){
        connectI2c();
        //initialize starting conditions
        //pot 1 set to 2.5v
        buffer[0] = 0x00;
        buffer[1] = 63;
        writeI2c(file_i2c,2);
        //set pot 2 tto 2.5v
        writeI2c(file_i2c1,2);

        int potNum;
        int Value;
        
        while(1){
           printf("Enter Pot number: ");
           scanf("%d", &potNum);
           if(potNum == 1 || potNum ==2){
           printf("You entered pot: %d\n", potNum);
           printf("Enter Value between 51 and 76, 51 being lowest 76 highest 63 neutral");
           scanf("%d" , &Value);
           printf("You entered: %d\n", Value);

            //build buffer to write
            buffer[0] = 0x00;
            buffer[1] = Value;
            //write to correct pot
            if(potNum ==1){
                writeI2c(file_i2c,2);
            }
            else{
                writeI2c(file_i2c1,2);
            }
           
           //else{printf("Invalid Value: %d\n", potNum);}
           }
           else{printf("Invalid potNum: %d\n", potNum);}
        }
    }