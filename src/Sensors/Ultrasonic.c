#include "Ultrasonic.h"

/// @brief interrupt function to be triggered on timer match
void TimerInterrupt();

/// @brief Samples the sensor value
void SampleSensor();

/// @brief Reads the sensor distance
/// @param sensorTrigPin the gpio pin on the raspberry pi that is wired to the trigger pin of the sensor
/// @return returns the distance in cm
double ReadSensorDistance(int sensorTrigPin);

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
            sensor1Val = ReadSensorDistance(SENSOR_1_TRIG);
            break;
        case 2:
            sensor2Val = ReadSensorDistance(SENSOR_2_TRIG);
            break;
        case 3:
            sensor3Val = ReadSensorDistance(SENSOR_3_TRIG);
            break;
        case 4:
            sensor4Val = ReadSensorDistance(SENSOR_4_TRIG);
            break;
        case 5:
            sensor5Val = ReadSensorDistance(SENSOR_5_TRIG);
            break;
        case 6:
            sensor6Val = ReadSensorDistance(SENSOR_6_TRIG);
            break;
        case 7:
            sensor7Val = ReadSensorDistance(SENSOR_7_TRIG);
            break;
        case 8:
            sensor8Val = ReadSensorDistance(SENSOR_8_TRIG);
            break;
    }
}

double ReadSensorDistance(int sensorTrigPin)
{
    unsigned int startUSec = 0;
    unsigned int endUSec = 0;
    double distanceCm = 0;
    unsigned int timeout = 1000000; // 1 second. if we reduce this to 10,000 that should cut off measurement at around 5 or 6 feet max
    const double SPEED_OF_SOUND = 343.8; // approximate speed of sound in 69.8 degree F air

    digitalWrite(sensorTrigPin, HIGH); // pulse trig pin to tell sensor we want to read
    delayMicroseconds(10);
    digitalWrite(sensorTrigPin, LOW);

    while (digitalRead(ECHO_PIN) == LOW); // wait until echo goes high
    startUSec = micros(); // record start time
    while (digitalRead(ECHO_PIN) == HIGH && (micros() - startUSec) < timeout); // wait until echo goes low.
    // can add a timeout here as well so that if something is really far away we don't pay care so we don't want to waste time waiting for the signal to come back
    endUSec = micros(); // record end time
    // (100 (cm / meter) * (elapsed time (microseconds) / 1000000 (microseconds / second)) * speed of sound (meters / second)) / 2.
    // we divide by two because the elapsed time is the time to travel to object and back to sensor so it travelled double the distance that we want.
    distanceCm = (100.0 * ((endUSec - startUSec) / 1000000.0) * SPEED_OF_SOUND) / 2.0;
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
        sensorCounter = 0;
    }
}
