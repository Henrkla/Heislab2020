#include hardware.h

#define BETWEEN_FLOORS -1
#define NUMBER_OF_BUTTONS 3

static int orders[HARDWARE_NUMBER_OF_FLOORS];

int queue_check_multiple_orders(int floor) {
	if (hardware_read_order(floor, HARDWARE_ORDER_UP) && hardware_read_order(floor, HARDWARE_ORDER_DOWN)) {
		return 1;
	}
	else {
		return 0;
	}
}

void queue_fetch_button_inputs() {
	 for(int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++){
		 for (int button = HARDWARE_ORDER_UP; button <= HARDWARE_ORDER_DOWN; button++) {
			 if (hardware_read_order(floor, button) && queue_check_multiple_orders(floor)) {
				 orders[floor] = HARDWARE_ORDER_INSIDE;
			 }
			 else if (hardware_read_order(floor, button) && !(queue_check_multiple_orders(floor))){
				 orders[floor] = button;
			 }
			 else {
				 orders[floor] = ORDER_NONE;
			 }
		 }
       
	}

}

void queue_clear_floor(int floor) {
	orders[floor] = ORDER_NONE;
}


void queue_clear_all_floors() {
	for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
		queue_clear_floor(floor);
	}
}

int queue_same_direction(int floor, HardwareMovement direction) {
	if (order[floor] == HARDWARE_ORDER_INSIDE) {
		return 1;
	}	
	else if	((direction == HARDWARE_MOVEMENT_DOWN)  &&   (orders[floor] == HARDWARE_ORDER_DOWN)) {
		return 1;
	}
	else if ((direction == HARDWARE_MOVEMENT_UP) && (orders[floor] == HARDWARE_ORDER_UP) || (orders[floor])) {
		return 1;
	}
	else {
		return 0;
	}
}
