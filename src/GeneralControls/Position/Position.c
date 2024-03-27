#include "Position.h"

extern float positionX;
extern float positionY;

void InitPosition()
{
    positionX = 0.0f;
    positionY = 0.0f;
    motorToWheelRatio = WHEEL_DIAM * PI / (GEAR_RATIO * sqrt(2));
}

void CalculatePosition()
{
    int encoder1Change = encoder1Count;
    int encoder2Change = encoder2Count;
    int encoder3Change = encoder3Count;
    int encoder4Change = encoder4Count;

    // not sure if waiting for all of these to stop will take too long 
    // but we need to make sure the variables aren't being accessed by multiple threads
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

   // https://github.com/FTC7393/EVLib/wiki/Mecanum-Wheels

   // FL and BR wheels move robot forward and right when wheel turns forward.
   // FR and BL wheels move robot forward and left when wheels move forward.

    // average encoder changes then multiply by wheel circumference and divide by gear ratio and sqrt(2) (wheel only moves forward sqrt(2) amount of rotation)
    positionY += ((encoder1Change + encoder2Change + encoder3Change + encoder4Change)  / NUM_OF_MOTORS) * motorToWheelRatio;
    positionX += (((encoder1Change + encoder3Change) / (NUM_OF_MOTORS / 2)) - ((encoder2Change + encoder4Change) / (NUM_OF_MOTORS / 2))) * motorToWheelRatio; 
}