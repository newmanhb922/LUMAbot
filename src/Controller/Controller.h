#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <linux/joystick.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <wiringPi.h>

extern short controllerXValue;
extern short controllerYValue;
extern short controllerSpin;

extern bool controllerConnected; // whether the controller is connected and ready to use.

/// @brief Initializes the joystick controller connection
void InitController();

/// @brief Reads an event from the joystick file
void ReadJoystickData();
#endif
