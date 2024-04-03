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

float motorToWheelRatio;
float sqrt_2;

bool motor1_3Dir;
bool motor2_4Dir;

// last time we calculated motor velocity
int lastTime1;
int lastTime2;
int lastTime3;
int lastTime4;

unsigned char readDataCounter;

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

    motorToWheelRatio = WHEEL_DIAM * PI / GEAR_RATIO;
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

    signal(SIGALRM, ReadData);
    ualarm(1000, 1000); // ReadData function called every 1 ms
}

void CalculateCurPosition()
{
    int encoder1Change = 0;
    int encoder2Change = 0;
    int encoder3Change = 0;
    int encoder4Change = 0;

    // not sure if waiting for all of these to stop will take too long 
    // but we need to make sure the variables aren't being accessed by multiple threads
    while (count1Changing) {};
    count1Changing = true;
    encoder1Change = encoder1Count;
    encoder1Count = 0;
    count1Changing = false;

    while (count2Changing) {};
    count2Changing = true;
    encoder2Change = encoder2Count;
    encoder2Count = 0;
    count2Changing = false;

    while (count3Changing) {};
    count3Changing = true;
    encoder3Change = encoder3Count;
    encoder3Count = 0;
    count3Changing = false;

    while (count4Changing) {};
    count4Changing = true;
    encoder4Change = encoder4Count;
    encoder4Count = 0;
    count4Changing = false;

   // https://github.com/FTC7393/EVLib/wiki/Mecanum-Wheels

   // FL and BR wheels move robot forward and right when wheel turns forward.
   // FR and BL wheels move robot forward and left when wheels move forward.

    // average encoder changes then multiply by wheel circumference and divide by gear ratio and sqrt(2) (wheel only moves forward sqrt(2) amount of rotation)
    curPosition1 += encoder1Change * motorToWheelRatio;
    curPosition2 += encoder2Change * motorToWheelRatio;
    curPosition3 += encoder3Change * motorToWheelRatio;
    curPosition4 += encoder4Change * motorToWheelRatio;

    curPositionY += (curPosition1 + curPosition2 + curPosition3 + curPosition4)  / (NUM_OF_MOTORS * sqrt_2);
    curPositionX += (((curPosition1 + curPosition3) / (NUM_OF_MOTORS / 2)) - ((curPosition2 + curPosition4) / (NUM_OF_MOTORS / 2))) / sqrt_2; 
}

void CalculateCurVelocity()
{   
    Debug("Calculating velocities.\n");
    int tempTime = micros();

    curVelocity1 = (curPosition1 - lastPosition1) * 1000000 / (tempTime - lastTime1);
    lastTime1 = tempTime;

    tempTime = micros();
    curVelocity2 = (curPosition2 - lastPosition2) * 1000000 / (tempTime - lastTime2);
    lastTime2 = tempTime;

    tempTime = micros();
    curVelocity3 = (curPosition3 - lastPosition3) * 1000000 / (tempTime - lastTime3);
    lastTime3 = tempTime;

    tempTime = micros();
    curVelocity4 = (curPosition4 - lastPosition4) * 1000000 / (tempTime - lastTime4);
    lastTime4 = tempTime;
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
    motor1Power = (yDiff + xDiff) / max;
    //motor3Power = motor1Power; 

    motor2Power = (yDiff - xDiff) / max;
    //motor4Power = motor2Power;

    if (motor1Power >= 0)
    {
        motor1_3Dir = 1; // go forward
    }
    else
    {
        motor1_3Dir = 0; // go backward
        motor1Power = motor1Power * -1; // duty cycle values always positive
    }

    if (motor2Power >= 0)
    {
        motor2_4Dir = 1; // go forward
    }
    else
    {
        motor2_4Dir = 0; // go backward
        motor2Power = motor2Power * -1; // duty cycle values always positive
    }

    dutyCycleMotors1_3 = (motor1Power / 1) * 100;
    dutyCycleMotors2_4 = (motor2Power / 1) * 100;

    if(dutyCycleMotors1_3 > MaxDutyCycle)
    {
        dutyCycleMotors1_3 = MaxDutyCycle;
    }
    else if (dutyCycleMotors2_4 > MaxDutyCycle)
    {
        dutyCycleMotors2_4 = MaxDutyCycle;
    }
    else if(dutyCycleMotors1_3 < MinDutyCycle)
    {
        dutyCycleMotors1_3 = MinDutyCycle;
    }
    else if (dutyCycleMotors2_4 < MinDutyCycle)
    {
        dutyCycleMotors2_4 = MinDutyCycle;
    }

    motor1Power = dutyCycleMotors1_3;
    motor2Power = dutyCycleMotors2_4;
    motor3Power = dutyCycleMotors1_3;
    motor4Power = dutyCycleMotors2_4;
}

// use this to: read controller (joystick) input, 
             // calculate motor velocity,
             // read ultrasonic sensor data
void ReadData()
{
    if ((readDataCounter % 50) == 0) // every 50 ms
    {
        ReadUltrasonicSensors();
    }
    if ((readDataCounter % 20) == 0) // every 20 ms
    {
        CalculateCurVelocity();
    }
    ReadJoystickData(); // every ms

    readDataCounter++;
    if (readDataCounter > 200)
    {
        readDataCounter = 1;
    }
}
