
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
static int previusDirection = HARDWARE_MOVEMENT_DOWN;

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
	if (hardware_floor_check() != targetFloor) {
		if ( (currentFloor == HARDWARE_NUMBER_OF_FLOORS - 1) && (currentFloor == 0) ){
			states_set_motor_dir(HARDWARE_MOVEMENT_STOP);
		}
		else if (targetFloor < currentFloor) {
			states_set_motor_dir(HARDWARE_MOVEMENT_DOWN);
		}
		else if (targetFloor > currentFloor) {
			states_set_motor_dir(HARDWARE_MOVEMENT_UP);
		}
		

	}
	else {
		states_set_next_state(STAY);
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
	if (queue_check_order_floor(currentFloor) != ORDER_NONE) {
	states_set_next_state(STAY);
	}
	else if (queue_get_next_dest(currentFloor, previusDirection) != -1) {
	states_set_next_state(RUN);
	}
}


void state_stay() {
	hardware_command_movement(HARDWARE_MOVEMENT_STOP);
	lights_reset_floor(currentFloor);
	queue_clear_floor(currentFloor);
	door_open();
	timer_on();

	if (door_obstruction_check()) {
		timer_reset();
	}

	if (timer_expired()) {
		door_close();
		timer_off();
		states_set_next_state(IDLE);
	}
}


void state_run() {
	states_update_current_floor();
	int dest = queue_get_next_dest(currentFloor, previusDirection);
	states_goto_floor(dest);
}


void state_emergency() {
	states_set_motor_dir(HARDWARE_MOVEMENT_STOP);
	while (hardware_read_stop_signal()) {
		hardware_command_stop_light(1);
		lights_order_emergency_clear_all();
		queue_clear_all_floors();
		hardware_command_stop_light(1);
		if (hardware_floor_check() != -1) {
			door_open();
		}
	}
	hardware_command_stop_light(0);

	if (hardware_floor_check() == -1) {
		states_set_next_state(IDLE);
	}
	else {
		states_set_next_state(STAY);
	}
}


void state_init() {
	lights_order_emergency_clear_all();
	queue_clear_all_floors();
	while (hardware_floor_check() == BEETWEEN_FLOORS) {
		states_set_motor_dir(HARDWARE_MOVEMENT_DOWN);
	}
	states_set_motor_dir(HARDWARE_MOVEMENT_STOP);
	states_set_next_state(IDLE);
	states_update_current_floor();
};


void states_update_current_floor() {
	if (hardware_floor_check() != BEETWEEN_FLOORS) {
		currentFloor = hardware_floor_check();
	}
}




