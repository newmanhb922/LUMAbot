#ifndef FSM_H
#define FSM_H

#include <wiringPi.h>
#include <stdbool.h>
#include <stdio.h>
#include "MotorControl.h"
#include "Controller.h"
#include "Ultrasonic.h"
#include "Position.h"
#include "I2CModule.h"

#define NUM_STATES          7

typedef enum
{
    AUTOMATED_MOVE_STATE, CONTROLLER_MOVE_STATE,  STOP_STATE, WAITING_STATE, E_STOP_STATE, 
    OBSTACLE_AVOIDANCE_STATE, START_STATE
} FSM_STATE_T;

bool eStopPressed;
short controllerXValue;
short controllerYValue;
bool hasBeenZeroed;
bool goPressed;

void Init_States();

void SetState(enum FSM_STATE_T newState);

void Fsm_Init();