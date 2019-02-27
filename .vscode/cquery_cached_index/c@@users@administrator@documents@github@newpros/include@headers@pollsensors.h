#ifndef pollSensors_h
#define pollSensors_h

#include "headers/filters.h"

void pollSensors(void* param);

// extern pros::ADIEncoder leftDriveSensor;
// pros::ADIEncoder rightDriveSensor (3, 4, false);
// pros::ADIGyro gyroSensor (5);
// pros::ADIDigitalIn launcherSensor(6);

extern demaFilter gyroFilter;
extern demaFilter leftDriveFilter;
extern demaFilter rightDriveFilter;
extern medianFilter accelerometer_xFilter;
extern medianFilter accelerometer_yFilter;
extern medianFilter accelerometer_zFilter;

void resetGyro();
float getRawGyro();
float getLiftSensor();
float getAccelerometerX();
float getAccelerometerY();
float getAccelerometerZ();
void resetLeftDriveSensor();
void resetRightDriveSensor();
void resetStrafeDriveSensor();
bool getLauncherSensor();
bool getFlipperSensor();

bool getAutoSensor();
bool getSideSensor();


extern const int SensorRefreshRate;


#endif
