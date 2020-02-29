
#ifndef DOOR_H
#define DOOR_H

#include <stdlib.h>
#include <stdio.h>
#include "hardware.h"
#include "lights.h"
#include "states.h"
#include <time.h>

#define DOOR_DELAY 2


/**@brief Enum that keeps track on the door is open or not
  *
  *
  */
typedef enum {
	DOOR_OPEN,			// Door is open
	DOOR_CLOSED			// Door is closed
} DOOR_STATE;



/*
* @brief Skrur på døren og endrer currentDoorState til DOOR_OPEN
*/
void door_open();




/** 
  * @breif Skrur av dørlys og endre currentDoorState til DOOR_CLOSED.
  *
  */
void door_close();

/**
  * @brief Sjekker om obstruksjonsbryteren er p� og om døren allerede er åpen. 
  * 
  * @return Hvorvidt døren er åpen og obstruksjonsiganelet er høyt.(True/False)
  */

int door_obstruction_check();


/**
  * @breif Forteller om hvorvidt tiden er utgått
  *
  * @return Returnerer hvorvidt tiden er utløpt (True/False)
  *
  */
int timer_expired();

/**
  * @breif Resetter timeren
  */
void timer_reset();

/**
  * @breif Setter timer_is_on variabelen høy
  *
  */
void timer_on();


/**
  * @breif Setter timer_is_on variabelen lav
  *
  */
void timer_off();
#endif
