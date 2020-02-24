/** @file
* @brief Tilstandsmaskin
*/

/** Enum med alle tilstandene heisen kan v�re i.
* Initialiseringstilstanden skjer bare en gang, s� den er ikke tatt med her
*/

typedef enum state {
	IDLE,		 ///< Heisen venter p� ny bestilling.
	GO,			 ///< Heisen bestemmer retning og g�r til bestilling.
	STAY,		 ///< Heisen st�r i en etasje og h�ndterer en bestilling
	EMERGENCY,	 ///< Heisen g�r i n�dmodus
} StateType;

/** Enum med actions for tilstandene.
*
* INTERNAL-action kan sies � v�re "selve tilstanden". ENTRY og EXIT utf�res �n gang hver (for hver tilstand), henholdsvis p� vei inn i og ut av tilstanden.
* Tilstander kan ha ingen, �n eller flere.
*/

typedef enum state_actions {
	ENTRY,		 ///< ENTRY-action utf�res p� vei inn i en ny tilstand.
	INTERNAL,	 ///< INTERNAL-action utf�res gjentatte ganger s� lenge vi holder oss i en tilstand.
	EXIT,		 ///< EXIT-action utf�res p� vei ut av en tilstand.
} StateActionType;






/** @brief Henter etasjesignal fra heisdriveren og oppdaterer global currentFloor.
*/
void fsm_update_current_floor();

/** @brief N�ytraliserer lastDirectionBeforeStop-variablen (setter den til 0-ish).
*
* Variablen blir satt til DIRN_STOP, en verdi og en retning som ikke gir mening at en aktiv lastDirectionBeforeStop-variabel har.
*/
void fsm_unset_last_direction_before_stop();

/** @brief Sjekker og returnerer hvorvidt lastDirectionBeforeStop har f�tt en verdi annet enn initialiserings- og unset-verdien.
*
* @return Hvorvidt variablen har en aktiv verdi.
*/
elev_motor_direction_t fsm_last_direction_before_stop_is_set();

/** @brief Sender motoren i gitt retning, og oppdaterer retningsvariabler.
*
* @param[in] dirn Ny motorretning
*/
void fsm_set_elevator_direction(elev_motor_direction_t dirn);

/** @brief Henter den neste tilstanden tilstandsmaskinen skal inn i
*
* @return Neste tilstand
*/
state_t fsm_get_next_state();

/** @brief Oppdaterer tilstandsmaskinsvariablene som ang�r neste tilstand og neste action.
*
* @param[in] state Neste tilstand
* @param[in] action Neste action
*/
void fsm_transition(state_t state, state_action_t action);

/** @brief Kj�rer initialiseringstilstanden.
*
* Kj�rer heisen ned til n�rmeste etasje hvis heisen startes mellom to etasjer. Heisen blir st�ende hvis den startes i en etasje.
* G�r deretter til idle-tilstand.
*/
void fsm_state_initialize();

/** @brief Kj�rer idle-tilstand.
*
* Venter p� ny bestilling hvis k�en er tom.
* G�r til stay-tilstand hvis vi har en bestilling i samme etasje som heisen st�r i.
* G�r til go-state hvis vi har bestilling et annet sted.
*/
void fsm_state_idle();

/** @brief Kj�rer go-tilstand.
*
* Sender heisen i retning av neste bestilling. Stopper hvis vi havner i en etasje med en bestilling som skal h�ndteres.
*/
void fsm_state_go();

/** @brief Kj�rer stay-state
*
* H�ndterer en bestilling i en etasje.
*/
void fsm_state_stay();

/** @brief Kj�rer stop-state
*
* Fikser alt som skal fikses ved n�dstopp.
*/
void fsm_state_emergency();
