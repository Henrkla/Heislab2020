#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "heislogikk.h"

void start_elevator() {
	lights_reset();
	while (current_floor() != 0) {
		hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
		lights_floor_indicator();
	}
	save_direction = direction;
	direction = HARDWARE_MOVEMENT_STOP;
	hardware_command_movement(direction);
};

int current_floor() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		if (hardware_read_floor_sensor(i)) {
			return i;
		}
	}
	return -1
}

void lights_floor_indicator() {
	int floor = current_floor();
	if (floor != -1) {
		hardware_command_floor_indicator_on(floor);
	}
};

/*
void lights_reset() {
Trenger queue for å kunne resete lysene
}


*/

void stop_button_check_delete() {
	if (hardware_read_stop_signal()) {
		lights_reset();
		direction = HARDWARE_MOVEMENT_STOP;
		hardware_command_movement(direction);
		while (hardware_read_stop_signal()) {
			hardware_command_stop_light(1);
			stop_button_door();
		}
		hardware_command_stop_light(0)
		stop_button_pressed = 1
	}

}

void timer() {
	time_t start_time = time(NULL);
	time_t current_time = time(NULL);
	double time_used = difftime(current_time, start_time);

	while (time_use)

};

void door() {
	hardware_command_door_open(1);
	timer();
	hardware_command_door_open(0);
};

void stop_button_door() {
	if (current_floor() != -1) {
		door();
	}
};

;