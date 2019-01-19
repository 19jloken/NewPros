#ifndef general_cpp
#define general_cpp

#include "pros/rtos.hpp"
#include "pros/misc.hpp"

const int frontLeftDrive = 0; // 1 port 2
const int frontRightDrive = 1; // 2 port 3
const int backLeftDrive = 2; // 3 port 4
const int backRightDrive = 3; // 4 port 5
const int flipperMotor = 4; // 5 port
const int intakeMotor = 5; // 6 port 6
const int shooter = 6; // 7 port 1
const int liftMotor = 7; // 8 port 8


bool clearGyroBeforeAuton = true;

int autonomousMode = 1;
bool autonomousSelected = true;

#endif
