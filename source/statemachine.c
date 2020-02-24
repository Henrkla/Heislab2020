#include <stdlib.h>
#include <stdio.h>

#include "statemachine.h"

#define BETWEEN_FLOORS -1

static StatesType nextState = IDLE;
static state_action_t nextAction = ENTRY;

static int currentFloor = BETWEEN_FLOORS;
static int lastFloor = BETWEEN_FLOORS;
static elev_motor_direction_t currentDirection = DIRN_STOP;
static elev_motor_direction_t lastDirection = DIRN_STOP;
static elev_motor_direction_t lastDirectionBeforeStop = DIRN_STOP;