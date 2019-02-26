#ifndef pollSensors_cpp
#define pollSensors_cpp

#include "headers/pollSensors.h"
#include "headers/filters.h"
#include "headers/timers.h"
#include "headers/motorSlew.h"
#include "headers/general.h"
#include "pros/rtos.hpp"
#include "pros/adi.hpp"
#include "headers/gyroFunctions.h"
#include "headers/accelerometer.h"
#include "pros/llemu.hpp"

#define ACCELEROMETER_X 4
#define ACCELEROMETER_Y 5
#define ACCELEROMETER_Z 6

pros::Task pollSensorsTask(pollSensors, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "pollSensorsTask");

const int SensorRefreshRate = 10;

demaFilter gyroFilter;
demaFilter leftDriveFilter;
demaFilter rightDriveFilter;
medianFilter accelerometer_xFilter;
medianFilter accelerometer_yFilter;
medianFilter accelerometer_zFilter;

 //
 // pros::ADIEncoder leftDriveSensor (6, 2, false);
 // pros::ADIEncoder rightDriveSensor (3, 4, false);
 pros::ADIGyro gyroSensor (3);
 pros::ADIDigitalIn launcherSensor(1);
 pros::ADIDigitalIn flipperSensor(2);
 pros::ADIAnalogIn lift_sensor(3);
 pros::ADIAnalogIn acc_x (ACCELEROMETER_X);
 pros::ADIAnalogIn acc_y (ACCELEROMETER_Y);
 pros::ADIAnalogIn acc_z (ACCELEROMETER_Z);


void pollSensors(void* param)
{

   // pros::ADIEncoder leftDriveSensor (6, 2, false);
   // pros::ADIEncoder rightDriveSensor (3, 4, false);
   pros::ADIGyro gyroSensor (3);
   pros::ADIAnalogIn acc_x (ACCELEROMETER_X);
   pros::ADIAnalogIn acc_y (ACCELEROMETER_Y);
   pros::ADIAnalogIn acc_z (ACCELEROMETER_Z);

	newDemaFilter(&gyroFilter);
	newDemaFilter(&leftDriveFilter);
	newDemaFilter(&rightDriveFilter);
  newMedianFilter(&accelerometer_xFilter);
  newMedianFilter(&accelerometer_yFilter);
  newMedianFilter(&accelerometer_zFilter);

  uint32_t lastRun = pros::c::millis();

	while(true)
	{
		filterDema(&gyroFilter, correctGyroValue(gyroSensor.get_value()));
		filterDema(&leftDriveFilter, motorArray[frontLeftDrive]->get_position());
		filterDema(&rightDriveFilter, motorArray[frontRightDrive]->get_position());
    // pros::lcd::print(5, "get left %f", motorArray[frontLeftDrive]->get_position());
    // pros::lcd::print(6, "get right sensor %f", motorArray[frontRightDrive]->get_position());
    // pros::lcd::print(7, "get raw gyro sensor %f", gyroSensor.get_value());
    // filterMedian(&accelerometer_xFilter, accelerometerXValue(acc_x.get_value()));
    // filterMedian(&accelerometer_yFilter, accelerometerYValue(acc_y.get_value()));
    // filterMedian(&accelerometer_zFilter, accelerometerZValue(acc_z.get_value()));

    pros::c::task_delay_until(&lastRun, SensorRefreshRate);
    lastRun = pros::c::millis();

	}
}

void resetGyro()
{
  gyroSensor.reset();
}
float getRawGyro()
{
  return gyroSensor.get_value();
}
void resetLeftDriveSensor()
{
  motorArray[frontLeftDrive]->tare_position();
}
void resetRightDriveSensor()
{
  motorArray[frontRightDrive]->tare_position();
}
bool getLauncherSensor()
{
	return launcherSensor.get_value();
}
bool getFlipperSensor()
{
  return flipperSensor.get_value();
}
float getLiftSensor()
{
	return lift_sensor.get_value();
}
float getRawAccelerometerX()
{
  return acc_x.get_value();
}
float getRawAccelerometerY()
{
  return acc_y.get_value();
}
float getRawAccelerometerZ()
{
  return acc_z.get_value();
}

#endif
