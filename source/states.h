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

<<<<<<< HEAD
typedef enum {
=======

typedef enum STATES {
>>>>>>> ec46f559fde9a91cf86122d82a06a8b5b106a49a
	IDLE,				/// Heisen st�r stille og venter p� ny bestilling
	STAY,				/// Heisen st�r stille i en etajse og h�ndterer en bestilling
	Go,					/// Heisen beveger seg til en annen bestilling for � betjene denne
	EMERGENCY,		/// Heisen er i et n�dstillfelle og kaster alle bestillinger til siden
};

/** @brief Setter motorretning i hardware filen, endrer ogs� currentDirection og previusDirection variablene
*/
void states_set_motor_dir(HardwareMovement movement);


/** @brief Sjekker Motorretning og n�v�rende etasje og sjekker hva som b�r v�re neste stop
  * @return Neste etasje med bestillinger i bevegelsesretningen, returnerer -1 hvis det ikke er bestillinger
*/
int states_get_next_dest();


/** @brief Kj�rer heisen fra currentFloor til targetFloor
  * @param[in] targetfloor Etasjen heisen skal kj�re til
*/
void states_goto_floor(int targetFloor);


/** @brief Endrer nextState variabelen til state
  * @param[in] state Tilstanden heisen skal til neste gang states_get_next_state kalles
*/
void states_set_next_state(STATES state);


/** @brief Kalles for � endre tilstand til nextState
*/
STATES states_get_next_state();


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

/** @brief Sjekker hvilken etasje heisen er i.
  * 
  * @return Returnerer etasje-integer. Returnerer -1 hvis mellom etasjer.
  */
int state_floor_check();

/** @brief sjekker siste etasje heisen har v�rt i. Brukes for � gi riktig etasjelys.
  * 
  * @return Returner etasje-integer. Returnerer siste etasje hvis mellom etasjer.
  */
int states_update_current_floor();

#endif

