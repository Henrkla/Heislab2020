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


/**
* @brief Setter heisen i f�rste etasje n�r programmet begynner.
*/

void start_elevator();

/**
 * @brief Sjekker hvilken etasje heisen er i.
 * @return Returnerer etasje-integer. Returnerer -1 hvis mellom etasjer.
 */
int current_floor();

/**
* @brief Setter etasje lys
*/

void lights_floor_indicator();

/**
 * @brief Rester lysene p� panelet
 */
void lights_reset();

/**
 * @param Returnerer 1 hvis stoppknappen er trykket.
 */
int stop_button_pressed;

/**
 * @brief Sjekker om stoppknappen er trykket og sletter alle ordre hvis trykket.
 */
void stop_button_check_delete();

/**
 * @brief Tidsinterval for �pen d�r osv.
 */
void timer();

/*
* @brief �pner d�r og setter p� d�rlys.
*/
void door();

/*
* @brief Hvis stopknapp er trykket, �pne d�r med mindre heisen er mellom etasjer.
*/
void stop_button_door();


#endif