#ifndef robotFunction_cpp
#define robotFunction_cpp

#include "headers/robotFunction.h"
#include <cmath>
#include "headers/mathFunctions.h"
#include "headers/motorSlew.h"
#include "headers/pidController.h"
#include "headers/liftController.h"
#include "headers/gyroFunctions.h"
// #include "headers/accelerometer.h"
#include "headers/filters.h"
#include "headers/pollSensors.h"
#include "headers/thresholds.h"
#include "headers/timers.h"
#include "headers/general.h"
#include "pros/rtos.hpp"
#include "pros/llemu.hpp"

pros::Task robotFunctionTask(robotFunction, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "robotFunctionTask");


int instructions[300];
int acceleration[500];
int commandReadPos = 0;
int commandWritePos = 0;
const int goToStart = -2;
bool resetRF = false;

void resetRobotFunction()
{
	commandReadPos = 0;
	commandWritePos = 0;
	int x = 0;
	while(x < 300)
	{
		instructions[x] = 0;
		x++;
	}
	resetRF = true;
}

float getLeftDriveSensor()
{
	return motorArray[frontLeftDrive]->get_position();
}

float getRightDriveSensor()
{
	return motorArray[frontRightDrive]->get_position();
}

float getIntakeSensor()
{
	return motorArray[intakeMotor]->get_position();
}

float getGyroSensor()
{
	return getDema(&gyroFilter);
}

float getAccelerometerX()
{
	return getMedian(&accelerometer_xFilter);
}

float getAccelerometerY()
{
	return getMedian(&accelerometer_yFilter);
}

float getAccelerometerZ()
{
	return getMedian(&accelerometer_zFilter);
}

bool isLauncherLoaded()
{
	return getLauncherSensor();
}

bool isFlipperDown()
{
	return getFlipperSensor();
}

void moveLift(int speed)
{
	setMotor(liftMotor, speed);
}

void moveIntake(int speed)
{
	setMotor(intakeMotor, speed);
}

void moveFlipper(int speed)
{
	setMotor(flipperMotor, speed);
}

void moveDrive(int left, int right, int strafe)
{
	// pros::lcd::print(3, "get left %d", left);
	// pros::lcd::print(4, "get right %d", right);
	setMotor(frontLeftDrive, left + (64 * strafe));
	setMotor(frontRightDrive, right - (64 * strafe));
	setMotor(backLeftDrive, left - (64 * strafe));
	setMotor(backRightDrive, right + (64 * strafe));
}

void moveLauncher(int speed)
{
	setMotor(shooter, speed);
}

int invertPotValue(int potValue)
{
	potValue = 4095-potValue;
	return potValue;
}

void addCommand(int a , int b , int c , int dd , int e , int f , int g , int h , int ii , int j , int k , int l)
{
	bool added = false;
	bool shouldAdd = true;
	while(!added)
	{
		shouldAdd = true;
		int x = 1;
		while(x <= 12)
		{
			if((commandWritePos+x) == commandReadPos)
			{
				shouldAdd = false;
			}
			x++;
		}
		if(commandWritePos+x >= 299)
		{
			if(shouldAdd)
			{
				instructions[commandWritePos] = goToStart;
				if(commandReadPos != 0)
				commandWritePos = 0;

				shouldAdd = false;
			}
		}
		if(shouldAdd)
		{
			instructions[commandWritePos] = a;
			instructions[commandWritePos+1] = b;
			instructions[commandWritePos+2] = c;
			instructions[commandWritePos+3] = dd;
			instructions[commandWritePos+4] = e;
			instructions[commandWritePos+5] = f;
			instructions[commandWritePos+6] = g;
			instructions[commandWritePos+7] = h;
			instructions[commandWritePos+8] = ii;
			instructions[commandWritePos+9] = j;
			instructions[commandWritePos+10] = k;
			instructions[commandWritePos+11] = l;
			commandWritePos += 12;
			added = true;
		}
	}
}

PIDController drivePID;
PIDController leftDrivePID;
PIDController rightDrivePID;
PIDController gyroPID;
PIDController straightGyroPID;

timer drivePIDTimer;
timer liftPIDTimer;
timer driveTimer;
timer liftTimer;
timer intakeTimer;
timer launcherTimer;
timer pauseTimer;
timer rfLauncherTimer;
timer accelerationTimer;
bool launcherShooting = false;

void robotFunction(void* param)
{
	disableSlew(0);
	disableSlew(1);
	disableSlew(2);
	disableSlew(3);
	disableSlew(4);
	disableSlew(5);
	disableSlew(6);
	disableSlew(7);

	instructions[commandWritePos] = -1;
	commandReadPos = commandWritePos;
	uint32_t lastRun = pros::c::millis();

	// Define local variables
	float leftSpeed = 0;// left drive speed
	float rightSpeed = 0;// right drive speed
	int chassisDirection = 0;
	float chassisSpeed = 0;
	float chassisDistance = 0;
	float maxDriveTime = 0;
	int largestDriveInput = 127;

	float liftSpeed = 0;
	float liftPosition = -1;
	int liftDirection = 0;
	float maxLiftTime = 0;

	float flipperPosition = -1;
	float flipperSpeed = 0;

	int intakeTarget = 0;
	float maxIntakeTime = 0;

	bool launcherShooting = false;
	float maxLauncherTime = 0;

	float maxPauseTime = 0;

	float heading = 0;
	bool driveDone = true;// the drive is not done
	bool liftDone = true;// the main lift is not done
	bool intakeDone = true;
	bool launcherDone = true;
	bool finished = false;// robotFunction is not finished


	holdingController liftHolder;
	newLiftControl(&(liftHolder), .2 ,15, 1, 100, liftUpper, liftLower, 50, 100, false);

	PIDController drivePID;
	PIDController leftDrivePID;
	PIDController rightDrivePID;
	PIDController gyroPID;
	PIDController straightGyroPID;

	initializePID(&leftDrivePID, .11, .2, .0, 0, 254, 0, 635);
	initializePID(&rightDrivePID, .11, .2, .0, 0, 254, 0, 635);
	initializePID(&drivePID, .13, .1, .001, 0, 400, 0, 635);
	initializePID(&gyroPID, .1, .025, .1, 0, 800, 0, 300);
	// initializePID(&straightGyroPID, .08, .01, .0, 0, 1000, 0, 500);
	initializePID(&straightGyroPID, .001, .0, .0, 0, 1000, 0, 500);



	initializeTimer(&drivePIDTimer);
	initializeTimer(&liftPIDTimer);
	initializeTimer(&driveTimer);
	initializeTimer(&liftTimer);
	initializeTimer(&intakeTimer);
	initializeTimer(&pauseTimer);
	initializeTimer(&launcherTimer);
	initializeTimer(&rfLauncherTimer);
	initializeTimer(&accelerationTimer);

	while(true)
	{
		if(!driveDone)// if the drive is not done
		{
			if(chassisDirection == driveStraight	)// if the robot should drive straight
			{
				setPIDTarget(&rightDrivePID, chassisDistance);
				setPIDTarget(&leftDrivePID, chassisDistance);
				if ((currentTime(&accelerationTimer) < 500) && ((fabs(getRightDriveSensor() - chassisDistance) >= driveThreshold) || (fabs(getLeftDriveSensor() - chassisDistance) >= driveThreshold)))
				{
					if (abs(acceleration[currentTime(&accelerationTimer)]) < fabs(calculatePID(&leftDrivePID, getLeftDriveSensor())))
					leftSpeed = acceleration[currentTime(&accelerationTimer)] * sgn(calculatePID(&leftDrivePID, getLeftDriveSensor()));
					else
					leftSpeed = calculatePID(&leftDrivePID, getLeftDriveSensor());
					if (abs(acceleration[currentTime(&accelerationTimer)]) < fabs(calculatePID(&rightDrivePID, getRightDriveSensor())))
					rightSpeed = acceleration[currentTime(&accelerationTimer)] * sgn(calculatePID(&rightDrivePID, getRightDriveSensor()));
					else
					rightSpeed = calculatePID(&rightDrivePID, getRightDriveSensor());
				}
				else
				{
					leftSpeed = calculatePID(&leftDrivePID, getLeftDriveSensor());
					rightSpeed = calculatePID(&rightDrivePID, getRightDriveSensor());
				}

				if(fabs(getRightDriveSensor()) - fabs(getLeftDriveSensor()) > 200)
				{

					if (fabs(getRightDriveSensor()) > fabs(getLeftDriveSensor()))// if the right drive has travelled farther than the left drive
					{
						resetPID(&drivePID);
						setPIDTarget(&drivePID, getLeftDriveSensor());
						rightSpeed = rightSpeed - fabs(calculatePID(&drivePID, getRightDriveSensor()));
					}
					else if (fabs(getLeftDriveSensor()) > fabs(getRightDriveSensor()))// if the left drive has travelled farther than the left drive
					{
						resetPID(&drivePID);
						setPIDTarget(&drivePID, getRightDriveSensor());
						leftSpeed = leftSpeed - fabs(calculatePID(&drivePID, getLeftDriveSensor()));
					}
				}


				if((fabs(getRightDriveSensor() - chassisDistance) <= driveThreshold) || (fabs(getLeftDriveSensor() - chassisDistance) <= driveThreshold))
				startTimer(&drivePIDTimer);

				if(currentTime(&drivePIDTimer) > 300)
				driveDone = true;

			}

			else if(chassisDirection == gyroDriveStraight)// otherwise if the robot should drive straight with the gyro
			{
				heading = correctGyroValue(heading);
				setPIDTarget(&straightGyroPID, 0);
				setPIDTarget(&rightDrivePID, chassisDistance);
				setPIDTarget(&leftDrivePID, chassisDistance);
				leftSpeed = calculatePID(&leftDrivePID, getLeftDriveSensor());
				rightSpeed = calculatePID(&rightDrivePID, getRightDriveSensor());
				if(getLeftDriveSensor() > getRightDriveSensor())
				chassisSpeed = getRightDriveSensor();
				else
				chassisSpeed = getLeftDriveSensor();

				if(getLeftDriveSensor() > getRightDriveSensor())
				leftSpeed = rightSpeed;
				else
				rightSpeed = leftSpeed;

				if(fabs(leftSpeed) > largestDriveInput)
				leftSpeed = largestDriveInput*sgn(leftSpeed);
				if(fabs(rightSpeed) > largestDriveInput)
				rightSpeed = largestDriveInput*sgn(rightSpeed);

				if((gyroDirection(getGyroSensor(), heading) == 1))// if the robot is drifting left
				{
					 leftSpeed += (fabs(leftSpeed) * fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading))));
					 rightSpeed -= (fabs(rightSpeed) * fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading))));
					// leftSpeed +=fabs(leftSpeed)*.5;
					// rightSpeed -=fabs(rightSpeed)*.5;
					// leftSpeed += fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading)));
					// rightSpeed -= fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading)));
				}
				else if((gyroDirection(getGyroSensor(), heading) == -1))//otherwise if the robot is drifting right
				{
					 leftSpeed -= (fabs(leftSpeed) * fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading))));
					 rightSpeed += (fabs(rightSpeed) * fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading))));
					// leftSpeed -=fabs(leftSpeed)*.5;
					// rightSpeed +=fabs(rightSpeed)*.5;
					// leftSpeed -= fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading)));
					// rightSpeed += fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading)));
				}

				if((fabs(chassisSpeed - chassisDistance) <= driveThreshold))
				{
					startTimer(&drivePIDTimer);
				}
				if(currentTime(&drivePIDTimer) > 300)
				driveDone = true;
			}

			else if(chassisDirection == gyroTurn)// if the robot should turn using the gyro sensor
			{
				chassisDistance = correctGyroValue(chassisDistance);// correct the gyro target value
				setPIDTarget(&gyroPID, 0);
				if((gyroDirection(getGyroSensor(), chassisDistance) == 1))
				{
					leftSpeed = fabs(calculatePID(&gyroPID, gyroDifference(getGyroSensor(), chassisDistance)*gyroDirection(getGyroSensor(), chassisDistance)));
					rightSpeed = -fabs(calculatePID(&gyroPID,gyroDifference(getGyroSensor(), chassisDistance)*gyroDirection(getGyroSensor(), chassisDistance)));
				}
				else if((gyroDirection(getGyroSensor(), chassisDistance) == -1))
				{
					leftSpeed = -fabs(calculatePID(&gyroPID, gyroDifference(getGyroSensor(), chassisDistance)*gyroDirection(getGyroSensor(), chassisDistance)));
					rightSpeed = fabs(calculatePID(&gyroPID, gyroDifference(getGyroSensor(), chassisDistance)*gyroDirection(getGyroSensor(), chassisDistance)));
				}
				if(fabs(getGyroSensor() - chassisDistance) <= gyroThreshold)
				{
					startTimer(&drivePIDTimer);
				}

				if(currentTime(&drivePIDTimer) > 300)
				driveDone = true;

			}

			else if(chassisDirection == turn)
			{
				setPIDTarget(&rightDrivePID, -chassisDistance);
				setPIDTarget(&leftDrivePID, chassisDistance);
				leftSpeed = calculatePID(&leftDrivePID, getLeftDriveSensor());
				rightSpeed = calculatePID(&rightDrivePID, getRightDriveSensor());

				if (fabs(getRightDriveSensor()) > fabs(getLeftDriveSensor()))// if the right drive has travelled farther than the left drive
				{
					resetPID(&drivePID);
					setPIDTarget(&drivePID, -getLeftDriveSensor());
					rightSpeed = rightSpeed + calculatePID(&drivePID, getRightDriveSensor());
				}
				else if (fabs(getLeftDriveSensor()) > fabs(getRightDriveSensor()))// if the left drive has travelled farther than the left drive
				{
					resetPID(&drivePID);
					setPIDTarget(&drivePID, -getRightDriveSensor());
					leftSpeed = leftSpeed + calculatePID(&drivePID, getLeftDriveSensor());
				}

				if((fabs(getRightDriveSensor() - chassisDistance) <= driveThreshold) || (fabs(getLeftDriveSensor() - chassisDistance) <= driveThreshold))
				startTimer(&drivePIDTimer);

				if(currentTime(&drivePIDTimer) > 300)
				driveDone = true;
			}

			else if(chassisDirection == sweepRight || chassisDirection == forwardRight)
			{
				setPIDTarget(&rightDrivePID, chassisDistance);
				chassisSpeed = calculatePID(&rightDrivePID, getRightDriveSensor());
				if(chassisDirection == sweepRight)
				{
					rightSpeed = chassisSpeed;
					leftSpeed = chassisSpeed*.5;
				}
				else
				{
					rightSpeed = chassisSpeed;
					leftSpeed = 0;
				}
				if((fabs(getRightDriveSensor() - chassisDistance) <= driveThreshold))
				{
					startTimer(&drivePIDTimer);
				}
				if(currentTime(&drivePIDTimer) > 300)
				driveDone = true;
			}
			else if(chassisDirection == sweepLeft || chassisDirection == forwardLeft)// otherwise if the robot is driving with the left drive
			{
				setPIDTarget(&leftDrivePID, chassisDistance);
				chassisSpeed = calculatePID(&leftDrivePID, getLeftDriveSensor());
				if(chassisDirection == sweepLeft)
				{
					rightSpeed = chassisSpeed*.5;
					leftSpeed = chassisSpeed;
				}
				else
				{
					rightSpeed = 0;
					leftSpeed = chassisSpeed;
				}
				if((fabs(getLeftDriveSensor() - chassisDistance) <= driveThreshold))
				{
					startTimer(&drivePIDTimer);
				}
				if(currentTime(&drivePIDTimer) > 300)
				driveDone = true;
			}

			else if(chassisDirection == driveSpeed)
			{
				leftSpeed = chassisSpeed;
				rightSpeed = chassisSpeed;
				if(fabs(getLeftDriveSensor()) >= fabs(chassisDistance) && fabs(getRightDriveSensor()) >= fabs(chassisDistance))
				driveDone = true;
			}

			else if(chassisDirection == turnSpeed)
			{
				leftSpeed = chassisSpeed;
				rightSpeed = -chassisSpeed;

				if(fabs(getLeftDriveSensor()) >= fabs(chassisDistance) && fabs(getRightDriveSensor()) >= fabs(chassisDistance))
				driveDone = true;
			}

			else if(chassisDirection == sweepLeftSpeed || chassisDirection == forwardLeftSpeed)
			{
				leftSpeed = chassisSpeed;

				if(chassisDirection == sweepLeft)
				rightSpeed = chassisSpeed*.5;

				else
				rightSpeed = 0;


				if(fabs(getLeftDriveSensor()) >= fabs(chassisDistance))
				driveDone = true;
			}

			else if(chassisDirection == sweepRightSpeed || chassisDirection == forwardRightSpeed)
			{
				rightSpeed = chassisSpeed;

				if(chassisDirection == sweepRight)
				leftSpeed = chassisSpeed*.5;

				else
				leftSpeed = 0;


				if(fabs(getRightDriveSensor()) >= fabs(chassisDistance))
				driveDone = true;
			}

			else if(chassisDirection == driveStraightSpeed)
			{
				leftSpeed = chassisSpeed;
				rightSpeed = chassisSpeed;

				if (fabs(getRightDriveSensor()) > fabs(getLeftDriveSensor()))// if the right drive has travelled farther than the left drive
				{
					setPIDTarget(&drivePID, getLeftDriveSensor());
					rightSpeed += calculatePID(&drivePID, getRightDriveSensor());
				}
				else if (fabs(getLeftDriveSensor()) > fabs(getRightDriveSensor()))// if the right drive has travelled farther than the left drive
				{
					setPIDTarget(&drivePID, getRightDriveSensor());
					rightSpeed += calculatePID(&drivePID, getLeftDriveSensor());
				}

				if(fabs(getLeftDriveSensor()) >= fabs(chassisDistance) && fabs(getRightDriveSensor()) >= fabs(chassisDistance))
				driveDone = true;
			}

			else if(chassisDirection == gyroDriveStraightSpeed)
			{
				heading = correctGyroValue(heading);
				setPIDTarget(&straightGyroPID, 0);
				leftSpeed = chassisSpeed;
				rightSpeed = chassisSpeed;

				if((gyroDirection(getGyroSensor(), heading) == 1))// if the robot is drifting left
				{
					leftSpeed += fabs(leftSpeed) * fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading)*gyroDirection(getGyroSensor(), heading)));
					rightSpeed -= fabs(rightSpeed) * fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading)*gyroDirection(getGyroSensor(), heading)));

				}
				else if((gyroDirection(getGyroSensor(), heading) == -1))//otherwise if the robot is drifting right
				{
					leftSpeed -= fabs(leftSpeed) * fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading)*gyroDirection(getGyroSensor(), heading)));
					rightSpeed += fabs(rightSpeed) * fabs(calculatePID(&straightGyroPID, gyroDifference(getGyroSensor(), heading)*gyroDirection(getGyroSensor(), heading)));
				}


				if(fabs(getLeftDriveSensor()) >= fabs(chassisDistance) && fabs(getRightDriveSensor()) >= fabs(chassisDistance))
				driveDone = true;

			}

			else if(chassisDirection == gyroTurnSpeed)
			{
				heading = correctGyroValue(heading);
				chassisDistance = correctGyroValue(chassisDistance);// correct the gyro target value

				if((gyroDirection(getGyroSensor(), chassisDistance) == 1))
				{
					leftSpeed = chassisSpeed;
					rightSpeed = -chassisSpeed;
				}
				else if((gyroDirection(getGyroSensor(), chassisDistance) == -1))
				{
					leftSpeed = -chassisSpeed;
					rightSpeed = chassisSpeed;
				}

				if(gyroDifference(getGyroSensor(), heading) >= gyroDifference(heading, chassisDistance))
				driveDone = true;
			}

			else if (chassisDirection == accelerometerPark)
			{

			}

			else// otherwise
			{
				driveDone = true;// the drive is done
			}
			if(fabs(leftSpeed) > largestDriveInput)
			leftSpeed = largestDriveInput*sgn(leftSpeed);
			if(fabs(rightSpeed) > largestDriveInput)
			rightSpeed = largestDriveInput*sgn(rightSpeed);

			moveDrive(leftSpeed, rightSpeed, 0);
		}
		else// if the drive is done
		{
			moveDrive(0,0,0);
		}

		///////////////////////////////////// End Drive /////////////////////////////////////////////////////////////////////////////////////////////////

		if(liftPosition != -1)// if the lift is not done
		{
				if((liftSensor > (liftPosition+liftThreshold)))// if the lift needs to go down
				{
					if(fabs(liftSensor-liftPosition) < 300)
					{
						moveLift(-liftSpeed/3);
					}
					else
					{
						moveLift(-liftSpeed);// move the lift down
				  }
				}
				else if((liftSensor < (liftPosition-liftThreshold)))// if the lift should go up
				{
					if(fabs(liftSensor-liftPosition) < 300)
					{
						moveLift(liftSpeed/3);
					}
					else
					{
						moveLift(liftSpeed);// move the lift down
				  }
				}
				else// otherwise
				{
					moveLift(0);
				}
		}
		else// otherwise
		{
			moveLift(0);// stop the lift
			liftDone = true;
		}

		if(flipperPosition != -1)// if the lift is not done
		{
				if((flipperSensor > (flipperPosition+flipperThreshold)))// if the lift needs to go down
				{
					moveFlipper(flipperSpeed);// move the lift down
				}
				else if((flipperSensor < (flipperPosition-flipperThreshold)))// if the lift should go up
				{
					moveFlipper(flipperSpeed);// move the lift up
				}
				else// otherwise
				{
					moveFlipper(10*sgn(flipperSpeed));
				}
		}
		else// otherwise
		{
			moveFlipper(0);// stop the lift
		}

		///////////////////////////////////// End Lift /////////////////////////////////////////////////////////////////////////////////////////////////
		if(!intakeDone)
		{
			moveIntake(intakeTarget);
		}
		else
		{
			moveIntake(intakeTarget);
		}

		if(currentTime(&rfLauncherTimer) < 300)
		{
			moveLauncher(127);
		}
		else
		{
			if(getLauncherSensor())
			{
				moveLauncher(0);
			}
			else
			{
				moveLauncher(127);
			}
		}


		// if(!launcherDone)
		// {
		// 	if(launcherShooting)
		// 	{
		// 		if(!isLauncherLoaded())
		// 		{
		// 			launcherDone = true;
		// 		}
		// 		else
		// 		{
		// 			moveLauncher(127);
		// 		}
		// 	}
		// 	else
		// 	{
		// 		if(!isLauncherLoaded())
		// 		{
		// 			startTimer(&rfLauncherTimer);
		// 			if(currentTime(&rfLauncherTimer) > 300)
		// 			{
		// 			  moveLauncher(127);
		// 		  }
		// 		}
		// 		else
		// 		{
		// 			moveLauncher(0);
		// 			launcherDone = true;
		// 		}
		// 	}
		// }
		// else
		// {
		// 	moveLauncher(0);
		// }

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		//Parse the instructions
		if((commandReadPos != commandWritePos) && (commandReadPos+1 != commandWritePos))
		{
			if(instructions[commandReadPos] == launcher)
			{
				zeroTimer(&rfLauncherTimer);
				commandReadPos ++;
			}
			// else if(instructions[commandReadPos] == launcherStop)
			// {
			// 	moveLauncher(0);
			// 	commandReadPos ++;
			// }
			else if(instructions[commandReadPos] == goToStart)
			{
				commandReadPos = 0;
			}
			else if(instructions[commandReadPos] < 0)
			{
				commandReadPos++;
			}
			else if(instructions[commandReadPos] <= driveCommandMaxValue)
			{
				if(driveDone)
				{
					resetPID(&rightDrivePID);
					resetPID(&leftDrivePID);
					resetPID(&drivePID);
					resetPID(&gyroPID);
					resetPID(&straightGyroPID);
					resetLeftDriveSensor();
					resetRightDriveSensor();
					zeroTimer(&driveTimer);
					stopTimer(&drivePIDTimer);
					zeroTimer(&drivePIDTimer);
					zeroTimer(&accelerationTimer);
					startTimer(&accelerationTimer);
					maxDriveTime = 0;
					driveDone = false;
					heading = getGyroSensor();
					if(instructions[commandReadPos] <= PIDDriveCommandMaxValue)
					{
						chassisDirection = instructions[commandReadPos];
						commandReadPos++;
						if(chassisDirection == gyroDriveStraight)
						{
							heading = instructions[commandReadPos];
							commandReadPos++;
						}
						chassisDistance = instructions[commandReadPos];
						commandReadPos++;
					}
					else
					{
						chassisDirection = instructions[commandReadPos];
						commandReadPos++;
						chassisSpeed = instructions[commandReadPos];
						commandReadPos++;
						chassisDistance = instructions[commandReadPos];
						commandReadPos++;
						if(chassisDirection == gyroDriveStraightSpeed)
						{
							heading = instructions[commandReadPos];
							commandReadPos++;
						}
					}
				}
			}
			else
			{
				switch(instructions[commandReadPos])
				{
					case launcher:
						// maxLauncherTime = 0;
						// launcherDone = false;
						commandReadPos++;
						// zeroTimer(&rfLauncherTimer);
						// stopTimer(&rfLauncherTimer);
						// if(commandReadPos == reload)
						// {
						// 	launcherReloading = true;
						// 	//launcherShooting = false;
						// }
						// if(commandReadPos == shoot)
						// {
						// 	launcherShooting = true;
						// }

					break;

					case lift:
						commandReadPos++;
						liftSpeed = instructions[commandReadPos];
						commandReadPos++;
						liftPosition = instructions[commandReadPos];
						commandReadPos++;
					break;

					case flipper:

						commandReadPos++;
						flipperSpeed = instructions[commandReadPos];
						commandReadPos++;
						flipperPosition = instructions[commandReadPos];
						commandReadPos++;
					break;

					case holdLift:
					if(liftDone)
					{

						zeroTimer(&liftTimer);
						liftDone = false;
						maxLiftTime = 0;
						liftDirection = instructions[commandReadPos];
						commandReadPos++;
						setLiftTarget(&liftHolder, instructions[commandReadPos]);
						commandReadPos++;

					}
					break;

					case intake:
					if(intakeDone)
					{
						intakeDone = false;
						commandReadPos++;
						intakeTarget = instructions[commandReadPos];
						commandReadPos++;
					}
					break;

					case setLift:
					if(liftDone)
					{
						zeroTimer(&liftTimer);
						stopTimer(&liftPIDTimer);
						zeroTimer(&liftPIDTimer);
						liftDone = false;
						maxLiftTime = 0;
						liftDirection = instructions[commandReadPos];
						commandReadPos++;
						setLiftTarget(&liftHolder, instructions[commandReadPos]);
						liftPosition = instructions[commandReadPos];
						commandReadPos++;
					}

					break;

					break;

					case pause:
					if(instructions[commandReadPos+1] <= driveCommandMaxValue)
					{
						if(driveDone)
						commandReadPos+=2;
					}
					else
					{
						switch(instructions[commandReadPos+1])
						{
							case time:
							if(commandReadPos+2 == 0)
							{
								if(finished)
								commandReadPos+=3;
							}
							else
							{
								if(maxPauseTime == 0 && finished)
								{
									zeroTimer(&pauseTimer);
									startTimer(&pauseTimer);
									maxPauseTime = instructions[commandReadPos+2];
								}
								if((currentTime(&pauseTimer) >= maxPauseTime) && maxPauseTime != 0)
								{
									maxPauseTime = 0;
									commandReadPos+=3;
								}
							}
							break;
							case lift:
							if(liftDone)
							commandReadPos+=2;
							break;
							case intake:
							if(intakeDone)
							commandReadPos+=2;
							break;
							case launcher:
							if(launcherDone)
							commandReadPos+=2;
							break;

						}
					}
					break;

					case pauseAll:
					if(driveDone && liftDone && intakeDone && launcherDone)
					commandReadPos++;
					break;
					case maxTime:
					commandReadPos++;
					if(instructions[commandReadPos] < driveCommandMaxValue)
					{
						commandReadPos++;
						maxDriveTime = instructions[commandReadPos];
						commandReadPos++;
					}
					else
					{
						switch(instructions[commandReadPos])
						{
							case lift:
							commandReadPos++;
							maxLiftTime = instructions[commandReadPos];
							commandReadPos++;
							break;
							case intake:
							commandReadPos++;
							maxIntakeTime = instructions[commandReadPos];
							commandReadPos++;
							break;
							case launcher:
							commandReadPos++;
							maxLauncherTime = instructions[commandReadPos];
							commandReadPos++;
							break;
						}
					}
					break;

					case end:
					commandReadPos++;
					if(instructions[commandReadPos] <= driveCommandMaxValue)
					{
						driveDone = true;
					}
					else
					{
						switch(instructions[commandReadPos])
						{
							case lift:
							liftDone = true;
							break;
							case intake:
							intakeDone = true;
							break;
							case launcher:
							launcherDone = true;
							break;
						}
					}
					commandReadPos++;
					break;
				}
			}
		}

		if((currentTime(&driveTimer) > maxDriveTime) && (maxDriveTime != 0))
		driveDone = true;
		if((currentTime(&liftTimer) > maxLiftTime) && (maxLiftTime != 0))
		liftDone = true;
		if((currentTime(&intakeTimer) > maxIntakeTime) && (maxIntakeTime != 0))
		intakeDone = true;
		if((currentTime(&launcherTimer) > maxLauncherTime) && (maxLauncherTime != 0))
		launcherDone = true;

		if(driveDone && liftDone && intakeDone && launcher)// if all the subsystems are done
		finished = true;

		launcherShooting = finished;

		pros::c::task_delay_until(&lastRun, 10);
		lastRun = pros::c::millis();
	}
}

#endif
