#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/ff.h>

#define DEVICE_PATH "/dev/input/event2"

void initialize_effects(int fd) {
    struct ff_effect effect_spring, effect_light_rumble, effect_aggressive_rumble;

    // Initialize the spring effect
    memset(&effect_spring, 0, sizeof(struct ff_effect));
    effect_spring.type = FF_SPRING;
    effect_spring.id = -1; // Autopilot ID assignment
    effect_spring.u.spring.constant = 5000; // Spring constant
    effect_spring.u.spring.coef = 0; // Not used for Spring type

    // Upload the spring effect to the device
    if (ioctl(fd, EVIOCSFF, &effect_spring) == -1) {
        perror("Error uploading spring effect");
        exit(EXIT_FAILURE);
    }

    // Initialize the light rumble effect
    memset(&effect_light_rumble, 0, sizeof(struct ff_effect));
    effect_light_rumble.type = FF_RUMBLE;
    effect_light_rumble.id = -1; // Autopilot ID assignment
    effect_light_rumble.u.rumble.strong_magnitude = 0;
    effect_light_rumble.u.rumble.weak_magnitude = 2000; // Light rumble

    // Upload the light rumble effect to the device
    if (ioctl(fd, EVIOCSFF, &effect_light_rumble) == -1) {
        perror("Error uploading light rumble effect");
        exit(EXIT_FAILURE);
    }

    // Initialize the aggressive rumble effect
    memset(&effect_aggressive_rumble, 0, sizeof(struct ff_effect));
    effect_aggressive_rumble.type = FF_RUMBLE;
    effect_aggressive_rumble.id = -1; // Autopilot ID assignment
    effect_aggressive_rumble.u.rumble.strong_magnitude = 10000; // Strong rumble
    effect_aggressive_rumble.u.rumble.weak_magnitude = 0;

    // Upload the aggressive rumble effect to the device
    if (ioctl(fd, EVIOCSFF, &effect_aggressive_rumble) == -1) {
        perror("Error uploading aggressive rumble effect");
        exit(EXIT_FAILURE);
    }

    printf("Effects uploaded successfully.\n");
}

void start_effect(int fd, int effect_id) {
    struct input_event play;

    play.type = EV_FF;
    play.code = effect_id;
    play.value = 1;

    // Send a "play" event to start the effect
    if (write(fd, &play, sizeof(play)) == -1) {
        perror("Error starting effect");
        exit(EXIT_FAILURE);
    }

    printf("Spring effect started.\n");
}

int main() {
    int fd;

    // Open the force feedback device
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd == -1) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    // Initialize all effects
    initialize_effects(fd);

    start_effect(fd, 1);

    while(1){
        //keeps program running
    }
    // Close the device
    close(fd);

    return 0;
}
