#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "heislogikk.h"
#include "lights.h"

#ifndef DOOR_H
#define DOOR_H

/*
* @brief �pner d�r og setter p� d�rlys.
*/
void door();

/*
* @brief Hvis stopknapp er trykket, �pne d�r med mindre heisen er mellom etasjer.
*/
void stop_button_door();

#endif