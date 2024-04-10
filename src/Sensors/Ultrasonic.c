#include "Ultrasonic.h"

// distance from sensor to object in inches
volatile float sensor1Val; //front
volatile float sensor2Val; //right
volatile float sensor3Val; //back
volatile float sensor4Val; //left
// extern volatile float sensor5Val;
// extern volatile float sensor6Val;
// extern volatile float sensor7Val;
// extern volatile float sensor8Val;

float readTimeout; // maximum time that we wait to receive back echo

/// @brief Samples the sensor value
/// @param sensorNum the sensor number to sample
void SampleSensor(int sensorNum);

/// @brief Reads the sensor distance
/// @param sensorTrigPin the gpio pin on the raspberry pi that is wired to the trigger pin of the sensor (wiringPi version)
/// @param echoPin the gpio pin on the raspberry pi that is wired to echo (wiringPi version)
/// @param oldSensorVal the previously read sensor value
/// @return returns the distance in inches
float ReadSensorDistance(int sensorTrigPin, int echoPin, float oldSensorVal);

// functions to be called by the interrupt on pin change
void Echo1Changed();
void Echo2Changed();
void Echo3Changed();
void Echo4Changed();

/// @brief Calculates the objects distance in cm
/// @param startTime timestamp when echo pin went high
/// @param endTime  timestamp when echo pin went low
/// @return returns the objects distance in inches
float CalculateObjectDistance(unsigned int startTime, unsigned int endTime);

/// @brief Writes to the trigger pin to signal we want the sensor to read the distance
/// @param triggerPin pin number of the trigger pin
void TriggerTheRead(int triggerPin);

void UltrasonicInit()
{
    wiringPiSetup();
    pinMode(SENSOR_1_ECHO, INPUT);
    pinMode(SENSOR_2_ECHO, INPUT);
    pinMode(SENSOR_3_ECHO, INPUT);
    pinMode(SENSOR_4_ECHO, INPUT);
    pinMode(SENSOR_1_TRIG, OUTPUT);
    pinMode(SENSOR_2_TRIG, OUTPUT);
    pinMode(SENSOR_3_TRIG, OUTPUT);
    pinMode(SENSOR_4_TRIG, OUTPUT);
    
    sensor1Val = 20;
    sensor2Val = 20;
    sensor3Val = 20;
    sensor4Val = 20;
    
    readTimeout = MAX_DISTANCE * CM_PER_IN * 2.0f / (100.0f * SPEED_OF_SOUND / 1000000.0f);

    // set up interrupts for ultrasonic sensor echo pins.
    // leaving commented out for now (4/10), test other changes I made then I'll uncomment and test the sensors
    // wiringPiISR(SENSOR_1_ECHO, INT_EDGE_BOTH, &Echo1Changed);
    // wiringPiISR(SENSOR_2_ECHO, INT_EDGE_BOTH, &Echo2Changed);
    // wiringPiISR(SENSOR_3_ECHO, INT_EDGE_BOTH, &Echo3Changed);
    // wiringPiISR(SENSOR_4_ECHO, INT_EDGE_BOTH, &Echo4Changed);
}

void SampleSensor(int sensorNum)
{
    switch (sensorNum)
    {
        case 1:
//            Debug("Reading ultrasonic sensor 1.\n");
           // sensor1Val = ReadSensorDistance(SENSOR_1_TRIG, SENSOR_1_ECHO, sensor1Val);
            TriggerTheRead(SENSOR_1_TRIG);
            break;
        case 2:
  //          Debug("Reading ultrasonic sensor 2.\n");
           // sensor2Val = ReadSensorDistance(SENSOR_2_TRIG, SENSOR_2_ECHO, sensor2Val);
            TriggerTheRead(SENSOR_2_TRIG);
            break;
        case 3:
    //        Debug("Reading ultrasonic sensor 3.\n");
            //sensor3Val = ReadSensorDistance(SENSOR_3_TRIG, SENSOR_3_ECHO, sensor3Val);
            TriggerTheRead(SENSOR_3_TRIG);
            break;
        case 4:
      //      Debug("Reading ultrasonic sensor 4.\n");
            //sensor4Val = ReadSensorDistance(SENSOR_4_TRIG, SENSOR_4_ECHO, sensor4Val);
            TriggerTheRead(SENSOR_4_TRIG);
            break;
    }
}

// float ReadSensorDistance(int sensorTrigPin, int echoPin, float oldSensorVal)
// {
//     unsigned int startUSec = 0;
//     unsigned int endUSec = 0;
//     float distanceCm = 0;
//     char debugMsg[100];
    
//     digitalWrite(sensorTrigPin, HIGH); // pulse trig pin to tell sensor we want to read
//     delayMicroseconds(10);
//     digitalWrite(sensorTrigPin, LOW);
//     startUSec = micros();
//     while (digitalRead(echoPin) == LOW && (micros() - startUSec) < readTimeout); // wait until echo goes high
//     if (micros() - startUSec >= readTimeout)
//     { // timeout was reason that the while ended, echo never went high
//         sprintf(debugMsg, "Echo pin never went high, error with sensor trigger pin %d\n", sensorTrigPin);
//         Debug(debugMsg);
//      	//printf(debugMsg);
// 	   return oldSensorVal; // return old value
//     }
//     startUSec = micros(); // record start time
//     while (digitalRead(echoPin) == HIGH && (micros() - startUSec) < readTimeout); // wait until echo goes low.
//     // can add a timeout here as well so that if something is really far away we don't pay care so we don't want to waste time waiting for the signal to come back
//     endUSec = micros(); // record end time
//     if (micros() - startUSec >= readTimeout)
//     { // timeout was reason that the while ended, echo never went low
// 	sprintf(debugMsg, "Echo pin never went low, object at max distance for sensor with trig pin %d\n", sensorTrigPin);
//         Debug(debugMsg);
// 	//printf(debugMsg);
//     }
//     // (100 (cm / meter) * (elapsed time (microseconds) / 1000000 (microseconds / second)) * speed of sound (meters / second)) / 2.
//     // we divide by two because the elapsed time is the time to travel to object and back to sensor so it travelled double the distance that we want.
//     distanceCm = (100.0f * ((endUSec - startUSec) / 1000000.0f) * SPEED_OF_SOUND) / 2.0;
//     return (distanceCm / CM_PER_IN);
// }

void ReadUltrasonicSensors()
{
    static sensorNum = 1;

    if (sensorNum <= NUM_OF_SENSORS)
    {
        SampleSensor(sensorNum);
        sensorNum++;
    }
    if (sensorNum > NUM_OF_SENSORS)
    {
        sensorNum = 1;
    }
}

void Echo1Changed()
{
    static unsigned int startTime = 0;
    if (digitalRead(SENSOR_1_ECHO))
    { // echo went high, record start time
        startTime = micros();
    }
    else
    { // echo went low, get end time and do calculation
        sensor1Val = CalculateObjectDistance(startTime, micros());
    }
}

void Echo2Changed()
{
    static unsigned int startTime = 0;
    if (digitalRead(SENSOR_2_ECHO))
    { // echo went high, record start time
        startTime = micros();
    }
    else
    { // echo went low, get end time and do calculation
        sensor2Val = CalculateObjectDistance(startTime, micros());
    }
}

void Echo3Changed()
{
    static unsigned int startTime = 0;
    if (digitalRead(SENSOR_3_ECHO))
    { // echo went high, record start time
        startTime = micros();
    }
    else
    { // echo went low, get end time and do calculation
        sensor3Val = CalculateObjectDistance(startTime, micros());
    }
}

void Echo4Changed()
{
    static unsigned int startTime = 0;
    if (digitalRead(SENSOR_4_ECHO))
    { // echo went high, record start time
        startTime = micros();
    }
    else
    { // echo went low, get end time and do calculation
        sensor4Val = CalculateObjectDistance(startTime, micros());
    }
}

float CalculateObjectDistance(unsigned int startTime, unsigned int endTime)
{
    // (100 (cm / meter) * (elapsed time (microseconds) / 1000000 (microseconds / second)) * speed of sound (meters / second)) / 2.
    // we divide by two because the elapsed time is the time to travel to object and back to sensor so it really travelled double the distance we want
    return ((100.0f * ((startTime - endTime) / 1000000.0f) * SPEED_OF_SOUND) / 2.0) / CM_PER_IN;
}

void TriggerTheRead(int triggerPin)
{
    digitalWrite(triggerPin, HIGH); // pulse trig pin to tell sensor we want to read
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
}