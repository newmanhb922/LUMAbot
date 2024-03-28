#include "Position.h"

extern float curPositionX;
extern float curPositionY;
extern float targetPositionX;
extern float targetPositionY;
extern float motor1Power;
extern float motor2Power;
extern float motor3Power;
extern float motor4Power;

extern volatile int encoder1Count;
extern volatile int encoder2Count;
extern volatile int encoder3Count;
extern volatile int encoder4Count;

extern volatile bool count1Changing;
extern volatile bool count2Changing;
extern volatile bool count3Changing;
extern volatile bool count4Changing;

void InitPosition()
{
    curPositionX = 0.0f;
    curPositionY = 0.0f;
    motorToWheelRatio = WHEEL_DIAM * PI / (GEAR_RATIO * sqrt(2));
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
    curPositionY += ((encoder1Change + encoder2Change + encoder3Change + encoder4Change)  / NUM_OF_MOTORS) * motorToWheelRatio;
    curPositionX += (((encoder1Change + encoder3Change) / (NUM_OF_MOTORS / 2)) - ((encoder2Change + encoder4Change) / (NUM_OF_MOTORS / 2))) * motorToWheelRatio; 
}

void CalculateMotorPowers()
{
    float yDiff = targetPositionY - curPositionY;
    float xDiff = targetPositionX - curPositionX;
    float yDiffAbs = yDiff;
    float xDiffAbs = xDiff;
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
        yDiffAbs;
    }
    // motors 1 and 3 are same and 2 and 4 are same when not rotating
    motor1Power = (yDiffAbs + xDiffAbs) / max;
    motor3Power = motor1Power; 

    motor2Power = (yDiffAbs - xDiffAbs) / max;
    motor4Power = motor2Power;
}