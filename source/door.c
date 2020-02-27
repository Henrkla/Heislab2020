#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door.h"

static DOOR_STATE currentDoorState = DOOR_CLOSED;

void door_open() {
	hardware_command_door_open(1);
	currentDoorState = DOOR_OPEN;
	door_timer();
	hardware_command_door_open(0);
	currentDoorState = DOOR_CLOSED;
};

void door_stop_button() {
	if (state_floor_check() != -1) {
		door_open();
	}
};


void door_obstruction_check() {
	while (hardware_read_obstruction_signal() && currentDoorState ==DOOR_OPEN) {
		door_open();
	}
}
;

void door_timer() {
	time_t start_time = time(NULL);
	time_t current_time = time(NULL);
	double time_used = difftime(current_time, start_time);

	while (time_used < DOOR_DELAY) {

		if (hardware_read_obstruction_signal() || hardware_read_stop_signal()) {
			start_time = time(NULL);

		}
		current_time = time(NULL);
		time_used = difftime(current_time, start_time);

		if (!hardware_read_stop_signal()) {
			hardware_command_stop_light(0);
		}
	}
};
