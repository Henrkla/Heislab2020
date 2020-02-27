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
  * init vil også være en tilstand, men denne tilstanden vil bare være en tilstand helt i begynnelsen av programmet
  */


typedef enum STATES {
	IDLE,				/// Heisen står stille og venter på ny bestilling
	STAY,				/// Heisen står stille i en etajse og håndterer en bestilling
	RUN,				/// Heisen beveger seg til en annen bestilling for å betjene denne
	EMERGENCY,			/// Heisen er i et nødstillfelle og kaster alle bestillinger til siden
} STATE;

/** @brief Setter motorretning i hardware filen, endrer også currentDirection og previusDirection variablene
*/
void states_set_motor_dir(HardwareMovement movement);


/** @brief Kjører heisen fra currentFloor til targetFloor
  * @param[in] targetfloor Etasjen heisen skal kjøre til
*/
void states_goto_floor(int targetFloor);


/** @brief Endrer nextState variabelen til state
  * @param[in] state Tilstanden heisen skal til neste gang states_get_next_state kalles
*/
void states_set_next_state(STATE state);


/** @brief Kalles for å endre tilstand til nextState
*/
STATE states_get_next_state();


/** @brief State for når heisen står stille og leter etter bestillinger
  *
  */
void state_idle();


/** @brief State for når heisen betjener en bestilling
  *
  */
void state_stay();


/** @brief State for når heisen kjører til en etasje
*/

void state_run();


/** @brief State for når stopknappen er trykket inn og det er en nødsituasjon
*/
void state_emergency();


/**
* @brief State for når programmet akkuratt startet. Kjører ned en etasje og skifter til IDLE.
*/
void state_init();

/** @brief sjekker siste etasje heisen har vært i. Brukes for å gi riktig etasjelys.
  * 
  * @return Returner etasje-integer. Returnerer siste etasje hvis mellom etasjer.
  */
void states_update_current_floor();

#endif

