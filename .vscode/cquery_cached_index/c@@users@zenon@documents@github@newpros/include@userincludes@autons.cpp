#ifndef autons_cpp
#define autons_cpp

#include "headers/autons.h"
#include "headers/robotFunction.h"
#include "headers/pollSensors.h"

// //autonomous routines
void autonomous1 ()
{
  //Front red
  // addCommand(driveStraight, 2750,intake, 127);
  // addCommand(turn, -200,driveStraight, -2500);
  // addCommand(turn, -1250);
  // addCommand(pause, drive);
  // addCommand(launcher);
  // addCommand(end, intake,turn, -100);
  // addCommand(driveStraight, 3400);
  // addCommand(driveStraight, -1500);
  // addCommand(turn, 1350,intake, -127);
  // addCommand(driveStraight, 900);
  // addCommand(driveStraight, 900);
  // addCommand(turn, -1300);
  // addCommand(driveStraight, -3000,end, intake);

  //Back Red
  addCommand(driveStraight, 3000,intake, 127);
  addCommand(driveStraight, -900);
  addCommand(end, intake);
  addCommand(turn, -1200);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(turn, 1200);
  addCommand(driveStraight, 600);
  addCommand(turn, 1300);
  addCommand(driveStraight, -2500);
  //
  // //Front Blue
  //   addCommand(driveStraight, 2750,intake,127);
  //   addCommand(driveStraight, -2750);
  //   addCommand(turn, 1370);
  //   addCommand(pause, drive);
  //   addCommand(launcher);
  //   addCommand(end, intake,turn, 100);
  //   addCommand(driveStraight, 2500);
  //   addCommand(driveStraight, -1500);
  //   addCommand(turn, -1300,intake, -127);
  //   addCommand(driveStraight, 800);
  //   addCommand(driveStraight, 800);
  //   addCommand(turn, 1300);
  //   addCommand(driveStr]aight, -3000,end, intake);
  //
  // //Back Blue
  // addCommand(driveStraight, 3000,intake, 127);
  // addCommand(driveStraight, -900);
  // addCommand(end, intake);
  // addCommand(turn, 990);
  // addCommand(pause, drive);
  // addCommand(launcher);
  // addCommand(turn, -1100);
  // addCommand(driveStraight, 800);
  // addCommand(turn, -1300);
  // addCommand(driveStraight, -1000);
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
