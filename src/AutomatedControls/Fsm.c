#include "Fsm.h"

extern float motor1Power;
extern float motor2Power;
extern float motor3Power;
extern float motor4Power;
extern float curPositionX;
extern float curPositionY;
extern float targetPositionX;
extern float targetPositionY;
extern bool eStopPressed;
extern short controllerXValue; 
extern short controllerYValue;
extern bool hasBeenZeroed;
extern bool goPressed;

static FSM_STATE_T currentState;

void (*stateFunctions[NUM_STATES])();

void AutomatedMoveState();
void ControllerMoveState();
void StopState();
void WaitingState();
void EStopState();
void ObstacleAvoidanceState();
void StartState();

void Init_States()
{
    currentState = START_STATE;
    stateFunctions[AUTOMATED_MOVE_STATE] = AutomatedMoveState;
    stateFunctions[CONTROLLER_MOVE_STATE] = ControllerMoveState;
    stateFunctions[STOP_STATE] = StopState;
    stateFunctions[WAITING_STATE] = WaitingState;
    stateFunctions[E_STOP_STATE] = EStopState;
    stateFunctions[OBSTACLE_AVOIDANCE_STATE] = ObstacleAvoidanceState;
    stateFunctions[START_STATE] = StartState;

}

void SetState(enum FSM_STATE_T newState) 
{
    currentState = newState;
}

void RunStateFunction() 
{
    if (currentState >= NUM_STATES)
    {
        return;
    }

    stateFunctions[currentState];
}

void AutomatedMoveState()
{
    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
    SetState(STOP_STATE);

}

float ScaleControllerValue(float controllerValue)
{
    float scaled = (controllerValue / MaxControllerValue) * 5;
    return scaled;
}

void ControllerMoveState()
{
    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
    
    targetPositionX = ScaleControllerValue(controllerXValue) + curPositionX;
    targetPositionY = ScaleControllerValue(controllerYValue) + curPositionY;

    CalculateMotorPowers();

    SetMotorPWM(1, motor1Power);
    SetMotorPWM(2, motor2Power);
    SetMotorPWM(3, motor3Power);
    SetMotorPWM(4, motor4Power);
    
    if(controllerXValue == 0 && controllerYValue == 0)
    {
        SetState(STOP_STATE);
    }    
}

void StopState()
{
    StopAllMotors();
    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
    SetState(WAITING_STATE);
    
}

void WaitingState()
{
    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
    if(goPressed && (controllerXValue == 0) && (controllerYValue == 0) && hasBeenZeroed)
    {
        SetState(AUTOMATED_MOVE_STATE);
    }
    else if((controllerXValue != 0 || controllerYValue != 0) && !goPressed)
    {
        SetState(CONTROLLER_MOVE_STATE);
    }
}

void EStopState()
{
    StopAllMotors();
    if(!eStopPressed)
    {
        SetState(WAITING_STATE);
    }
}

void ObstacleAvoidanceState()
{
    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
}

void StartState()
{
    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
    SetUpMotors();
}

void Fsm_Init()
{
    Init_States();
}


//when trying to move, go into move state
//in the move state, it'll get current position

// FMM - don't need to calculate angle. Use CalculateMotorPowers in Position.c to 
// get motor powers scaled from -1 to 1. Then multiply that by some duty cycle constant 
// to set motor speeds. Maybe have some sort of "ramp up" speed function that 'slowly' increases
// speed and then slow down to a lower speed when we are close to the point.


//send message payload string ex: "(0,0)"
//parse through message to get x and y coords
// case structure to find which letter is correct doesnt matter jk
//save letter spot as current position jk
//determine how to move to new position based on current spot


//how to move
//figure out how many motor rotation/encoder clicks each coord takes
//subtract new coord from old one ex: new = P (-7,-14), old = B (7,0)
// move -14 on x, move -14 on y 


//whenever you recieve a message in controller.c you would 
//axis 1 = y
//axis 0 = x
//goes from signed 16 bit: - 32768 to 32767

//only