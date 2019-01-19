#ifndef autons_cpp
#define autons_cpp

#include "headers/autons.h"
#include "headers/robotFunction.h"
#include "headers/pollSensors.h"

// //autonomous routines
void autonomous1 ()
{
if (getSideSensor()) //if on red side
{
  if(getAutoSensor())//  if in front red  tile by flags
  {
  addCommand(driveStraight, 2800);
  addCommand(intake,127);
  addCommand(driveStraight, -2800);
  addCommand(turn, -1340);
  addCommand(pause, drive);
  addCommand(end, intake);
  addCommand(intake, -127);
  addCommand(launcher);
  addCommand(turn, 650); //increase I think
  addCommand(end, intake);
  addCommand(intake, -127);
  addCommand(driveStraight, 800);
  addCommand(driveStraight, 800);
  addCommand(driveStraight, 800);
}
else// if in back blue tile by posts
{
  addCommand(intake,127);
  addCommand(driveStraight, 2950);
  addCommand(driveStraight, -400);
  addCommand(turn, -1220);
  addCommand(pause, drive);
  addCommand(end, intake);
  addCommand(turn, 2200);
  addCommand(driveStraight, -3050);
}
}
else //if on blue side
{
  if(getAutoSensor())//   if in front tile by flags
  {
    addCommand(driveStraight, 2800);
    addCommand(intake,127);
    addCommand(driveStraight, -2800);
    addCommand(turn, -900);
    addCommand(pause, drive);
    addCommand(end, intake);
    addCommand(intake, -127);
    addCommand(launcher);
    addCommand(driveStraight, 3750);
    addCommand(driveStraight, -800);
    addCommand(turn, -500);
    addCommand(end, intake);
    addCommand(intake, -127);
    addCommand(driveStraight, 800);
    addCommand(driveStraight, 800);
    addCommand(driveStraight, 800);
}
else// if in back tile by posts
{
  addCommand(driveStraight, 2800);
  addCommand(intake,127);
  addCommand(turn, -600);
  addCommand(pause, drive);
  addCommand(end, intake);
  addCommand(turn, -1250);
  addCommand(driveStraight, 1200);
}
}
}
void autonomous2 ()
{
}
void autonomous3 ()
{
}
void autonomous4 ()
{
}
void autonomous5 ()
{
}
void autonomous6 ()
{
}
void autonomous7 ()
{
}
void autonomous8 ()
{
}
void autonomous9 ()
{
}
void autonomous10 ()
{
}
void autonomous11 ()
{
}
void autonomous12 ()
{
}
void autonomous13 ()
{
}
void autonomous14 ()
{
}
void autonomous15 ()
{
}
void autonomous16 ()
{
}

#endif
