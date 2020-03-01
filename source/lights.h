
#ifndef LIGHTS_H
#define LIGHTS_H

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

/**
* @brief Setter etasje lys
*/

void lights_floor_indicator();

/**
* @brief Rester lysene p� panelet
*/

void lights_reset_floor(int floor);

/**
* @brief Rester alle lysene ved emergency
*/

void lights_order_emergency_clear_all();



#endif