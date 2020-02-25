#include "hardware.h"
#include "states.h"
#include "queue.h"


#define BEETWEEN_FLOORS -1

static int currentFloor = BEETWEEN_FLOORS;
static int nextFloor = BEETWEEN_FLOORS;

static int currentDirection = HARDWARE_MOVEMENT_STOP;
static int previusDirection = HARDWARE_MOVEMENT_STOP;


// floor check
// viktig at dette ikke er -1
void states_update_current_floor() {
	currentFloor = // floor check
}

void states_set_motor_dir(HardwareMovement movement) {
	currentDirection = movement;
	if (currentDirection != HARDWARE_MOVEMENT_STOP) {
		previusDirection = movement;
	}
	hardware_command_movement(movement);
}



int states_get_next_dest() {
	if (previusDirection == HARDWARE_MOVEMENT_UP) {
		return queue_check_orders_above;
		return queue_check_orders_below;
	}
	else if (previusDirection == HARDWARE_MOVEMENT_DOWN) {
		return queue_check_orders_below;
		return queue_check_orders_above;
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