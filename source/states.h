/** @file
  * @brief Tilstandene med hjelpefunksjoner
  */



#ifndef STATES_H
#define STATES_H

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "lights.h"
#include "door.h"
#include "queue.h"



/** Enum mulige tilstander
  *
  * Dette er de mulige tilstandene for switchen i main.c filen
  * init vil ogs� v�re en tilstand, men denne tilstanden vil bare v�re en tilstand helt i begynnelsen av programmet
  */


typedef enum STATES {
	IDLE,				/// Heisen st�r stille og venter p� ny bestilling
	STAY,				/// Heisen st�r stille i en etajse og h�ndterer en bestilling
	RUN,				/// Heisen beveger seg til en annen bestilling for � betjene denne
	EMERGENCY,			/// Heisen er i et n�dstillfelle og kaster alle bestillinger til siden
} STATE;

/** @brief Setter motorretning i hardware filen, endrer ogs� currentDirection og previusDirection variablene
*/
void states_set_motor_dir(HardwareMovement movement);


/** @brief Kj�rer heisen fra currentFloor til targetFloor
  * @param[in] targetfloor Etasjen heisen skal kj�re til
*/
void states_goto_floor(int targetFloor);


/** @brief Endrer nextState variabelen til state
  * @param[in] state Tilstanden heisen skal til neste gang states_get_next_state kalles
*/
void states_set_next_state(STATE state);


/** @brief Kalles for � endre tilstand til nextState
*/
STATE states_get_next_state();


/** @brief State for n�r heisen st�r stille og leter etter bestillinger
  *
  */
void state_idle();


/** @brief State for n�r heisen betjener en bestilling
  *
  */
void state_stay();


/** @brief State for n�r heisen kj�rer til en etasje
*/

void state_run();


/** @brief State for n�r stopknappen er trykket inn og det er en n�dsituasjon
*/
void state_emergency();

/**
* @brief State for n�r programmet akkuratt startet. Kj�rer ned en etasje og skifter til IDLE.
*/
void state_init();

/** @brief sjekker siste etasje heisen har v�rt i. Brukes for � gi riktig etasjelys.
  * 
  * @return Returner etasje-integer. Returnerer siste etasje hvis mellom etasjer.
  */
void states_update_current_floor();



#endif

