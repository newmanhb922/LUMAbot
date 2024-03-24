#include "Ultrasonic.h"

extern volatile float sensor1Val;
extern volatile float sensor2Val;
extern volatile float sensor3Val;
extern volatile float sensor4Val;
extern volatile float sensor5Val;
extern volatile float sensor6Val;
extern volatile float sensor7Val;
extern volatile float sensor8Val;

/// @brief interrupt function to be triggered on timer match
void TimerInterrupt();

/// @brief Samples the sensor value
void SampleSensor();

/// @brief Reads the sensor distance
/// @param sensorTrigPin the gpio pin on the raspberry pi that is wired to the trigger pin of the sensor
/// @param oldSensorVal the previously read sensor value
/// @return returns the distance in cm
float ReadSensorDistance(int sensorTrigPin, float oldSensorVal);

void UltrasonicInit()
{
    wiringPiSetup();
    pinMode(ECHO_PIN, INPUT);
    pinMode(SENSOR_1_TRIG, OUTPUT);
    pinMode(SENSOR_2_TRIG, OUTPUT);
    pinMode(SENSOR_3_TRIG, OUTPUT);
    pinMode(SENSOR_4_TRIG, OUTPUT);
    pinMode(SENSOR_5_TRIG, OUTPUT);
    pinMode(SENSOR_6_TRIG, OUTPUT);
    pinMode(SENSOR_7_TRIG, OUTPUT);
    pinMode(SENSOR_8_TRIG, OUTPUT);
    
    sensorCounter = 0;
    sensor1Val = 0;
    sensor2Val = 0;
    sensor3Val = 0;
    sensor4Val = 0;
    sensor5Val = 0;
    sensor6Val = 0;
    sensor7Val = 0;
    sensor8Val = 0;
}

void StartSampling(int microSeconds)
{
    signal(SIGALRM, TimerInterrupt); // set TimerInterrupt as callback
    ualarm(microSeconds, microSeconds); // set alarm interval to number of microseconds
    sensorCounter = 1;
}

void SampleSensor()
{
    switch (sensorCounter)
    {
        case 1:
            sensor1Val = ReadSensorDistance(SENSOR_1_TRIG, sensor1Val);
            break;
        case 2:
            sensor2Val = ReadSensorDistance(SENSOR_2_TRIG, sensor2Val);
            break;
        case 3:
            sensor3Val = ReadSensorDistance(SENSOR_3_TRIG, sensor3Val);
            break;
        case 4:
            sensor4Val = ReadSensorDistance(SENSOR_4_TRIG, sensor4Val);
            break;
        // we may only have 4 sensors now?
        case 5:
           // sensor5Val = ReadSensorDistance(SENSOR_5_TRIG, sensor5Val);
            break;
        case 6:
           // sensor6Val = ReadSensorDistance(SENSOR_6_TRIG, sensor6Val);
            break;
        case 7:
           // sensor7Val = ReadSensorDistance(SENSOR_7_TRIG, sensor7Val);
            break;
        case 8:
           // sensor8Val = ReadSensorDistance(SENSOR_8_TRIG, sensor8Val);
            break;
    }
}

float ReadSensorDistance(int sensorTrigPin, float oldSensorVal)
{
    unsigned int startUSec = 0;
    unsigned int endUSec = 0;
    float distanceCm = oldSensorVal;
    unsigned int timeout = 10000; // 1 second. if we reduce this to 10,000 that should cut off measurement at around 5 or 6 feet max
    char debugMsg[100];
    
    digitalWrite(sensorTrigPin, HIGH); // pulse trig pin to tell sensor we want to read
    delayMicroseconds(10);
    digitalWrite(sensorTrigPin, LOW);
    startUSec = micros();
    while (digitalRead(ECHO_PIN) == LOW && (micros() - startUSec) < timeout); // wait until echo goes high
    if (micros() - startUSec >= timeout)
    { // timeout was reason that the while ended, echo never went high
        sprintf(debugMsg, "Echo pin never went high, error with sensor trigger pin %d\n", sensorTrigPin);
        //Debug(debugMsg);
        return distanceCm; // return old value
    }
    startUSec = micros(); // record start time
    while (digitalRead(ECHO_PIN) == HIGH && (micros() - startUSec) < timeout); // wait until echo goes low.
    // can add a timeout here as well so that if something is really far away we don't pay care so we don't want to waste time waiting for the signal to come back
    endUSec = micros(); // record end time
    if (micros() - startUSec >= timeout)
    { // timeout was reason that the while ended, echo never went low
        sprintf(debugMsg, "Echo pin never went low, object at max distance for sensor with trig pin %d\n", sensorTrigPin);
        //Debug(debugMsg);
    }
    // (100 (cm / meter) * (elapsed time (microseconds) / 1000000 (microseconds / second)) * speed of sound (meters / second)) / 2.
    // we divide by two because the elapsed time is the time to travel to object and back to sensor so it travelled double the distance that we want.
    distanceCm = (100.0f * ((endUSec - startUSec) / 1000000.0f) * SPEED_OF_SOUND) / 2.0;
    return distanceCm;
}

void TimerInterrupt()
{
    if (sensorCounter > 0 && sensorCounter < 9)
    {
        SampleSensor();
        sensorCounter++;
    }
    if (sensorCounter < 1 || sensorCounter > 8)
    {
        sensorCounter = 1;
    }
}
