#include "MotorControl.h"

// these variables store the encoder counts for each motor
volatile int encoder1Count;
volatile int encoder2Count;
volatile int encoder3Count;
volatile int encoder4Count;

volatile bool count1Changing;
volatile bool count2Changing;
volatile bool count3Changing;
volatile bool count4Changing;

// hold the last value (1 or 0) of the encoder pins
volatile unsigned char last1A;
volatile unsigned char last1B;
volatile unsigned char last2A;
volatile unsigned char last2B;
volatile unsigned char last3A;
volatile unsigned char last3B;
volatile unsigned char last4A;
volatile unsigned char last4B;

/// @brief Initialize encoder pins and variables and set up hardware interrupts
void SetupEncoders();

// Interrupt Service routines for each Encoder
void EncoderISR1();
void EncoderISR2();
void EncoderISR3();
void EncoderISR4();

/// @brief Calculate the encoder change
/// @param encoderNum number of the encoder we are working with (1 - 4)
/// @param lastA last value of the encoder channel A
/// @param lastB last value of the encoder channel B
/// @param curA current value of the encoder channel A
/// @param curB current value of the encoder channel B
/// @return the encoder change, will be 1 for motor moving forward, -1 for motor moving backwards
unsigned char CalculateEncoderChange(unsigned char encoderNum, unsigned char lastA, unsigned char lastB, unsigned char curA, unsigned char curB);

/// @brief Updates the lastxA and lastxB variables for the specified encoder
/// @param encoderNum number of the encoder we are working with (1 - 4)
/// @param curA current value of the encoder channel A
/// @param curB current value of the encoder channel B
void SetLastVars(unsigned char encoderNum, unsigned char curA, unsigned char curB);

void SetupMotors()
{
    int returnVal = wiringPiSetup();
    if (returnVal == 0)
    {
        printf("wiringPiSetup success\n");
    }
    else 
    {
        printf("wiringPiSetup failed\n");
    }
    pinMode(MOTOR_1_DIR, OUTPUT);
    pinMode(MOTOR_2_DIR, OUTPUT);
    pinMode(MOTOR_3_DIR, OUTPUT);
    pinMode(MOTOR_4_DIR, OUTPUT);

    SetupEncoders();
}

void SetMotorDir(int motorNum, bool forward)
{
    int motorPin = 0;
    switch (motorNum)
    {
        case 1:
            motorPin = MOTOR_1_DIR;
            break;
            case 2:
            motorPin = MOTOR_2_DIR;
            break;
        case 3:
            motorPin = MOTOR_3_DIR;
            break;
        case 4:
            motorPin = MOTOR_4_DIR;
            break;
        default:
            motorPin = -1;
            break;
    }
    digitalWrite(motorPin, forward);
}

void SetupEncoders()
{    
    // set Encoder pins as inputs
    pinMode(ENCODER_1A, INPUT);
    pinMode(ENCODER_1B, INPUT);
    pinMode(ENCODER_2A, INPUT);
    pinMode(ENCODER_2B, INPUT);
    pinMode(ENCODER_3A, INPUT);
    pinMode(ENCODER_3B, INPUT);
    pinMode(ENCODER_4A, INPUT);
    pinMode(ENCODER_4B, INPUT);

    // initialize encoder variables
    last1A = 0;
    last1B = 0;
    last2A = 0;
    last2B = 0;
    last3A = 0;
    last3B = 0;
    last4A = 0;
    last4B = 0;

    encoder1Count = 0;
    encoder2Count = 0;
    encoder3Count = 0;
    encoder4Count = 0;

    count1Changing = false;
    count2Changing = false;
    count3Changing = false;
    count4Changing = false;

    // set up Interrupts for encoders. 
    // receive an interrupt on a rising or falling edge of the A and B channels of each encoder
    // However, both A and B channels will call the same interrupt function
    wiringPiISR(ENCODER_1A, INT_EDGE_BOTH, &EncoderISR1);
    wiringPiISR(ENCODER_1B, INT_EDGE_BOTH, &EncoderISR1);
    wiringPiISR(ENCODER_2A, INT_EDGE_BOTH, &EncoderISR2);
    wiringPiISR(ENCODER_2B, INT_EDGE_BOTH, &EncoderISR2);
    wiringPiISR(ENCODER_3A, INT_EDGE_BOTH, &EncoderISR3);
    wiringPiISR(ENCODER_3B, INT_EDGE_BOTH, &EncoderISR3);
    wiringPiISR(ENCODER_4A, INT_EDGE_BOTH, &EncoderISR4);
    wiringPiISR(ENCODER_4B, INT_EDGE_BOTH, &EncoderISR4);
}

// in these ISR's, we want to read the encoder A and B channels as soon as the ISR is fired
// however, we don't want to update the count variable if another thread (that was maybe called from the other channel) is accessing it
// so first read the encoder A and B channels, then wait until the encoder count is done being changed
// then notify others that we are now changing the encoder count
// then calculate the encoder change and update the encoder count
// then notify others we are done changing the encoder count so that they can change it
void EncoderISR1()
{
    unsigned char curA = digitalRead(ENCODER_1A);
    unsigned char curB = digitalRead(ENCODER_1B);
    while (count1Changing); // wait for another encoder 1 thread to finish
    count1Changing = true;
    encoder1Count = encoder1Count + CalculateEncoderChange(1, last1A, last1B, curA, curB);
    count1Changing = false; // we are done changing count, let other threads change it
}

void EncoderISR2()
{
    unsigned char curA = digitalRead(ENCODER_2A);
    unsigned char curB = digitalRead(ENCODER_2B);
    while (count2Changing); // wait for another encoder 2 thread to finish
    count2Changing = true;
    encoder2Count = encoder2Count + CalculateEncoderChange(2, last2A, last2B, curA, curB);
    count2Changing = false; // we are done changing count, let other threads change it
}

void EncoderISR3()
{
    unsigned char curA = digitalRead(ENCODER_3A);
    unsigned char curB = digitalRead(ENCODER_3B);
    while (count3Changing); // wait for another encoder 3 thread to finish
    count3Changing = true;
    encoder3Count = encoder3Count + CalculateEncoderChange(3, last3A, last3B, curA, curB);
    count3Changing = false; // we are done changing count, let other threads change it
}

void EncoderISR4()
{
    unsigned char curA = digitalRead(ENCODER_4A);
    unsigned char curB = digitalRead(ENCODER_4B);
    while (count4Changing); // wait for another encoder 4 thread to finish
    count4Changing = true;
    encoder4Count = encoder4Count + CalculateEncoderChange(4, last4A, last4B, curA, curB);
    count4Changing = false; // we are done changing count, let other threads change it
}

unsigned char CalculateEncoderChange(unsigned char encoderNum, unsigned char lastA, unsigned char lastB, unsigned char curA, unsigned char curB)
{
    char countChange = 0;

    // calculate whether to increment or decrement count (countChange will be 1 or -1)

    if (lastA != lastB) // A and B were different
    { 
        if (lastB != curB) // B changed so we count up
        {
            countChange = 1;
        }
        else if (lastA != curA) // A changed so we count down
        {
            countChange = -1;
        }
        else // not sure if we need this, theoretically impossible to get here
        {
           // Debug("Error in CalculateEncoderCount, nothing changed\n");
        }
    }
    else // A and B were the same
    {
        if (lastA != curA) // A changed so we count up
        {
            countChange = 1;
        }
        else if (lastB != curB) // B changed so we count down
        {
            countChange = -1;
        }
        else // not sure if we need this, theoretically impossible to get here
        {
            //Debug("Error in CalculateEncoderCount, nothing changed\n");
        }
    }

    // update the lastxA and lastxB variables based on which encoder we are working with
    SetLastVars(encoderNum, curA, curB); 

    return countChange;
}

void SetLastVars(unsigned char encoderNum, unsigned char curA, unsigned char curB)
{
    switch (encoderNum)
    {
        case 1:
            last1A = curA;
            last1B = curB;
            break;
        case 2:
            last2A = curA;
            last2B = curB;
            break;
        case 3:
            last3A = curA;
            last3B = curB;
            break;
        case 4:
            last4A = curA;
            last4B = curB;
            break;
        default:
          //  Debug("Error in SetLastVars, encoderNum should only be 1-4\n");
            break;
    }
}
