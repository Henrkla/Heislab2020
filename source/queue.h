

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

/**@file
  *@brief Tar input signalene til knappene og legger dem inn i et array
  */

/**/
typedef enum ORDERS{
	ORDER_NONE = -1,						// Ingen Bestilling
	ORDER_UP = HARDWARE_ORDER_UP,			// Bestilling oppover
	ORDER_DOWN = HARDWARE_ORDER_DOWN,		// Bestilling Nedover
	ORDER_INSIDE = HARDWARE_ORDER_INSIDE	// Bestilling Både opp og ned eller Bestilling fra inne i heisen
} ORDER;


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
ORDER queue_check_order_floor(int floor);


/** @brief Finner nærmeste bestilling over heisen, uavhengig av motorretning
  * 
  * @param[in] currentFloor Etasjen vi er i
  *
  * @return Returner den nærmeste bestillingen over heisen.
*/
int queue_check_orders_above(int currentFloor);


/** @brief Finner nærmeste bestilling under heisen, uavhengig av motorretning
  *
  * @param[in] currentFloor Etasjen vi er i
  *
  * @return Returner den nærmeste bestillingen under heisen.
*/
int queue_check_orders_below(int currentFloor);


/** @brief Finner nærmeste bestilling over heisen, sjekker også at bestillingene skal i samme retning som heisen
  *
  * @param[in] currentFloor Etasjen vi er i
  * @param[in] direction Retningen heisen har
  *
  * @return Returner den nærmeste bestillingen over heisen som også skal i samme retning.
*/
int queue_check_orders_above_motor(int currentFloor, HardwareMovement direction);


/** @brief Finner nærmeste bestilling under heisen, sjekker også at bestillingene skal i samme retning som heisen
  *
  * @param[in] currentFloor Etasjen vi er i
  * @param[in] direction Retningen heisen har
  *
  * @return Returner den nærmeste bestillingen under heisen som også skal i samme retning.
*/
int queue_check_orders_below_motot(int currentFloor, HardwareMovement direction);



/** @brief Finner ut hvilken bestilling som skal betjenes som neste
  * 
  * @param[in] currentFloor her taes inn den nåhverende etasjen
  * @param[in] prevDirection her taes inn den forrige retningen
  * 
  * @return hvilken etasje er neste heisen skal dra til
*/
int queue_get_next_dest(int currentFloor, HardwareMovement prevDirection);


#endif

