#include "Position.h"

float curPositionX;
float curPositionY;
float targetPositionX;
float targetPositionY;

float motor1Power;
float motor2Power;
float motor3Power;
float motor4Power;

extern volatile int encoder1Count;
extern volatile int encoder2Count;
extern volatile int encoder3Count;
extern volatile int encoder4Count;

extern volatile bool count1Changing;
extern volatile bool count2Changing;
extern volatile bool count3Changing;
extern volatile bool count4Changing;

float curVelocity1;
float curVelocity2;
float curVelocity3;
float curVelocity4;

// position of each motor in inches, used to calculate velocity
float curPosition1;
float curPosition2;
float curPosition3;
float curPosition4;

// last position of each motor in inches, used to calculate velocity
float lastPosition1;
float lastPosition2;
float lastPosition3;
float lastPosition4;

float lastMotor1Power;
float lastMotor2Power;
float lastMotor3Power;
float lastMotor4Power;

float motorToWheelRatio;
float sqrt_2;

bool motor1Dir;
bool motor2Dir;
bool motor3Dir;
bool motor4Dir;

// last time we calculated motor velocity
unsigned int lastTime1;
unsigned int lastTime2;
unsigned int lastTime3;
unsigned int lastTime4;

unsigned short readDataCounter;

extern bool controllerConnected;

void InitPosition()
{
    curPositionX = 0.0f;
    curPositionY = 0.0f;
    targetPositionX = 0.0f;
    targetPositionY = 0.0f;

    curPosition1 = 0.0f;
    curPosition2 = 0.0f;
    curPosition3 = 0.0f;
    curPosition4 = 0.0f;

    lastMotor1Power = 0.0f;
    lastMotor2Power = 0.0f;

    motorToWheelRatio = WHEEL_DIAM * PI / (GEAR_RATIO * COUNTS_PER_MOTOR_REV);
    sqrt_2 = sqrt(2);
}

void StartSamplingData()
{
    readDataCounter = 1;
    lastPosition1 = 0.0f;
    lastPosition2 = 0.0f;
    lastPosition3 = 0.0f;
    lastPosition4 = 0.0f;

    lastTime1 = micros();
    lastTime2 = micros();
    lastTime3 = micros();
    lastTime4 = micros();

    curVelocity1 = 0.0f;
    curVelocity2 = 0.0f;
    curVelocity3 = 0.0f;
    curVelocity4 = 0.0f;

    CalculateCurVelocity();
    signal(SIGALRM, ReadData);
    ualarm(10000, 10000); // ReadData function called every 10 ms
}

void CalculateCurPosition()
{
   // https://github.com/FTC7393/EVLib/wiki/Mecanum-Wheels

   // FL and BR wheels move robot forward and right when wheel turns forward.
   // FR and BL wheels move robot forward and left when wheels move forward.

    // average encoder changes then multiply by wheel circumference and divide by gear ratio and sqrt(2) (wheel only moves forward sqrt(2) amount of rotation)
    curPosition1 = encoder1Count * motorToWheelRatio;
    curPosition2 = encoder2Count * motorToWheelRatio * -1; // when wheels two and three move forward, the motor moves backward so encoder counts down
    curPosition3 = encoder3Count * motorToWheelRatio * -1;
    curPosition4 = encoder4Count * motorToWheelRatio;

    curPositionY = ((curPosition1 + curPosition2 + curPosition3 + curPosition4)  / (NUM_OF_MOTORS * sqrt_2)) * YPOS_CALIBRATION;
    curPositionX = ((((curPosition1 + curPosition3) / (NUM_OF_MOTORS / 2)) - ((curPosition2 + curPosition4) / (NUM_OF_MOTORS / 2))) / sqrt_2) * XPOS_CALIBRATION; 
}

void CalculateCurVelocity()
{   
    unsigned int tempTime = micros();

    curVelocity1 = (curPosition1 - lastPosition1) * 1000000 / (tempTime - lastTime1);
    lastTime1 = tempTime;
    lastPosition1 = curPosition1;

    tempTime = micros();
    curVelocity2 = (curPosition2 - lastPosition2) * 1000000 / (tempTime - lastTime2);
    lastTime2 = tempTime;
    lastPosition2 = curPosition2;

    tempTime = micros();
    curVelocity3 = (curPosition3 - lastPosition3) * 1000000 / (tempTime - lastTime3);
    lastTime3 = tempTime;
    lastPosition3 = curPosition3;

    tempTime = micros();
    curVelocity4 = (curPosition4 - lastPosition4) * 1000000 / (tempTime - lastTime4);
    lastTime4 = tempTime;
    lastPosition4 = curPosition4;
}

void CalculateMotorDir()
{
    if (motor1Power >= 0)
    {
        motor1Dir = 0; // go forward
        motor3Dir = 1;
    }
    else
    {
        motor1Dir = 1; // go backward
        motor3Dir = 0;
        motor1Power = motor1Power * -1; // duty cycle values always positive
        motor3Power = motor3Power * -1;
    }

    if (motor2Power >= 0)
    {
        motor2Dir = 1; // go forward
        motor4Dir = 0;
    }
    else
    {
        motor2Dir = 0; // go backward
        motor4Dir = 1;
        motor2Power = motor2Power * -1; // duty cycle values always positive
        motor3Power = motor3Power * -1;
    }
}

void CalculateMotorPowers()
{
    float yDiff = targetPositionY - curPositionY;
    float xDiff = targetPositionX - curPositionX;
    float yDiffAbs = yDiff;
    float xDiffAbs = xDiff;
    float dutyCycleMotors1_3;
    float dutyCycleMotors2_4;
    float max = 0;

    if (yDiffAbs < 0)
    {
        yDiffAbs = yDiffAbs * -1;
    }

    if (xDiffAbs < 0)
    {
        xDiffAbs = xDiffAbs * -1;
    }

    if (xDiffAbs > yDiffAbs)
    {
        max = xDiffAbs;
    }

    else
    {
	max = yDiffAbs;
    }

    // motors 1 and 3 are same and 2 and 4 are same when not rotating
    motor1Power = ControllerDutyCycle * (yDiff + xDiff) / max;
    motor2Power = ControllerDutyCycle * (yDiff - xDiff) / max;
   // motor3Power = motor1Power;
    //motor4Power = motor2Power;
    
    // slow down the acceleration and deceleration
   // AccelMotorPowers();

  //  CalculateMotorDir();

  //  BoundMotorPowers();
    motor3Power = motor1Power;
    motor4Power = motor2Power;
}

void BoundMotorPowers()
{
    if (motor1Power > MaxDutyCycle)
    {
        motor1Power = MaxDutyCycle;
    }
    else if (motor1Power < MinDutyCycle)
    {
        motor1Power = MinDutyCycle;
    }

    if (motor2Power > MaxDutyCycle)
    {
        motor2Power = MaxDutyCycle;
    }
    else if (motor2Power < MinDutyCycle)
    {
        motor2Power = MinDutyCycle;
    }

    if (motor3Power > MaxDutyCycle)
    {
        motor3Power = MaxDutyCycle;
    }
    else if (motor3Power < MinDutyCycle)
    {
        motor3Power = MinDutyCycle;
    }

    if (motor4Power > MaxDutyCycle)
    {
        motor4Power = MaxDutyCycle;
    }
    else if (motor4Power < MinDutyCycle)
    {
        motor4Power = MinDutyCycle;
    }
}

void AccelMotorPowers()
{
    if ((motor1Power - lastMotor1Power) > MAX_DUTY_CHANGE)
    {
        motor1Power = lastMotor1Power + MAX_DUTY_CHANGE;
    }
    else if ((motor1Power - lastMotor1Power) < (MAX_DUTY_CHANGE * -1))
    {
        motor1Power = lastMotor1Power - MAX_DUTY_CHANGE;
    }

    if ((motor2Power - lastMotor2Power) > MAX_DUTY_CHANGE)
    {
        motor2Power = lastMotor2Power + MAX_DUTY_CHANGE;
    }
    else if ((motor2Power - lastMotor2Power) < (MAX_DUTY_CHANGE * -1))
    {
        motor2Power = lastMotor2Power - MAX_DUTY_CHANGE;
    }
    
    if ((motor3Power - lastMotor3Power) > MAX_DUTY_CHANGE)
    {
        motor3Power = lastMotor3Power + MAX_DUTY_CHANGE;
    }
    else if ((motor3Power - lastMotor3Power) < (MAX_DUTY_CHANGE * -1))
    {
        motor3Power = lastMotor3Power - MAX_DUTY_CHANGE;
    }

    if ((motor4Power - lastMotor4Power) > MAX_DUTY_CHANGE)
    {
        motor4Power = lastMotor4Power + MAX_DUTY_CHANGE;
    }
    else if ((motor4Power - lastMotor4Power) < (MAX_DUTY_CHANGE * -1))
    {
        motor4Power = lastMotor4Power - MAX_DUTY_CHANGE;
    }
    
    lastMotor1Power = motor1Power;
    lastMotor2Power = motor2Power;
    lastMotor3Power = motor3Power;
    lastMotor4Power = motor4Power;
}

void ResetEncoderCounts()
{
    while (count1Changing) {};
    count1Changing = true;
    encoder1Count = 0;
    count1Changing = false;

    while (count2Changing) {};
    count2Changing = true;
    encoder2Count = 0;
    count2Changing = false;

    while (count3Changing) {};
    count3Changing = true;
    encoder3Count = 0;
    count3Changing = false;

    while (count4Changing) {};
    count4Changing = true;
    encoder4Count = 0;
    count4Changing = false;
}

void SetMotorSpeed(int motorNum, float dutyCycle)
{
    bool forward = 1;
    if (motorNum == 1 || motorNum == 4)
    {
        forward = dutyCycle < 0;
    }
    else if (motorNum == 2 || motorNum == 3)
    {
        forward = dutyCycle > 0;
    }
    
    if (dutyCycle < 0)
    {
        dutyCycle = dutyCycle * -1;
    }
    
    SetMotorDir(motorNum, forward);
    SetMotorPWM(motorNum, dutyCycle);
}

// use this to: read controller (joystick) input, 
             // calculate motor velocity,
             // read ultrasonic sensor data
             // send position data to UI
void ReadData()
{
    if ((readDataCounter % 100) == 0) // every second
    {
        SendCurPositionToUI();
    }
    else if ((readDataCounter % 7) == 0) // every 70 ms
    {
        CalculateCurPosition();
    }
    // waiting a little longer to read velocity gives us more accurate readings
    else if ((readDataCounter % 20) == 0) // every 200 ms
    {
        CalculateCurVelocity();
    }
    else if ((readDataCounter % 5) == 0) // every 50 ms
    {
        // running this causes program to break so don't run it yet.
        //ReadUltrasonicSensors(); //don't run this until sensors are wired in
    }
    
    if (controllerConnected)
    { // if controller is connected and ready, read joystick data every ms
        ReadJoystickData();
    }
    if (GetCurrentState() != CONTROLLER_MOVE_STATE && GetCurrentState() != AUTOMATED_MOVE_STATE
        && GetCurrentState() != CONTROLLER_SPIN_STATE && (readDataCounter % 100) == 0)
    { // if we aren't in a "moving" state, try to connect to controller every 1 second
        InitController();
    }

    readDataCounter++;
    if (readDataCounter > 100)
    {
        readDataCounter = 1;
    }
}
