

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "queue.h"


#define BETWEEN_FLOORS -1
#define UNVALID_ORDER -1
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
		if (((orders[floor] == ORDER_DOWN) && (hardware_read_order(floor, HARDWARE_ORDER_UP))) || 
		( (orders[floor] == ORDER_UP) && (hardware_read_order(floor, HARDWARE_ORDER_DOWN)) )) {
			orders[floor] = ORDER_UP_AND_DOWN;
		}
		else if (hardware_read_order(floor, HARDWARE_ORDER_UP)) {
			orders[floor] = ORDER_UP;
		}
		else if (hardware_read_order(floor, HARDWARE_ORDER_DOWN)){
			orders[floor] = ORDER_DOWN;
		}
		else if (hardware_read_order(floor, HARDWARE_ORDER_INSIDE)){
			orders[floor] = ORDER_INSIDE;
		}
		queue_order_lights(floor, orders[floor]);
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

int queue_same_direction(int floor, HardwareMovement direction) {
	if ((orders[floor] == ORDER_INSIDE)	||	(orders[floor] == ORDER_UP_AND_DOWN)) {
		return 1;
	}
	else if ((direction == HARDWARE_MOVEMENT_DOWN) && (orders[floor] == ORDER_DOWN)) {
		return 1;
	}
	else if (((direction == HARDWARE_MOVEMENT_UP) && (orders[floor] == ORDER_UP))) {
		return 1;
	}
	else {
		return 0;
	}
};

ORDER queue_check_order_floor(int floor) {
	return orders[floor];
};

int queue_check_orders_above(int currentFloor) {
	for (int floor = currentFloor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		if (queue_check_order_floor(floor) != ORDER_NONE) {
			return floor;
		}
	}
	return UNVALID_ORDER;
};

int queue_check_orders_below(int currentFloor) {
	for (int floor = currentFloor; floor >= 0; floor--) {
		if (queue_check_order_floor(floor) != ORDER_NONE) {
			return floor;
		}
	}
	return UNVALID_ORDER;
};

int queue_check_orders_above_motor(int currentFloor, HardwareMovement direction) {
	for (int floor = currentFloor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		if ((queue_check_order_floor(floor) != ORDER_NONE) && (queue_same_direction(floor, direction))) {
			return floor;
		}
	}
	return UNVALID_ORDER;
}

int queue_check_orders_below_motor(int currentFloor, HardwareMovement direction) {
	for (int floor = currentFloor; floor >= 0; floor--) {
		if ((queue_check_order_floor(floor) != ORDER_NONE) && (queue_same_direction(floor, direction))) {
			return floor;
		}
	}
	return UNVALID_ORDER;
};

int queue_get_next_dest(int currentFloor, HardwareMovement prevDirection) {
	if (prevDirection == HARDWARE_MOVEMENT_UP) {
		if (queue_check_orders_above_motor(currentFloor, HARDWARE_MOVEMENT_UP) != UNVALID_ORDER){
			return queue_check_orders_above_motor(currentFloor, HARDWARE_MOVEMENT_UP);
		}
		if (queue_check_orders_above(currentFloor) != UNVALID_ORDER){
			return queue_check_orders_above(currentFloor);
		}
		if (queue_check_orders_below(currentFloor) != UNVALID_ORDER){
			return queue_check_orders_below(currentFloor);
		}
	}
	else if (prevDirection == HARDWARE_MOVEMENT_DOWN) {
		if (queue_check_orders_below_motor(currentFloor, HARDWARE_MOVEMENT_DOWN) != UNVALID_ORDER){
				return queue_check_orders_below_motor(currentFloor, HARDWARE_MOVEMENT_DOWN);
		}
		if (queue_check_orders_below(currentFloor) != UNVALID_ORDER){
			return queue_check_orders_below(currentFloor);
		}
		if (queue_check_orders_above(currentFloor) != UNVALID_ORDER){
			return queue_check_orders_above(currentFloor);
		}
	}
	return UNVALID_ORDER;
};

void queue_order_lights(int floor, ORDER order) {
	if (order == ORDER_UP){
		hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
	}
	else if (order == ORDER_UP_AND_DOWN){
		hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
		hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
	}
	else if (order == ORDER_DOWN){
			hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
	}
	else if (order == ORDER_INSIDE){
			hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
	}
}
