#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "lights.h"
#include "door.h"

void lights_floor_indicator() {
	int floor = lights_update_current_floor();
	hardware_command_floor_indicator_on(floor);
}

void lights_reset_floor(int floor) {
	hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
	hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
	hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
}

void lights_order_emergency_clear_all() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		lights_reset_floor(i);
	}
}

int lights_floor_check() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		if (hardware_read_floor_sensor(i)) {
			return i;
		}
	}
	return -1;
}

int lights_update_current_floor() {
	return 0;
}
	;
