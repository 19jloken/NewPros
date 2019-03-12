#ifndef autons_cpp
#define autons_cpp

#include "headers/autons.h"
#include "headers/robotFunction.h"
#include "headers/pollSensors.h"

// //autonomous routines
void autonomous1 ()
{
  //Front red flipps all red side flags and gets 2 caps
  addCommand(driveStraight, 3000,intake, 127);
  addCommand(driveStraight, -2800);
  addCommand(turn, -1300);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(end, intake,turn, -220);
  addCommand(driveStraight, 3600);
  addCommand(driveStraight, -1600);
  addCommand(turn, 1500,intake, -127);
  addCommand(driveStraight, 1000);
  addCommand(driveStraight, 1000);
  addCommand(driveStraight, -325);
  addCommand(turn, -725);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(turn, -100);
  addCommand(driveStraight, 2300);
}
void autonomous2 ()
{
  //Back Red, shoots at center flags, gets one cap, and parks
  addCommand(driveStraight, 3000,intake, 127);
  addCommand(driveStraight, -900);
  addCommand(end, intake);
  addCommand(turn, -1200);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(turn, 1200);
  addCommand(driveStraight, 600);
  addCommand(turn, 1300);
  addCommand(driveStraight, -2800);
}
void autonomous3 ()
{
  //Back Red gets ball under cap by platform, turn and pick up cap, score on
  //post and get second cap flip cap and then go put it on post, park
  addCommand(intake, 127, driveStraight, 3000);
  addCommand(driveStraight, -1000);
  addCommand(turn, -2700, flipper, -100, 10);
  addCommand(driveStraight, -1000);
  addCommand(flipper, 10, 10, driveStraight, 800);
  addCommand(turn, 1300);
  addCommand(pause, drive);
  addCommand(lift, 127, 2200, driveStraight, -800);
  addCommand(pause, drive);
  addCommand(lift, 127, 1800, driveStraight, 400);
  addCommand(flipper, -80, 10, lift, 127, 1450, driveStraight, -800);
  addCommand(pause, drive);
  addCommand(flipper, 127, 10, driveStraight, 1800);
  addCommand(turn, 1300, lift, 100, 2200);
  addCommand(driveStraight, -600);
  addCommand(flipper, -80, 10);
  addCommand(lift, 127, 1800, driveStraight, 1500);
  addCommand(turn, -1300);
  addCommand(driveStraight, -2000);
}
void autonomous4 ()
{
  //Front Blue flipps all blue side flags and gets 2 caps
  addCommand(driveStraight, 2950,intake, 127);
  addCommand(driveStraight, -2900);
  addCommand(turn, 1300);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(end, intake);
  addCommand(driveStraight, 3600);
  addCommand(driveStraight, -1600);
  addCommand(turn, -1550,intake, -127);
  addCommand(driveStraight, 1000);
  addCommand(driveStraight, 1000);
  addCommand(driveStraight, -325);
  addCommand(turn, 725);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(turn, 100);
  addCommand(driveStraight, 2300);
}
void autonomous5 ()
{
  //Back Blue shoots at center flags, gets one cap, parks
  addCommand(driveStraight, 3000,intake, 127);
  addCommand(driveStraight, -900);
  addCommand(end, intake);
  addCommand(turn, 1100);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(turn, -1100);
  addCommand(driveStraight, 600);
  addCommand(turn, -1300);
  addCommand(driveStraight, -2800);
}
void autonomous6 ()
{
  //Back Blue gets ball under cap by platform, turn and pick up cap, score on
  //post and get second cap flip cap and then go put it on post, park
  addCommand(intake, 127, driveStraight, 2650);
  addCommand(driveStraight, -1000);
  addCommand(turn, 2620, flipper, -100, 10);
  addCommand(end, intake, intake, 0);
  addCommand(driveStraight, -1100);
  addCommand(pause, drive);
  addCommand(flipper, 20, 10, lift, 100, 1700);
  addCommand(pause, time, 100);
  addCommand(driveStraight, 1600);
  addCommand(turn, -1600);
  addCommand(pause, drive);
  addCommand(pause, time, 100);
  addCommand(driveStraight, -400, lift, 127, 2800);
  addCommand(driveStraight, -800);
  addCommand(pause, drive);
  addCommand(pause, time, 800);
  addCommand(lift, 10, 1800, driveStraight, 800);
  addCommand(flipper, -30, 10, lift, 127, 1400, turn, 960);
  addCommand(driveStraight, -1900);
  addCommand(pause, drive);
  addCommand(flipper, 70, 1);
  addCommand(driveStraight, 2700);
  addCommand(turn, -2650, lift, 100, 3100);
  addCommand(driveStraight, -600);
  addCommand(flipper, -10, 10);
  addCommand(pause, time, 100);
  addCommand(lift, 127, 1800, driveStraight, 1500);
  addCommand(pause, drive);
  addCommand(lift, 100, 1350, turn, 2400);
  addCommand(driveStraight, -3000);
}
void autonomous7 ()
{
  //Programming skills starting in the back tile
  // addCommand(intake, 127, driveStraight, 3200);
  // addCommand(driveStraight, -3000);
  // addCommand(turn, -1335);
  // addCommand(driveStraight, 3750);
  // addCommand(pause, drive);
  // addCommand(launcher);
  // addCommand(turn, -250);
  // addCommand(driveStraight, 3600);
  // addCommand(driveStraight, -1600);
  // addCommand(pause, time, 500);
  // addCommand(end, intake, turn, 1375);
  // addCommand(intake, -127);
  // addCommand(driveStraight, 1000);
  // addCommand(driveStraight, 1000);
  // addCommand(driveStraight, -325);
  // addCommand(turn, -725);
  // addCommand(pause, drive);
  // addCommand(launcher);
  // addCommand(turn, -100);
  // addCommand(driveStraight, 2300, end, intake);
  // addCommand(driveStraight, -3000);
  addCommand(driveStraight, 3000,intake, 127);
  addCommand(driveStraight, -2800);
  addCommand(turn, -1300);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(end, intake,turn, -220);
  addCommand(driveStraight, 3600);
  addCommand(driveStraight, -1600);
  addCommand(turn, 1550,intake, -127);
  addCommand(driveStraight, 1000);
  addCommand(driveStraight, 1000);
  addCommand(driveStraight, -325);
  addCommand(turn, -725);
  addCommand(pause, drive);
  addCommand(launcher);
  addCommand(turn, -150);
  addCommand(driveStraight, 2300);
  addCommand(turn, 250);
  addCommand(driveStraight, -2500);
  addCommand(turn, -750);
  addCommand(lift, 10, 1500, driveStraight, -3000);
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
