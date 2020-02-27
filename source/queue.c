

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "queue.h"


#define BETWEEN_FLOORS -1
#define NUMBER_OF_BUTTONS 3

static ORDER orders[HARDWARE_NUMBER_OF_FLOORS];

int queue_check_multiple_orders(int floor) {
	if (hardware_read_order(floor, HARDWARE_ORDER_UP) && hardware_read_order(floor, HARDWARE_ORDER_DOWN)) {
		return 1;
	}
	else {
		return 0;
	}
};

void queue_fetch_button_inputs() {
	for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		for (int button = ORDER_UP; button <= ORDER_DOWN; button++) {
			if (hardware_read_order(floor, button) && queue_check_multiple_orders(floor)) {
				orders[floor] = ORDER_INSIDE;
			}
			else if (hardware_read_order(floor, button) && !(queue_check_multiple_orders(floor))) {
				orders[floor] = button;
			}
			else {
				orders[floor] = ORDER_NONE;
			}
		}
	}
};

void queue_clear_floor(int floor) {
	orders[floor] = ORDER_NONE;
};

void queue_clear_all_floors() {
	for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		queue_clear_floor(floor);
	}
};

/*
* gcc er ikke spesielt happy n�r vi sammenligner to enums "(orders[floor] == HARDWARE_ORDER_DOWN)", og flagger dette som en feil. Mulig vi m� finne en bedre m�te � gj�re dette p�, men er mulig � fjerne flagget som sier det er feil.
*/

int queue_same_direction(int floor, HardwareMovement direction) {
	if (orders[floor] == ORDER_INSIDE) {
		return 1;
	}
	else if ((direction == HARDWARE_MOVEMENT_DOWN) && (orders[floor] == ORDER_DOWN)) {
		return 1;
	}
	else if (((direction == HARDWARE_MOVEMENT_UP) && (orders[floor] == ORDER_UP)) || (orders[floor])) {
		return 1;
	}
	else {
		return 0;
	}
};

ORDER queue_check_order_floor(int floor) {
	return orders[floor];
};

/*
* La til return 0; p� alle int funksjoner under. (unntatt den som returnerer -1)
*/


int queue_check_orders_above(int currentFloor) {
	for (int floor = currentFloor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		if (queue_check_order_floor(floor) != ORDER_NONE) {
			return floor;
		}
	}
	return 0;
};

int queue_check_orders_below(int currentFloor) {
	for (int floor = currentFloor; floor >= 0; floor--) {
		if (queue_check_order_floor(floor) != ORDER_NONE) {
			return floor;
		}
	}
	return 0;
};


int queue_check_orders_above_motor(int currentFloor, HardwareMovement direction) {
	for (int floor = currentFloor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		if ((queue_check_order_floor(floor) != ORDER_NONE) && (queue_same_direction(floor, direction))) {
			return floor;
		}
	}
	return 0;
}


int queue_check_orders_below_motor(int currentFloor, HardwareMovement direction) {
	for (int floor = currentFloor; floor >= 0; floor--) {
		if ((queue_check_order_floor(floor) != ORDER_NONE) && (queue_same_direction(floor, direction))) {
			return floor;
		}
	}
	return 0;
};


int queue_get_next_dest(int currentFloor, HardwareMovement prevDirection) {
	if (prevDirection == HARDWARE_MOVEMENT_UP) {
		return queue_check_orders_above_motor(currentFloor, HARDWARE_MOVEMENT_UP);
		return queue_check_orders_above(currentFloor);
		return queue_check_orders_below(currentFloor);
	}
	else if (prevDirection == HARDWARE_MOVEMENT_DOWN) {
		return queue_check_orders_below_motor(currentFloor, HARDWARE_MOVEMENT_DOWN);
		return queue_check_orders_below(currentFloor);
		return queue_check_orders_above(currentFloor);
	}
	return -1;
};
