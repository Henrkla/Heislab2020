#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "heislogikk.h"
#include "lights.h"

#ifndef DOOR_H
#define DOOR_H

/*
* @brief Åpner dør og setter på dørlys.
*/
void door();

/*
* @brief Hvis stopknapp er trykket, åpne dør med mindre heisen er mellom etasjer.
*/
void stop_button_door();

#endif