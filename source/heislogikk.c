#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "heislogikk.h"
#include "lights.h"
#include "door.h"

void start_elevator() {
	lights_order_emergency_clear_all();
	while (current_floor() != 0) {
		hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
		lights_floor_indicator();
	}
	save_direction = direction;
	direction = HARDWARE_MOVEMENT_STOP;
	hardware_command_movement(direction);
};

int floor_check() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		if (hardware_read_floor_sensor(i)) {
			return i;
		}
	}
	return -1;
};

int current_last_floorindicator() {
	int currentlastfloor = f
		if floor_check() != -1 {
			currentlastfloor = floor_check();
		else
			return f;
	}
	return f;
}

void stop_button_check_delete() {
	while (hardware_read_stop_signal()) {
		lights_order_emergency_clear_all();
		direction = HARDWARE_MOVEMENT_STOP;
		hardware_command_movement(direction);
		queue_clear_all_floors();
		hardware_command_stop_light(1);
		door_stop_button();
	}
	hardware_command_stop_light(0);
};

void timer() {
	time_t start_time = time(NULL);
	time_t current_time = time(NULL);
	double time_used = difftime(current_time, start_time);

	while (time_used) < (3.0) {

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