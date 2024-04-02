#include "Ultrasonic.h"

int sensorCounter;

// distance from sensor to object in inches
volatile float sensor1Val; //front
volatile float sensor2Val; //right
volatile float sensor3Val; //back
volatile float sensor4Val; //left
// extern volatile float sensor5Val;
// extern volatile float sensor6Val;
// extern volatile float sensor7Val;
// extern volatile float sensor8Val;

/// @brief Samples the sensor value
void SampleSensor();

/// @brief Reads the sensor distance
/// @param sensorTrigPin the gpio pin on the raspberry pi that is wired to the trigger pin of the sensor
/// @param oldSensorVal the previously read sensor value
/// @return returns the distance in inches
float ReadSensorDistance(int sensorTrigPin, float oldSensorVal);

void UltrasonicInit()
{
    wiringPiSetup();
    pinMode(ECHO_PIN, INPUT);
    pinMode(SENSOR_1_TRIG, OUTPUT);
    pinMode(SENSOR_2_TRIG, OUTPUT);
    pinMode(SENSOR_3_TRIG, OUTPUT);
    pinMode(SENSOR_4_TRIG, OUTPUT);
    // pinMode(SENSOR_5_TRIG, OUTPUT);
    // pinMode(SENSOR_6_TRIG, OUTPUT);
    // pinMode(SENSOR_7_TRIG, OUTPUT);
    // pinMode(SENSOR_8_TRIG, OUTPUT);
    
    sensorCounter = 1;
    sensor1Val = 0;
    sensor2Val = 0;
    sensor3Val = 0;
    sensor4Val = 0;
    // sensor5Val = 0;
    // sensor6Val = 0;
    // sensor7Val = 0;
    // sensor8Val = 0;
}

void SampleSensor()
{
    switch (sensorCounter)
    {
        case 1:
            Debug("Reading ultrasonic sensor 1.\n");
            sensor1Val = ReadSensorDistance(SENSOR_1_TRIG, sensor1Val);
            break;
        case 2:
            Debug("Reading ultrasonic sensor 2.\n");
            sensor2Val = ReadSensorDistance(SENSOR_2_TRIG, sensor2Val);
            break;
        case 3:
            Debug("Reading ultrasonic sensor 3.\n");
            sensor3Val = ReadSensorDistance(SENSOR_3_TRIG, sensor3Val);
            break;
        case 4:
            Debug("Reading ultrasonic sensor 4.\n");
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
    unsigned int timeout = 10000; // 10 ms. if we reduce this to 10,000 that should cut off measurement at around 5 or 6 feet max
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
    return (distanceCm / CM_PER_IN);
}

void ReadUltrasonicSensors()
{
    if (sensorCounter > 0 && sensorCounter < NUM_OF_SENSORS + 1)
    {
        SampleSensor();
        sensorCounter++;
    }
    if (sensorCounter < 1 || sensorCounter > NUM_OF_SENSORS)
    {
        sensorCounter = 1;
    }
}
