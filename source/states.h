


typedef enum {
	IDLE,				/// Heisen står stille og venter på ny bestilling
	STAY,				/// Heisen står stille i en etajse og håndterer en bestilling
	Go,					/// Heisen beveger seg til en annen bestilling for å betjene denne
	EMERGENCY			/// Heisen er i et nødstillfelle og kaster alle bestillinger til siden
} States;


/** @brief Oppdaterer currentFloor variabelen til riktig etasje, -1 mellom etasjer
*/
void states_update_current_floor();



/** @brief Setter motorretning i hardware filen, endrer også currentDirection og previusDirection variablene
*/
void states_set_motor_dir(HardwareMovement movement);


/** @brief Sjekker Motorretning og nåværende etasje og sjekker hva som bør være neste stop
  * @return Neste etasje med bestillinger i bevegelsesretningen, returnerer -1 hvis det ikke er bestillinger
*/
int states_get_next_dest();


/** @brief Kjører heisen fra currentFloor til targetFloor
  * @param[in] targetfloor Etasjen heisen skal kjøre til
*/
void states_goto_floor(int targetFloor);


/** @brief Endrer nextState variabelen til state
  * @param[in] state Tilstanden hesen skal til neste gang states_get_next_state kalles
*/
void states_set_next_state(States state);


/** @brief Kalles for å endre nåhverdne state til til nextState
*/
States states_get_next_state();



/*
De følgene funskjonene er alle states som brukes i main.c

*/


/** @brief State for når heisen står stille og leter etter bestillinger
*/
void state_idle();


/** @brief State for når heisen betjener en bestilling
*/
void state_stay();


/** @brief State for når heisen kjører til en etasje
*/

void state_run();


/** @brief State for når stopknappen er trykket inn og det er en nødsituasjon
*/
void state_emergency();


/**
* @brief Setter heisen i første etasje når programmet begynner, samt skrur av alle etasje command lys.
*/

void state_init_elevator();
