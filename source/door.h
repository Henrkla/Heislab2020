
#include <stdlib.h>
#include "hardware.h"
#include "lights.h"

#define DOOR_DELAY = 3

#ifndef DOOR_H
#define DOOR_H

/*
* @brief �pner d�r og setter p� d�rlys.
*/
void door_open();

/*
* @brief Hvis stopknapp er trykket, �pne d�r med mindre heisen er mellom etasjer.
*/
void door_stop_button();

/**
* @brief Sjekker om obstruksjonsbryteren er p�. Holder d�ren �pen hvis den allerde er �pen. P�virker ikke systemet om d�ren er lukket.
*/

void door_obstruction_check();

/**
* @brief Tidsinterval for �pen d�r. St�r p� i 3 sekunder. resetter timeren ved n�r obstruksjon eller stoppknappen er trykket.
*/
void door_timer();

#endif