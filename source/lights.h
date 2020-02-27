
#ifndef LIGHTS_H
#define LIGHTS_H

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "door.h"

/**
* @brief Setter etasje lys
*/

void lights_floor_indicator();

/**
* @brief Rester lysene på panelet
*/

void lights_reset_floor(int floor);

/**
* @brief Rester alle lysene ved emergency
*/

void lights_order_emergency_clear_all();

/**
* @brief Sjekker etasje, returnerer -1 mellom etasjer.
*/

int lights_floor_check();

/**
* @brief Returnerer siste etasje heisen har vært.
*/

int lights_update_current_floor();

#endif