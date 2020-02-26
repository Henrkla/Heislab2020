#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "lights.h"
#include "heislogikk.h"
#include "door.h"

void lights_floor_indicator() {
	int floor = state_current_last_floorindicator();
	hardware_command_floor_indicator_on(floor);

}

void lights_reset_floor(int floor) {
	hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
	hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
	hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
}

void lights_order_emergency_clear_all() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
		hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
		hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
	}
}