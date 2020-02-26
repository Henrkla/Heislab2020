
#include <stdlib.h>
#include "hardware.h"
#include "door.h"

#ifndef LIGHTS_H
#define LIGHTS_H

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

void lights_emergency_clear_all()

#endif