


typedef enum {
	IDLE,				/// Heisen st�r stille og venter p� ny bestilling
	STAY,				/// Heisen st�r stille i en etajse og h�ndterer en bestilling
	Go,					/// Heisen beveger seg til en annen bestilling for � betjene denne
	EMERGENCY			/// Heisen er i et n�dstillfelle og kaster alle bestillinger til siden
} States;


/** @brief Oppdaterer currentFloor variabelen til riktig etasje, -1 mellom etasjer
*/
void states_update_current_floor();



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
  * @param[in] state Tilstanden hesen skal til neste gang states_get_next_state kalles
*/
void states_set_next_state(States state);


/** @brief Kalles for � endre n�hverdne state til til nextState
*/
States states_get_next_state();



/*
De f�lgene funskjonene er alle states som brukes i main.c

*/


/** @brief State for n�r heisen st�r stille og leter etter bestillinger
*/
void state_idle();


/** @brief State for n�r heisen betjener en bestilling
*/
void state_stay();


/** @brief State for n�r heisen kj�rer til en etasje
*/

void state_run();


/** @brief State for n�r stopknappen er trykket inn og det er en n�dsituasjon
*/
void state_emergency();


/**
* @brief Setter heisen i f�rste etasje n�r programmet begynner, samt skrur av alle etasje command lys.
*/

void state_init_elevator();
