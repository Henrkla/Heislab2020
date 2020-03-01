#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door.h"
#include <time.h>

static DOOR_STATE currentDoorState = DOOR_CLOSED;
time_t start_time = 0;
static int timer_is_on = 0;



void door_open() {
	if (hardware_floor_check() != -1) {
		hardware_command_door_open(1);
		currentDoorState = DOOR_OPEN;
	}
};

void door_close() {
	hardware_command_door_open(0);
	currentDoorState = DOOR_CLOSED;
}

int door_obstruction_check() {
	return (hardware_read_obstruction_signal() && currentDoorState ==DOOR_OPEN);
}



int timer_expired() {
	return (time(NULL) - start_time > DOOR_DELAY);
	//return (difftime(time(NULL), start_time) > 3);
}

void timer_reset() {
	start_time = time(NULL);
}

void timer_on() {
	if (!timer_is_on) {
		timer_reset();
	}
	timer_is_on = 1;
}

void timer_off() {
	timer_is_on = 0;
}