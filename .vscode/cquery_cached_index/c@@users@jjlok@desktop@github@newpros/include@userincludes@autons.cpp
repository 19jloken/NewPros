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
  addCommand(driveStraight, 2750,intake,127);
  addCommand(driveStraight, -2750);
  addCommand(turn, -1370);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(end, intake,turn, -100);
  addCommand(driveStraight, 2500);
  addCommand(driveStraight, -1500);
  addCommand(turn, 1300,intake, -127);
  addCommand(driveStraight, 800);
  addCommand(driveStraight, 800);
  addCommand(turn, -1300);
  addCommand(driveStraight, -3000,end, intake);
}
else// if in back red tile by posts
{
  addCommand(driveStraight, 3000);
  addCommand(turn, -1300);
  addCommand(pause, drive);
  addCommand(driveStraight, -1000);
  addCommand(pause, drive, setLift, 80);
  addCommand(driveStraight, -500);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(driveStraight, 500);
  addCommand(turn, 400);
  addCommand(driveStraight, -800);
}
}
else //if on blue side (have button un-clicked)
{
  if(getAutoSensor())//   if in front blue tile by flags (button is clicked)
  {
    addCommand(driveStraight, 2750,intake,127);
    addCommand(driveStraight, -2750);
    addCommand(turn, 1370);
    addCommand(pause, drive);
    addCommand(launcher);
    addCommand(end, intake,turn, 100);
    addCommand(driveStraight, 2500);
    addCommand(driveStraight, -1500);
    addCommand(turn, -1300,intake, -127);
    addCommand(driveStraight, 800);
    addCommand(driveStraight, 800);
    addCommand(turn, 1300);
    addCommand(driveStraight, -3000,end, intake);
}
else// if in back blue tile by posts (button unclicked)
{
  addCommand(driveStraight, 3000);
  addCommand(turn, 1300);
  addCommand(pause, drive);
  addCommand(driveStraight, -1000);
  addCommand(pause, drive, setLift, 80);
  addCommand(driveStraight, -500);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(driveStraight, 500);
  addCommand(turn, -400);
  addCommand(driveStraight, -800);

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
