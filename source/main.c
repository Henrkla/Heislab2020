#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "heislogikk.h"
#include "states.h"
#include "door.h"
#include "queue.h"
#include "lights.h"

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

	start_elevator();

	//

	while(1) {
		
		if (hardware_read_obstruction_signal()) {
			states_set_next_state(EMERGENCY);
		}
		queue_fetch_button_inputs();
		lights_floor_indicator();


		switch (states_get_next_state()) {
			case IDLE:
				state_idle();
				break;
			case RUN:
				state_run();
				break;
			case STAY:
				state_stay();
				break;
			case EMERGENCY:
				state_emergency();
				break;
		}
	}




    return 0;
}
