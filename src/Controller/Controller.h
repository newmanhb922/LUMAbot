#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <linux/joystick.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

extern short controllerXValue;
extern short controllerYValue;

/// @brief Initializes the joystick controller connection
void InitController();

/// @brief Reads an event from the joystick file
void ReadJoystickData();
#endif
