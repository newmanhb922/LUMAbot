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

extern bool motor1Dir;
extern bool motor2Dir;
extern bool motor3Dir;
extern bool motor4Dir;

bool eStopPressed;
extern short controllerXValue; 
extern short controllerYValue;
bool hasBeenZeroed;
bool goPressed;

static FSM_STATE_T currentState;
static FSM_STATE_T previousState;

float integralError1;
float integralError2;
float integralError3;
float integralError4;

float previousError1;
float previousError2;
float previousError3;
float previousError4;

float motor1TargetVelocity;
float motor2TargetVelocity;
float motor3TargetVelocity;
float motor4TargetVelocity;

void (*stateFunctions[NUM_STATES])();

void AutomatedMoveState();
void ControllerMoveState();
void StopState();
void WaitingState();
void EStopState();
void ObstacleAvoidanceState();
void StartState();
char * StateToString(FSM_STATE_T state);
float MinFloats(float val1, float val2, float val3, float val4);

/// @brief Calculates the motor power as specified by the PID controller. Updates the motorxPower variables
/// @param velocityXTarget target velocity in the Y direction
/// @param velocityYTarget target velocity in the x direction
void CalculatePID(float velocityXTarget, float velocityYTarget);

/// @brief Calculates the angle formed by the horizontal length (xVal) and the vertical length (yVal)
/// @param xVal the horizontal length or value
/// @param yVal the vertical length or value
/// @return returns the angle in radians
float CalculateTheta(float xVal, float yVal);

/// @brief Scales the controller value to a percentage based on the max controller value
/// @param controllerVal controller value (-32768 to 32767)
/// @return 
float ScaleControllerValue(float controllerValue);

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
    if (newState == AUTOMATED_MOVE_STATE || newState == CONTROLLER_MOVE_STATE)
    { // if new state is automated or controller move, clear the error vars used in PID calculations.
        previousError1 = 0;
        previousError2 = 0;
        previousError3 = 0;
        previousError4 = 0;

        integralError1 = 0;
        integralError2 = 0;
        integralError3 = 0;
        integralError4 = 0;

        motor1Power = 0;
        motor2Power = 0;
        motor3Power = 0;
        motor4Power = 0;
    }
    printf("Setting state to: %s\n", StateToString(newState));
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

    if(sensor1Val < MinDistance || sensor2Val < MinDistance || sensor3Val < MinDistance || sensor4Val < MinDistance)
    {
        SetState(OBSTACLE_AVOIDANCE_STATE);
    }

    OffCourseSensor1 = 0;
    OffCourseSensor2 = 0;
    OffCourseSensor3 = 0;
    OffCourseSensor4 = 0;

    //find the distance we need to move
    float xDistance = targetPositionX - curPositionX; 
    float yDistance = targetPositionY - curPositionY;

    //find the angle of movement and desired velocity of x and y on that angle
    float theta = CalculateTheta(xDistance, yDistance);
    
    float velocityXTarget = Velocity * cos(theta);
    float velocityYTarget = Velocity * sin(theta);

    char helperStr[200];
    sprintf(helperStr, "theta: %.2f, xDistance: %.2f, yDistance: %.2f\n", theta, xDistance, yDistance);
    Debug(helperStr);

    CalculatePID(velocityXTarget, velocityYTarget);

    CalculateMotorDir();

    BoundMotorPowers();
    sprintf(helperStr, "after bounding powers motor1Power: %.2f, motor2Power: %.2f\n", motor1Power, motor2Power);
    Debug(helperStr);
    SetMotorPWM(1, motor1Power);
    SetMotorPWM(2, motor2Power);
    SetMotorPWM(3, motor3Power);
    SetMotorPWM(4, motor4Power);

    // have to set direction here as well with SetMotorDir
    SetMotorDir(1, motor1Dir);
    SetMotorDir(2, motor2Dir);
    SetMotorDir(3, motor3Dir);
    SetMotorDir(4, motor4Dir);

    if((xDistance < 1) && (yDistance < 1))
    {
        integralError1 = 0;
        integralError2 = 0;
        integralError3 = 0;
        integralError4 = 0;
    
        SetState(STOP_STATE);
    }
}

void ControllerMoveState()
{
    previousState = currentState;

    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
    
    float theta = CalculateTheta(controllerXValue, controllerYValue);

    float velocityXTarget = ScaleControllerValue(controllerXValue) * Velocity * cos(theta);
    float velocityYTarget = ScaleControllerValue(controllerYValue) * Velocity * sin(theta);


    CalculatePID(velocityXTarget, velocityYTarget);

    //CalculateMotorDir();

    //BoundMotorPowers();

	printf("Motor1Power: %.2f, motor2Power: %.2f, motor3Power: %.2f, motor4Power: %.2f\n", motor1Power, motor2Power, motor3Power, motor4Power);
	printf("motor1Dir: %d, motor2Dir: %d, motor3Dir: %d, motor4Dir: %d\n", motor1Dir, motor2Dir, motor3Dir, motor4Dir);

    //sets motor power
    SetMotorPWM(1, motor1Power, motor1TargetVelocity > 0);
    SetMotorPWM(2, motor2Power, motor2TargetVelocity > 0);
    SetMotorPWM(3, motor3Power, motor3TargetVelocity > 0);
    SetMotorPWM(4, motor4Power, motor4TargetVelocity > 0);

    // have to set direction here as well with SetMotorDir
    // SetMotorDir(1, motor1Dir);
    // SetMotorDir(2, motor2Dir);
    // SetMotorDir(3, motor3Dir);
    // SetMotorDir(4, motor4Dir);

    if(controllerXValue == 0 && controllerYValue == 0)
    {
	Debug("controllerXValue and controllerYValue are both 0, should be stopping motors\n");
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
        if(sensor1Val > VeryCloseDistance && sensor2Val > VeryCloseDistance && sensor3Val > VeryCloseDistance && sensor4Val > VeryCloseDistance)
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

    if(sensor1Val < VeryCloseDistance || sensor2Val < VeryCloseDistance || sensor3Val < VeryCloseDistance || sensor4Val < VeryCloseDistance)
    {
        SetState(STOP_STATE);
    }
    
    else
    {
        if(sensor1Val < MinDistance && (MinFloats(sensor1Val, sensor2Val, sensor3Val, sensor4Val) == sensor1Val)) //move away in x direction add that sensor 1 is less than all other sensors
        {
            targetPositionX = curPositionX + 1;
            OffCourseSensor1++;
            if((sensor2Val < MinDistance && sensor2Val < sensor1Val) || (sensor3Val < MinDistance && sensor3Val < sensor1Val) || (sensor4Val < MinDistance && sensor4Val < sensor1Val))
            {
                SetState(OBSTACLE_AVOIDANCE_STATE);
            }
        }
        else if (sensor2Val < MinDistance && (MinFloats(sensor1Val, sensor2Val, sensor3Val, sensor4Val) == sensor2Val)) //move away in -y direction
        {
            targetPositionY = curPositionY - 1;
            OffCourseSensor2--;
            if((sensor1Val < MinDistance && sensor1Val < sensor2Val) || (sensor3Val < MinDistance && sensor3Val < sensor2Val) || (sensor4Val < MinDistance && sensor4Val < sensor2Val))
            {
                SetState(OBSTACLE_AVOIDANCE_STATE);
            }
        }
        else if(sensor3Val < MinDistance && (MinFloats(sensor1Val, sensor2Val, sensor3Val, sensor4Val) == sensor3Val)) //-x dir
        {
            targetPositionX = curPositionX - 1;
            OffCourseSensor3--;
            if((sensor1Val < MinDistance && sensor1Val < sensor3Val) || (sensor2Val < MinDistance && sensor2Val < sensor3Val) || (sensor4Val < MinDistance && sensor4Val < sensor3Val))
            {
                SetState(OBSTACLE_AVOIDANCE_STATE);
            }  
        }
        else if (sensor4Val < MinDistance && (MinFloats(sensor1Val, sensor2Val, sensor3Val, sensor4Val) == sensor4Val)) //-y dir
        {
            targetPositionY = curPositionY - 1; 
            OffCourseSensor4--;
            if((sensor1Val < MinDistance && sensor1Val < sensor4Val) || (sensor2Val < MinDistance && sensor2Val < sensor4Val) || (sensor3Val < MinDistance && sensor3Val < sensor4Val))
            {
                SetState(OBSTACLE_AVOIDANCE_STATE);
            }
        }
        
        if (sensor1Val > MinDistance && sensor2Val > MinDistance && sensor3Val > MinDistance && sensor4Val > MinDistance)
        {
            if(OffCourseSensor1 == 0 && OffCourseSensor2 == 0 && OffCourseSensor3 == 0 && OffCourseSensor4 == 0)
            {
                SetState(AUTOMATED_MOVE_STATE);
            }
            else
            {
                if(OffCourseSensor1 > 0)
                {
                    //checking sensor 4 for side
                    targetPositionX = curPositionX - OffCourseSensor1;
                    OffCourseSensor1 = 0;
                    //move forward until side sensor doesn't see object
                }
                if(OffCourseSensor2 > 0)
                {
                    //checking sensor 1
                    targetPositionY = curPositionY - OffCourseSensor2;
                    OffCourseSensor2 = 0;
                }
                if(OffCourseSensor3 > 0)
                {
                    //checking sensor 2
                    targetPositionX = curPositionX - OffCourseSensor3;
                    OffCourseSensor3 = 0;
                }
                if(OffCourseSensor4 > 0)
                {
                    //checking sensor 1
                    targetPositionY = curPositionY - OffCourseSensor4;
                    OffCourseSensor4 = 0;
                }
            }
        }

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
    }
}

void StartState()
{
    previousState = currentState;

    if(eStopPressed)
    {
        SetState(E_STOP_STATE);
    }
    SetState(WAITING_STATE);
}

void Fsm_Init()
{
    integralError1 = 0;
    integralError2 = 0;
    integralError3 = 0;
    integralError4 = 0;
    
    previousError1 = 0;
    previousError2 = 0;
    previousError3 = 0;
    previousError4 = 0;

    Init_States();
}

char * StateToString(FSM_STATE_T state)
{
    switch (state)
    {
        case AUTOMATED_MOVE_STATE:
            return "Automated Move State";
        case CONTROLLER_MOVE_STATE:
            return "Controller Move State";
        case STOP_STATE:
            return "Stop State";
        case WAITING_STATE:
            return "Waiting State";
        case E_STOP_STATE:
            return "E Stop State";
        case OBSTACLE_AVOIDANCE_STATE:
            return "Obstacle Avoidance State";
        case START_STATE:
            return "Start State";
    }
}

float MinFloats(float val1, float val2, float val3, float val4)
{
    float minVal = fminf(val1, val2);
    minVal = fminf(val3, minVal);
    return fminf(val4, minVal);
}

void CalculatePID(float velocityXTarget, float velocityYTarget)
{
    char helperStr[200];

    motor1TargetVelocity = velocityXTarget + velocityYTarget; 
    motor2TargetVelocity = -velocityXTarget + velocityYTarget; 
    motor3TargetVelocity = velocityXTarget + velocityYTarget; 
    motor4TargetVelocity = -velocityXTarget + velocityYTarget;
    sprintf(helperStr, "motor1TargetVel: %.2f, motor2TargetVel: %.2f\n", motor1TargetVelocity, motor2TargetVelocity);
    //Debug(helperStr);
	printf(helperStr);
    //find error
    float motor1VelocityError = motor1TargetVelocity - curVelocity1;
    float motor2VelocityError = motor2TargetVelocity - curVelocity2;
    float motor3VelocityError = motor3TargetVelocity - curVelocity3;
    float motor4VelocityError = motor4TargetVelocity - curVelocity4;

    sprintf(helperStr, "motor1VelError: %.2f, motor2VelError: %.2f\n", motor1VelocityError, motor2VelocityError);
//    Debug(helperStr);
	printf(helperStr);
    integralError1 += motor1VelocityError;
    integralError2 += motor2VelocityError;
    integralError3 += motor3VelocityError;
    integralError4 += motor4VelocityError;

    float pidOutput1 = KP * motor1VelocityError + KI * integralError1 + KD * (motor1VelocityError - previousError1);
    float pidOutput2 = KP * motor2VelocityError + KI * integralError2 + KD * (motor2VelocityError - previousError2);
    float pidOutput3 = KP * motor3VelocityError + KI * integralError3 + KD * (motor3VelocityError - previousError3);
    float pidOutput4 = KP * motor4VelocityError + KI * integralError4 + KD * (motor4VelocityError - previousError4);

    previousError1 = motor1VelocityError;
    previousError2 = motor2VelocityError;
    previousError3 = motor3VelocityError;
    previousError4 = motor4VelocityError;

    // we always want pidOutputx to be same sign as motorxTargetVelocity
    // if (pidOutput1 < 0 && motor1TargetVelocity > 0)
    // {
    //     pidOutput1 = pidOutput1 * -1;
    // }
    // else if (pidOutput1 > 0 && motor1TargetVelocity < 0)
    // {
    //     pidOutput1 = pidOutput1 * -1;
    // }

    // if (pidOutput2 < 0 && motor2TargetVelocity > 0)
    // {
    //     pidOutput2 = pidOutput2 * -1;
    // }
    // else if (pidOutput2 > 0 && motor2TargetVelocity < 0)
    // {
    //     pidOutput2 = pidOutput2 * -1;
    // }

    // if (pidOutput3 < 0 && motor3TargetVelocity > 0)
    // {
    //     pidOutput3 = pidOutput3 * -1;
    // }
    // else if (pidOutput3 > 0 && motor3TargetVelocity < 0)
    // {
    //     pidOutput3 = pidOutput3 * -1;
    // }

    // if (pidOutput4 < 0 && motor4TargetVelocity > 0)
    // {
    //     pidOutput4 = pidOutput4 * -1;
    // }
    // else if (pidOutput4 > 0 && motor4TargetVelocity < 0)
    // {
    //     pidOutput4 = pidOutput4 * -1;
    // }

    sprintf(helperStr, "pid1: %.2f, pid2: %.2f\n", pidOutput1, pidOutput2);
    Debug(helperStr);
    motor1Power += pidOutput1;
    motor2Power += pidOutput2;
    motor3Power += pidOutput3;
    motor4Power += pidOutput4;
    //Debug(helperStr);
    motor1Power = pidOutput1;
    printf(helperStr);
    motor2Power = pidOutput2;
    motor3Power = pidOutput3;
    motor4Power = pidOutput4;
}

float CalculateTheta(float xVal, float yVal)
{
    float theta = PI / 2;
    if (xVal != 0)
    {
        theta = atan(yVal / xVal); // only returns values from - pi / 2 to pi / 2 (quadrants 1 and 4)
    }
    if (xVal < 0)
    { // if we should be in quadrants 2 or 3, add PI to theta to get to these quadrants
        theta = theta + PI;
    }
    return theta;
}

float ScaleControllerValue(float controllerValue)
{
    float scaled = (controllerValue / MaxControllerValue);
    return scaled;
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

