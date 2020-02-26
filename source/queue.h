/**@file
  *@brief Tar input signalene til knappene og legger dem inn i et array
  */

/**/
typedef enum {
	ORDER_NONE = -1,						//Ingen Bestilling
	ORDER_UP = HARDWARE_ORDER_UP,			//Bestilling oppover
	ORDER_DOWN = HARDWARE_ORDER_DOWN,		//Bestilling Nedover
	ORDER_INSIDE = HARDWARE_ORDER_INSIDE	//Bestilling Både opp og ned eller Bestilling fra inne i heisen
} ORDERS;


/** @brief Sjekker om det er tryket inn både opp og ned knapp i en etasje
*/
int queue_check_multiple_orders(int floor);

/** @brief Sjekker alle knappene og oppdaterer arrayet med aktive knapper. Tar også høyde for om to knapper er trykket inn om gangen
  */
void queue_fetch_button_inputs();

/** @brief fjerner alle bestillinger i en etasje
*/
void queue_clear_floor(int floor);

/** @brief fjerner alle bestillinger fra alle etasjene
*/
void queue_clear_all_floors();

/** @brief sjekker hvorvidt heisen kjører i samme retning som en bestilling
  * @param[in] floor
  * @param[in] direction
  *
  * @return Om vi skal stoppe eller ikke (t/f) = (1/0)
  */
int queue_same_direction(int floor, HardwareMovement direction);


/** @brief finner hvilken bestilling som ligger i en spesefikk etasje
  * @param[in] floor etasjen som skal sjekkes
  * @return bestillingen som ligger i etasjen
*/
ORDERS queue_check_order_floor(int floor);