


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
*/
void states_goto_floor(int targetFloor);

void states_set_next_state(States state);

States states_get_next_state();