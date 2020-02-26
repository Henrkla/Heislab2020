#include "hardware.h"
#include "states.h"

#include "queue.h"
#include "lights.h"
#include "door.h"


#define BEETWEEN_FLOORS -1

static int currentFloor = BEETWEEN_FLOORS;

static int currentDirection = HARDWARE_MOVEMENT_STOP;
static int previusDirection = HARDWARE_MOVEMENT_STOP;

static States nextState = IDLE;



// floor check
// viktig at dette ikke er -1
void states_update_current_floor() {
	currentFloor = state_current_last_floorindicator();
}

void states_set_motor_dir(HardwareMovement movement) {
	currentDirection = movement;
	if (currentDirection != HARDWARE_MOVEMENT_STOP) {
		previusDirection = movement;
	}
	hardware_command_movement(movement);
}


int states_get_next_dest() {
	states_update_current_floor();
	if (previusDirection == HARDWARE_MOVEMENT_UP) {
		return queue_check_orders_above_motor(currentFloor, HARDWARE_MOVEMENT_UP);
		return queue_check_orders_above(currentFloor);
		return queue_check_orders_below(currentFloor);
	}
	else if (previusDirection == HARDWARE_MOVEMENT_DOWN) {
		return queue_check_orders_below_motor(currentFloor, HARDWARE_MOVEMENT_DOWN);
		return queue_check_orders_below(currentFloor);
		return queue_check_orders_above(currentFloor);
	}
	return -1;
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


void states_set_next_state(States state) {
	nextState = state;
}


States states_get_next_state() {
	return nextState;
}


void state_idle() {
	while (states_get_next_dest() == -1) {
		if (queue_check_order_floor(currentFloor) != ORDER_NONE) {
			states_set_next_state(STAY);
			}
		}
	states_set_next_state(RUN);
}


void state_stay() {
	lights_reset_floor(currentFloor)
	queue_clear_floor(currentFloor);
	door_open();
	door_obstruction_check();
	if (states_get_next_dest() == -1) {
		states_set_next_state(IDLE);
	}
	else {
		states_set_next_state(RUN);
	}
}


void state_run() {
	int dest = states_get_next_dest();
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


void state_init_elevator() {
	lights_order_emergency_clear_all();
	while (state_floor_check() = -1) {
		hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
		lights_floor_indicator();
	}
	save_direction = direction;
	direction = HARDWARE_MOVEMENT_STOP;
	hardware_command_movement(direction);
};

int state_floor_check() {
	for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
		if (hardware_read_floor_sensor(i)) {
			return i;
		}
	}
	return -1;
};

int state_current_last_floorindicator() {
	int currentlastfloor = f;
		if state_floor_check() != -1 {
			currentlastfloor = state_floor_check();
		else
			return f;
		}
	return f;
}











/*
void states_init() {
	int error = hardware_init();
	if (error != 0) {
		fprintf(stderr, "Unable to initialize hardware\n");
		exit(1);
	}
	queue_clear_all_floors();
	//lights_clear_all();
	states_update_current_floor();
	if (currentFloor == BEETWEEN_FLOORS) {
		nextFloor = 1;
	}

}
*/