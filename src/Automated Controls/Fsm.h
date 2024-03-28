#ifndef FSM_H
#define FSM_H

#include <wiringPi.h>
#include <stdbool.h>
#include <stdio.h>
#include "MotorControl.h"
#include "Controller.h"
#include "Ultrasonic.h"
#include "Position.h"

typedef enum
{
    MOVE_STATE, STOP_STATE, WAITING_STATE, E_STOP_STATE, 
    OBSTACLE_AVOIDANCE_STATE, START_STATE
} FSM_STATE_T;

void Init_States();

void SetState(enum FSM_STATE_T newState);