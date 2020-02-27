
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "states.h"
#include "queue.h"
#include "lights.h"
#include "door.h"


#define BEETWEEN_FLOORS -1

static int currentFloor = BEETWEEN_FLOORS;

static int currentDirection = HARDWARE_MOVEMENT_STOP;
static int previusDirection = HARDWARE_MOVEMENT_STOP;

static STATE nextState = IDLE;



void states_set_motor_dir(HardwareMovement movement) {
	currentDirection = movement;
	if (currentDirection != HARDWARE_MOVEMENT_STOP) {
		previusDirection = movement;
	}
	hardware_command_movement(movement);
}

void states_goto_floor(int targetFloor) {
	states_update_current_floor();
	while (currentFloor != targetFloor) {
		if ((targetFloor < currentFloor) && (currentFloor != 0)) {
			states_set_motor_dir(HARDWARE_MOVEMENT_DOWN);
		}
		else if ((targetFloor > currentFloor) && (currentFloor != HARDWARE_NUMBER_OF_FLOORS - 1)) {
			states_set_motor_dir(HARDWARE_MOVEMENT_UP);
		}
		states_update_current_floor();
	}
}


void states_set_next_state(STATE state) {
	nextState = state;
}


STATE states_get_next_state() {
	return nextState;
}


void state_idle() {
	states_update_current_floor();
	while (queue_get_next_dest(currentFloor, previusDirection) == -1) {
		if (queue_check_order_floor(currentFloor) != ORDER_NONE) {
			states_set_next_state(STAY);
			}
		}
	states_set_next_state(RUN);
}


void state_stay() {
	lights_reset_floor(currentFloor);
	queue_clear_floor(currentFloor);
	door_open();
	door_obstruction_check();
	if (queue_get_next_dest(currentFloor, previusDirection) == -1) {
		states_set_next_state(IDLE);
	}
	else {
		states_set_next_state(RUN);
	}
}


void state_run() {
	int dest = queue_get_next_dest(currentFloor, previusDirection);
	states_goto_floor(dest);
	states_set_next_state(STAY);
}


void state_emergency() {
	while (hardware_read_stop_signal()) {
		lights_order_emergency_clear_all();
		hardware_command_movement(HARDWARE_MOVEMENT_STOP);
		queue_clear_all_floors();
		hardware_command_stop_light(1);
		door_stop_button();
	}
	hardware_command_stop_light(0);
	states_set_next_state(IDLE);
}


void state_init() {
	lights_order_emergency_clear_all();
	queue_clear_all_floors();
	while (lights_floor_check() == -1) {
		states_set_motor_dir(HARDWARE_MOVEMENT_DOWN);
	}
	states_set_motor_dir(HARDWARE_MOVEMENT_STOP);
	states_set_next_state(IDLE);
};


void states_update_current_floor() {
	if (lights_floor_check() != -1) {
		currentFloor = lights_floor_check();
	}
}




