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


/** @brief Sjekker alle knappene og oppdaterer arrayet med aktive knapper
  */
void button_fetch_inputs();


/** @brief sjekker hvorvidt heisen skal stoppe i en etasje eller bare kjøre forbi
  * @param[in] floor
  * @param[in] direction
  *
  * @return Om vi skal stoppe eller ikke (t/f) = (1/0)
  */
int queue_should_stop(int floor, HardwareMovement direction);