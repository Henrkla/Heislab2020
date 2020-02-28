

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

/**@file
  *@brief Tar input signalene til knappene og legger dem inn i et array
  */

typedef enum ORDERS {
	ORDER_NONE,						  // Ingen Bestilling
	ORDER_UP,			          // Bestilling oppover
	ORDER_DOWN,	            // Bestilling Nedover
	ORDER_INSIDE,	          // Bestilling B�de opp og ned eller Bestilling fra inne i heisen
  ORDER_UP_AND_DOWN,
} ORDER;


/** @brief Sjekker om det er tryket inn b�de opp og ned knapp i en etasje
*/
int queue_check_multiple_orders(int floor);

/** @brief Sjekker alle knappene og oppdaterer arrayet med aktive knapper. Tar ogs� h�yde for om to knapper er trykket inn om gangen
  */
void queue_fetch_button_inputs();

/** @brief fjerner alle bestillinger i en etasje
*/
void queue_clear_floor(int floor);

/** @brief fjerner alle bestillinger fra alle etasjene
*/
void queue_clear_all_floors();

/** @brief sjekker hvorvidt heisen kj�rer i samme retning som en bestilling
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


/** @brief Finner n�rmeste bestilling over heisen, uavhengig av motorretning
  * 
  * @param[in] currentFloor Etasjen vi er i
  *
  * @return Returner den n�rmeste bestillingen over heisen.
*/
int queue_check_orders_above(int currentFloor);


/** @brief Finner n�rmeste bestilling under heisen, uavhengig av motorretning
  *
  * @param[in] currentFloor Etasjen vi er i
  *
  * @return Returner den n�rmeste bestillingen under heisen.
*/
int queue_check_orders_below(int currentFloor);


/** @brief Finner n�rmeste bestilling over heisen, sjekker ogs� at bestillingene skal i samme retning som heisen
  *
  * @param[in] currentFloor Etasjen vi er i
  * @param[in] direction Retningen heisen har
  *
  * @return Returner den n�rmeste bestillingen over heisen som ogs� skal i samme retning.
*/
int queue_check_orders_above_motor(int currentFloor, HardwareMovement direction);


/** @brief Finner n�rmeste bestilling under heisen, sjekker ogs� at bestillingene skal i samme retning som heisen
  *
  * @param[in] currentFloor Etasjen vi er i
  * @param[in] direction Retningen heisen har
  *
  * @return Returner den n�rmeste bestillingen under heisen som ogs� skal i samme retning.
*/
int queue_check_orders_below_motor(int currentFloor, HardwareMovement direction);



/** @brief Finner ut hvilken bestilling som skal betjenes som neste
  * 
  * @param[in] currentFloor her taes inn den n�hverende etasjen
  * @param[in] prevDirection her taes inn den forrige retningen
  * 
  * @return hvilken etasje er neste heisen skal dra til
*/
int queue_get_next_dest(int currentFloor, HardwareMovement prevDirection);




/**
 * @brief Leser bestiilingene og bestillingslysene når det er en bestilling
 * 
 * @param floor Etasjen der knappen trykkes på
 * @param order hvilken knapp som trykkes
 */
void queue_order_lights(int floor, ORDER order);


#endif

