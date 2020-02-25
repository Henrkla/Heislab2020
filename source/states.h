
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