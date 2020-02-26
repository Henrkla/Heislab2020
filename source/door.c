#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "heislogikk.h"
#include "door.h"

void door_open() {
	hardware_command_door_open(1);
	timer();
	hardware_command_door_open(0);
};

void door_stop_button() {
	if (current_floor() != -1) {
		door_open();
	}
};
