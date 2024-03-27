#include "Fsm.h"

static FSM_STATE_T currentState;

void (*stateFunctions[NUM_STATES])();

void MoveState();
void StopState();
void WaitingState();
void EStopState();
void ObstacleAvoidanceState();
void StartState();

void Init_States()
{
    currentState = START_STATE;
    stateFunctions[MOVE_STATE] = MoveState;
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

void MoveState()
{

}

void StopState()
{
    
}

void WaitingState()
{
    
}

void EStopState()
{
    
}

void ObstacleAvoidanceState()
{
    
}

void StartState()
{
    
}


//when trying to move, go into move state
//in the move state, it'll get current position, 
//calculate angle function, while moving constantly caluclating the angle and data
//for all 4 motors



//send message payload string ex: "(0,0)"
//parse through message to get x and y coords
// case structure to find which letter is correct doesnt matter jk
//save letter spot as current position jk
//determine how to move to new position based on current spot


//how to move
//figure out how many motor rotation/encoder clicks each coord takes
//subtract new coord from old one ex: new = P (-7,-14), old = B (7,0)
// move -14 on x, move -14 on y 