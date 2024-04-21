#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define DEV_PATH "/dev/input/event1" // Replace X with the event number of your controller

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
        }
                // Check if the event is an absolute axis event (such as a trigger)
        if (ev.type == EV_ABS) {
            if (ev.code == ABS_Z) { // Left trigger
                printf("Left trigger: %d\n", ev.value);
            }
            if (ev.code == ABS_RZ) { // Right trigger
                printf("Right trigger: %d\n", ev.value);
            }
        }
        // Check if the event is an absolute axis event (such as a trigger or stick movement)
        if (ev.type == EV_ABS) {
            if (ev.code == ABS_Z) { // Left trigger
                printf("Left trigger: %d\n", ev.value);
            }
            if (ev.code == ABS_RZ) { // Right trigger
                printf("Right trigger: %d\n", ev.value);
            }
            if (ev.code == ABS_X) { // Left stick X-axis
                printf("Left stick X: %d\n", ev.value);
            }
            if (ev.code == ABS_Y) { // Left stick Y-axis
                printf("Left stick Y: %d\n", ev.value);
            }
            if (ev.code == ABS_RX) { // Right stick X-axis
                printf("Right stick X: %d\n", ev.value);
            }
            if (ev.code == ABS_RY) { // Right stick Y-axis
                printf("Right stick Y: %d\n", ev.value);
            }
        }
    

    }

    // Close the device
    close(fd);

    return 0;
}