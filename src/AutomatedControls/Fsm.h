#ifndef FSM_H
#define FSM_H

#include <wiringPi.h>
#include <stdbool.h>
#include <stdio.h>
#include "../GeneralControls/Motors/MotorControl.h"
#include "../Controller/Controller.h"
#include "../Sensors/Ultrasonic.h"
#include "../GeneralControls/Position/Position.h"
#include "../I2C_Module/I2CModule.h"

#define NUM_STATES          7
#define MaxDutyCycle        80
#define MinDutyCycle        10
#define MaxControllerValue  32767
#define Velocity            12 // 1 ft/s
#define KD                  1
#define KI                  1
#define KP                  1
#define MinDistance         12
#define VeryCloseDistance   4
#define ControllerDutyCycle 30

typedef enum
{
    AUTOMATED_MOVE_STATE, CONTROLLER_MOVE_STATE,  STOP_STATE, WAITING_STATE, E_STOP_STATE, 
    OBSTACLE_AVOIDANCE_STATE, START_STATE
} FSM_STATE_T;

extern bool eStopPressed;
extern bool hasBeenZeroed;
extern bool goPressed;

void Init_States();

void SetState(FSM_STATE_T newState);

void Fsm_Init();

void RunStateFunction();

#endif
