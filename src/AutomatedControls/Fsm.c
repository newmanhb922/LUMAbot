#include "Fsm.h"

extern float motor1Power;
extern float motor2Power;
extern float motor3Power;
extern float motor4Power;

extern float curPositionX;
extern float curPositionY;

extern float targetPositionX;
extern float targetPositionY;

extern float curVelocity1;
extern float curVelocity2;
extern float curVelocity3;
extern float curVelocity4;

float OffCourseSensor1;
float OffCourseSensor2;
float OffCourseSensor3;
float OffCourseSensor4;
float saveXValue;
float saveYValue;

extern bool motor1Dir;
extern bool motor2Dir;
extern bool motor3Dir;
extern bool motor4Dir;

bool eStopPressed;
short controllerXValue; 
short controllerYValue;
bool hasBeenZeroed;
bool goPressed;

static FSM_STATE_T currentState;
static FSM_STATE_T previousState;

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

void SetState(FSM_STATE_T newState) 
{
    printf("Setting state to: %s\n", xstr(newState));
    currentState = newState;
}

void RunStateFunction() 
{
    if (currentState >= NUM_STATES)
    {
        return;
    }

    (*stateFunctions[currentState])();
}

void AutomatedMoveState()
{
    previousState = currentState;

    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }

    CalculateCurPosition();

    if(sensor1Val < 12 || sensor2Val < 12 || sensor3Val < 12 || sensor4Val < 12)
    {
        SetState(OBSTACLE_AVOIDANCE_STATE);
        saveXValue = targetPositionX;
        saveYValue = targetPositionY;
    }

    OffCourseSensor1 = 0;
    OffCourseSensor2 = 0;
    OffCourseSensor3 = 0;
    OffCourseSensor4 = 0;

    //convert from ft to in
    targetPositionX = targetPositionX * 12; 
    targetPositionY = targetPositionY * 12;

    //find the distance we need to move
    float xDistance = targetPositionX - curPositionX;
    float yDistance = targetPositionY - curPositionY;

    //find the angle of movement and desired velocity of x and y on that angle
    float theta = atan(yDistance/xDistance);
    float velocityX = Velocity * cos(theta);
    float velocityY = Velocity * sin(theta);

    //target motor velocities
    float motor1TargetVelocity = velocityX + velocityY;
    float motor2TargetVelocity = -velocityX + velocityY;
    float motor3TargetVelocity = velocityX + velocityY;
    float motor4TargetVelocity = -velocityX + velocityY;

    //find error
    float motor1VelocityError = motor1TargetVelocity - curVelocity1;
    float motor2VelocityError = motor2TargetVelocity - curVelocity2;
    float motor3VelocityError = motor3TargetVelocity - curVelocity3;
    float motor4VelocityError = motor4TargetVelocity - curVelocity4;

    
    // need to use velocity error as feedback to get motors to that velocity by
    // setting duty cycle, below code isn't what we need to do.

    //convert velocity to a percentage to use for duty cycle
    // motor1Power = (motor1Velocity / Velocity) * 100;
    // motor2Power = (motor2Velocity / Velocity) * 100;
    // motor3Power = (motor3Velocity / Velocity) * 100;
    // motor4Power = (motor4Velocity / Velocity) * 100;

    // SetMotorPWM(1, motor1Power);
    // SetMotorPWM(2, motor2Power);
    // SetMotorPWM(3, motor3Power);
    // SetMotorPWM(4, motor4Power);

    if((xDistance < 1) && (yDistance < 1))
    {
        SetState(STOP_STATE);
    }
}

float ScaleControllerValue(float controllerValue)
{
    float scaled = (controllerValue / MaxControllerValue) * 5;
    return scaled;
}

void ControllerMoveState()
{
    previousState = currentState;

    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
    
    //Scale controller value down to find the target position, at max 5 in away from current position
    targetPositionX = ScaleControllerValue(controllerXValue) + curPositionX;
    targetPositionY = ScaleControllerValue(controllerYValue) + curPositionY;

    //converts motor power to the duty cycle and maps the duty cycle within the allowed constraints
    CalculateMotorPowers();

    //sets motor power
    SetMotorPWM(1, motor1Power);
    SetMotorPWM(2, motor2Power);
    SetMotorPWM(3, motor3Power);
    SetMotorPWM(4, motor4Power);

    // have to set direction here as well with SetMotorDir
    SetMotorDir(1, motor1Dir);
    SetMotorDir(2, motor2Dir);
    SetMotorDir(3, motor3Dir);
    SetMotorDir(4, motor4Dir);

    if(controllerXValue == 0 && controllerYValue == 0)
    {
        SetState(STOP_STATE);
    }    
}

void StopState()
{
    previousState = currentState;

    StopAllMotors();

    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
   
    if(previousState != OBSTACLE_AVOIDANCE_STATE)
    {
        SetState(WAITING_STATE);
    }

    else
    {
        if(sensor1Val > 4 && sensor2Val > 4 && sensor3Val > 4 && sensor4Val > 4)
        {
            SetState(AUTOMATED_MOVE_STATE);
        }
    }
}

void WaitingState()
{
    previousState = currentState;

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
    previousState = currentState;

    StopAllMotors();
    if(!eStopPressed)
    {
        SetState(START_STATE);
    }
}

void ObstacleAvoidanceState()
{
    previousState = currentState;

    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }

    if(sensor1Val < 4 || sensor2Val < 4 || sensor3Val < 4 || sensor4Val < 4)
    {
        SetState(STOP_STATE);
    }
    
    else
    {
        
        if(sensor1Val < 12) //move away in x direction
        {
            targetPositionX = curPositionX + 1;
            OffCourseSensor1++;
            if(sensor1Val > 12)
            {
                targetPositionX = saveXValue;

                //move forward until side sensor doesn't see object
                //move to other x side the number of off course
            }
            if(sensor2Val < 12 || sensor3Val < 12 || sensor4Val < 12)
            {
                SetState(OBSTACLE_AVOIDANCE_STATE);
            }
        }
        else if (sensor2Val < 12) //move away in y direction
        {
            targetPositionY = curPositionY + 1;
            OffCourseSensor2++;
            if(sensor2Val > 12)
            {
                targetPositionY = saveYValue;
            }
            if(sensor1Val < 12 || sensor3Val < 12 || sensor4Val < 12)
            {
                SetState(OBSTACLE_AVOIDANCE_STATE);
            }
        }
        else if(sensor3Val < 12) //x dir
        {
            targetPositionX = curPositionX + 1;
            OffCourseSensor3++;
            if(sensor3Val > 12)
            {
                targetPositionX = saveXValue;
            }
            if(sensor2Val < 12 || sensor1Val < 12 || sensor4Val < 12)
            {
                SetState(OBSTACLE_AVOIDANCE_STATE);
            }  b   
        }
        else if (sensor4Val < 12) //y dir
        {
            targetPositionY = curPositionY + 1;
            OffCourseSensor4++;
            if(sensor4Val > 12)
            {
                targetPositionY = saveYValue;
            }
            if(sensor2Val < 12 || sensor3Val < 12 || sensor1Val < 12)
            {
                SetState(STOP_STATE);
            }
        }

        CalculateMotorPowers();

        SetMotorPWM(1, motor1Power);
        SetMotorPWM(2, motor2Power);
        SetMotorPWM(3, motor3Power);
        SetMotorPWM(4, motor4Power);
}
}

void StartState()
{
    previousState = currentState;

    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
}

void Fsm_Init()
{
    Init_States();
}


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

