
#include <stdlib.h>
#include "hardware.h"
#include "lights.h"

#define DOOR_DELAY = 3

#ifndef DOOR_H
#define DOOR_H

/*
* @brief Åpner dør og setter på dørlys.
*/
void door_open();

/*
* @brief Hvis stopknapp er trykket, åpne dør med mindre heisen er mellom etasjer.
*/
void door_stop_button();

/**
* @brief Sjekker om obstruksjonsbryteren er på. Holder døren åpen hvis den allerde er åpen. Påvirker ikke systemet om døren er lukket.
*/

void door_obstruction_check();

/**
* @brief Tidsinterval for åpen dør. Står på i 3 sekunder. resetter timeren ved når obstruksjon eller stoppknappen er trykket.
*/
void door_timer();

#endif