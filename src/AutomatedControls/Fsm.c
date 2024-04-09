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

extern float lastMotor1Power;
extern float lastMotor2Power;
extern float lastMotor3Power;
extern float lastMotor4Power;

extern short controllerSpin;

void (*stateFunctions[NUM_STATES])();

void AutomatedMoveState();
void ControllerMoveState();
void StopState();
void WaitingState();
void EStopState();
void ObstacleAvoidanceState();
void StartState();
void ControllerSpinState();
char * StateToString(FSM_STATE_T state);
float MinFloats(float val1, float val2, float val3, float val4);
void StopAllMotorsWithDecel();

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
    stateFunctions[CONTROLLER_SPIN_STATE] = ControllerSpinState;

}

void SetState(FSM_STATE_T newState) 
{
    if (newState == CONTROLLER_MOVE_STATE || newState == AUTOMATED_MOVE_STATE)
    {
        lastMotor1Power = 0.0f;
        lastMotor2Power = 0.0f;
        lastMotor3Power = 0.0f;
        lastMotor4Power = 0.0f;
    }
    if (newState == STOP_STATE || newState == E_STOP_STATE)
    {
        goPressed = false;
        
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
    float theta = PI / 2;
    if(xDistance != 0)
    {
        theta = atan(yDistance/xDistance);
    }
    if (xDistance < 0 || (xDistance == 0 && yDistance < 0))
    {
        theta = theta + PI;
    }
    
    float velocityX = Velocity * cos(theta);
    float velocityY = Velocity * sin(theta);

    char helperStr[200];
    sprintf(helperStr, "theta: %.2f, xDistance: %.2f, yDistance: %.2f\n", theta, xDistance, yDistance);
    Debug(helperStr);
    printf(helperStr);
    //target motor velocities
    float motor1TargetVelocity = velocityX + velocityY; 
    float motor2TargetVelocity = -velocityX + velocityY; 
    float motor3TargetVelocity = velocityX + velocityY; 
    float motor4TargetVelocity = -velocityX + velocityY;
    sprintf(helperStr, "motor1TargetVel: %.2f, motor2TargetVel: %.2f\n", motor1TargetVelocity, motor2TargetVelocity);
    Debug(helperStr);
    printf(helperStr);
    //find error
    float motor1VelocityError = motor1TargetVelocity - curVelocity1;
    float motor2VelocityError = motor2TargetVelocity - curVelocity2;
    float motor3VelocityError = motor3TargetVelocity - curVelocity3;
    float motor4VelocityError = motor4TargetVelocity - curVelocity4;

    sprintf(helperStr, "motor1VelError: %.2f, motor2VelError: %.2f\n", motor1VelocityError, motor2VelocityError);
    Debug(helperStr);
   // printf(helperStr);

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

    sprintf(helperStr, "pid1: %.2f, pid2: %.2f\n", pidOutput1, pidOutput2);
    Debug(helperStr);
   // printf(helperStr);
    motor1Power += pidOutput1;
    motor2Power += pidOutput2;
    motor3Power += pidOutput3;
    motor4Power += pidOutput4;

    //AccelMotorPowers();
    
    //CalculateMotorDir();

    //BoundMotorPowers();
    sprintf(helperStr, "after bounding powers motor1Power: %.2f, motor2Power: %.2f\n", motor1Power, motor2Power);
    Debug(helperStr);
   // printf(helperStr);
    
    SetMotorSpeed(1, motor1Power);
    SetMotorSpeed(2, motor2Power);
    SetMotorSpeed(3, motor3Power);
    SetMotorSpeed(4, motor4Power);
    
//    SetMotorPWM(1, motor1Power);
//    SetMotorPWM(2, motor2Power);
//    SetMotorPWM(3, motor3Power);
//    SetMotorPWM(4, motor4Power);

    // have to set direction here as well with SetMotorDir
//    SetMotorDir(1, motor1Dir);
//    SetMotorDir(2, motor2Dir);
//    SetMotorDir(3, motor3Dir);
//    SetMotorDir(4, motor4Dir);

    if((fabs(xDistance) < 1) && (fabs(yDistance) < 1))
    {
        integralError1 = 0;
        integralError2 = 0;
        integralError3 = 0;
        integralError4 = 0;
        
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

    //AccelMotorPowers();
    
    SetMotorSpeed(1, motor1Power);
    SetMotorSpeed(2, motor2Power);
    SetMotorSpeed(3, motor3Power);
    SetMotorSpeed(4, motor4Power);
    //sets motor power
  //  SetMotorPWM(1, motor1Power);
  //  SetMotorPWM(2, motor2Power);
   // SetMotorPWM(3, motor3Power);
   // SetMotorPWM(4, motor4Power);

    // have to set direction here as well with SetMotorDir
 //   SetMotorDir(1, motor1Dir);
 //   SetMotorDir(2, motor2Dir);
  //  SetMotorDir(3, motor3Dir);
  //  SetMotorDir(4, motor4Dir);

    if(controllerXValue == 0 && controllerYValue == 0)
    {
        SetState(STOP_STATE);
    }    
}

void ControllerSpinState()
{
    previousState = currentState;
    
    if (controllerSpin < 0)
    {
        SetMotorSpeed(1, -1 * ControllerDutyCycle);
        SetMotorSpeed(2, ControllerDutyCycle);
        SetMotorSpeed(3, ControllerDutyCycle);
        SetMotorSpeed(4, -1 * ControllerDutyCycle);
    }
    else if (controllerSpin > 0)
    {
        SetMotorSpeed(1, ControllerDutyCycle);
        SetMotorSpeed(2, -1 * ControllerDutyCycle);
        SetMotorSpeed(3, -1 * ControllerDutyCycle);
        SetMotorSpeed(4, ControllerDutyCycle);
    }    
    else if (controllerSpin == 0)
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
    else if ((controllerSpin != 0) && !goPressed)
    {
        SetState(CONTROLLER_SPIN_STATE);
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
        case CONTROLLER_SPIN_STATE:
            return "Controller Spin State";
        default:
            return "Unknown State";
    }
}

float MinFloats(float val1, float val2, float val3, float val4)
{
    float minVal = fminf(val1, val2);
    minVal = fminf(val3, minVal);
    return fminf(val4, minVal);
}

void StopAllMotorsWithDecel()
{
    float motor1Step = MAX_DUTY_CHANGE * -1;
    float motor2Step = MAX_DUTY_CHANGE * -1;
    
    float motor1PowerDecel = lastMotor1Power;
    float motor2PowerDecel = lastMotor2Power;
    
    if (motor1PowerDecel < 0)
    {
        motor1PowerDecel = motor1PowerDecel * -1;
    }
    
    if (motor2PowerDecel < 0)
    {
        motor2PowerDecel = motor2PowerDecel * -1;
    }
    
    while (motor1PowerDecel != 0.0f && motor2PowerDecel != 0.0f)
    {  
              
        if (motor1PowerDecel <= MAX_DUTY_CHANGE)
        {
            motor1PowerDecel = 0.0f;
        }
        
        if (motor2PowerDecel <= MAX_DUTY_CHANGE)
        {
            motor2PowerDecel = 0.0f;
        }

        SetMotorPWM(1, motor1PowerDecel);
        SetMotorPWM(2, motor2PowerDecel);
        SetMotorPWM(3, motor1PowerDecel);
        SetMotorPWM(4, motor2PowerDecel);
        
        if (motor1PowerDecel == 0.0f && motor2PowerDecel == 0.0f)
        {
            StopAllMotors();
            break;
        }
        
        motor1PowerDecel = motor1PowerDecel + motor1Step;
        motor2PowerDecel = motor2PowerDecel + motor2Step;
        delayMicroseconds(100);
    }   
    lastMotor1Power = 0.0f;
    lastMotor2Power = 0.0f;        
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

