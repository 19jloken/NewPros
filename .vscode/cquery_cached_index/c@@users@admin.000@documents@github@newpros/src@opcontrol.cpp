#include "main.h"
#include "headers/opcontrol.h"
#include "headers/robotFunction.h"
#include "headers/motorSlew.h"
#include "headers/general.h"
#include "headers/timers.h"
#include "headers/pollSensors.h"
#include "pros/rtos.h"

using namespace pros;

/**
* Runs the operator control code. This function will be started in its own task
* with the default priority and stack size whenever the robot is enabled via
* the Field Management System or the VEX Competition Switch in the operator
* control mode.
*
* If no competition control is connected, this function will run immediately
* following initialize().
*
* If the robot is disabled or communications is lost, the
* operator control task will be stopped. Re-enabling the robot will restart the
* task, not resume it from where it left off.
*/
bool curve = false;// should the robot use the parametric drive formula
bool inversed = false;// should the drive be inversed
bool control = false;// should the drive be in control mode
timer opLauncherTimer;
bool launcherWasLoaded = false;
int firstLoadedPostion;
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);
// pros::Task userAutonomousTask(userAutonomous, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "userAutonomousTask");
void opcontrol()
{
  // userAutonomousTask.suspend();
  robotFunctionTask.suspend();
  enableSlew(0);
  enableSlew(1);
  enableSlew(2);
  enableSlew(3);
  enableSlew(4);
  enableSlew(5);
  enableSlew(6);
  enableSlew(7);

  initializeTimer(&opLauncherTimer);
  zeroTimer(&opLauncherTimer);
  stopTimer(&opLauncherTimer);
  uint32_t lastRun = pros::c::millis();
  // pros::lcd::set_text(1, "Hello PROS User!u");

  while(true)// infinite while loop
  {
    // pros::lcd::set_text(1, "Hello PROS User");
    if (partner.is_connected())// if their are two controllers
    {
      // pros::lcd::set_text(1, "Two Controller Drive");
      doubleControllerDrive();// use the two controller drive code
    }
    else// if there is one controller
    {
      // pros::lcd::set_text(0, "Single Controller Drive");
      // pros::lcd::print(2, "raw cali %d", pros::c::adi_analog_read_calibrated_HR(5));
      singleControllerDrive();// use the one controller drive code
    }
    pros::c::task_delay_until(&lastRun, 5);
    lastRun = pros::c::millis();
  }
}

void doubleControllerDrive()
{
  // userAutonomousTask.suspend();
  robotFunctionTask.suspend();
  float leftIn;
  float rightIn;
  float tempLeftIn;
  float tempRightIn;
  int strafe;

  leftIn = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  rightIn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);


  if(control)
  {
    leftIn = (leftIn*.5);
    rightIn = (rightIn*.5);
  }

  if (curve)
  {
    leftIn = fabs(leftIn)*leftIn/127;
    rightIn = fabs(rightIn)*rightIn/127;
  }

  if(inversed)
  {
    tempLeftIn = -rightIn;
    tempRightIn = -leftIn;
    leftIn = tempLeftIn;
    rightIn = tempRightIn;
  }

  strafe = master.get_digital(E_CONTROLLER_DIGITAL_R1) + master.get_digital(E_CONTROLLER_DIGITAL_R2) - master.get_digital(E_CONTROLLER_DIGITAL_L1) - master.get_digital(E_CONTROLLER_DIGITAL_L2);

  moveDrive(leftIn, rightIn, strafe);

  moveLift(partner.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
  {
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {
      pros::delay(5);
    }
     autonomous();
     while(!master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {
      pros::delay(5);
    }
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {
      pros::delay(5);
    }
  }

  if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    moveIntake(-127);
  }
  else if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
  {
    moveIntake(127);
  }
  else
  {
    moveIntake(0);
  }

  moveFlipper(partner.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));


  if(isLauncherLoaded() || (fabs(firstLoadedPostion - motorArray[6]->get_position()) < 150 && launcherWasLoaded))
  {
    if(!launcherWasLoaded)
    {
      firstLoadedPostion = motorArray[6]->get_position();
    }
      launcherWasLoaded = true;
      zeroTimer(&opLauncherTimer);
      stopTimer(&opLauncherTimer);
      if(partner.get_digital(pros::E_CONTROLLER_DIGITAL_A) || master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
      {
        moveLauncher(127);
      }
      else
      {
        moveLauncher(0);
      }
  }
  else
  {
    launcherWasLoaded = false;
    startTimer(&opLauncherTimer);
    if(currentTime(&opLauncherTimer) > 400)
    {
      moveLauncher(127);
    }
    else
    {
      moveLauncher(0);
    }
  }



}

void singleControllerDrive()
{
  // userAutonomousTask.suspend();
  robotFunctionTask.suspend();
  float leftIn;
  float rightIn;
  float tempLeftIn;
  float tempRightIn;
  int strafe;

  leftIn = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  rightIn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);


  if(control)
  {
    leftIn = (leftIn*.5);
    rightIn = (rightIn*.5);
  }

  if (curve)
  {
    leftIn = fabs(leftIn)*leftIn/127;
    rightIn = fabs(rightIn)*rightIn/127;
  }

  if(inversed)
  {
    tempLeftIn = -rightIn;
    tempRightIn = -leftIn;
    leftIn = tempLeftIn;
    rightIn = tempRightIn;
  }

  strafe = 2*(master.get_digital(E_CONTROLLER_DIGITAL_R2)) - 2*(master.get_digital(E_CONTROLLER_DIGITAL_L2));

  moveDrive(leftIn, rightIn, strafe);

  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
  {
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
      pros::delay(5);
    }
     autonomous();
     while(!master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
      pros::delay(5);
    }
    while(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
      pros::delay(5);
    }
  }

  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
  {
    moveIntake(127);
  }
  else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
  {
    moveIntake(-127);
  }
  else
  {
    moveIntake(0);
  }

  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
  {
    moveFlipper(127);
  }
  else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
  {
    moveFlipper(-127);
  }
  else
  {
    moveFlipper(0);
  }

  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
  {
    moveLift(127);
  }
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
  {
    moveLift(-127);
  }
  else
  {
    moveLift(0);
  }


  if(isLauncherLoaded() || (fabs(firstLoadedPostion - motorArray[6]->get_position()) < 150 && launcherWasLoaded))
  {
    if(!launcherWasLoaded)
    {
      firstLoadedPostion = motorArray[6]->get_position();
    }
      launcherWasLoaded = true;
      zeroTimer(&opLauncherTimer);
      stopTimer(&opLauncherTimer);
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
      {
        moveLauncher(127);
      }
      else
      {
        moveLauncher(0);
      }
  }
  else
  {
    launcherWasLoaded = false;
    startTimer(&opLauncherTimer);
    if(currentTime(&opLauncherTimer) > 400)
    {
      moveLauncher(127);
    }
    else
    {
      moveLauncher(0);
    }
  }
  // userAutonomousTask.resume();
  // autonomous();
}

// void userAutonomous(void* param)
// {
//     autonomous();
//     while(1 == 1)
//     {
//       pros::delay(5);
//     }
// }
