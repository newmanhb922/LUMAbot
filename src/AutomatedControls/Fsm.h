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
#define KD                  0
#define KI                  0
#define KP                  3
#define MinDistance         12
#define VeryCloseDistance   4
#define ControllerDutyCycle 35
#define MAX_DUTY_CHANGE     1.0f

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
