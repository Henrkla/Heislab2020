/**
* @file
* @brief Heislogikk
*
*
* #ifndef og #define er include guards. Hindrer dobbel deklarasjon av variabler, enums etc. (slett dette f�r innlevering)
*/

#ifndef HEISLOGIKK_H
#define HEISLOGIKK_H


#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "lights.h"
#include "door.h"



/**
 * @brief Sjekker hvilken etasje heisen er i.
 * @return Returnerer etasje-integer. Returnerer -1 hvis mellom etasjer.
 */
int floor_check();

/*
* @brief sjekker siste etasje heisen har v�rt i. Brukes for � gi riktig etasjelys.
*/

int current_last_floorindicator();

/**
 * @param Returnerer 1 hvis stoppknappen er trykket.
 */

/*int stop_button_pressed();
*/

/**
 * @brief Sjekker om stoppknappen er trykket og sletter alle ordre hvis trykket.
 */
void stop_button_check_delete();

/**
* @brief Sjekker om obstruksjonsbryteren er p�. Holder d�ren �pen hvis den allerde er �pen. P�virker ikke systemet om d�ren er lukket.
*/

void obstruction_check();


/**
 * @brief Tidsinterval for �pen d�r. St�r p� i 3 sekunder. resetter timeren ved n�r obstruksjon eller stoppknappen er trykket.
 */
void timer();

#endif