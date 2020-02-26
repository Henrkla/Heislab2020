


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
*/
void states_goto_floor(int targetFloor);

void states_set_next_state(States state);

States states_get_next_state();