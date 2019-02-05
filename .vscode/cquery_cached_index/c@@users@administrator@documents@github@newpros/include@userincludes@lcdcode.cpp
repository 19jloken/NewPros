#ifndef lcdCode_cpp
#define lcdCode_cpp

#include "headers/lcdCode.h"
#include "headers/general.h"
#include "pros/llemu.hpp"
#include "main.h"

bool leftButtonPressed = false;
bool centerButtonPressed = false;
bool rightButtonPressed = false;

// https://docs.littlevgl.com/

// void lv_tutorial_objects(void)
// {
//     /********************
//      * CREATE A SCREEN
//      *******************/
//     /* Create a new screen and load it
//      * Screen can be created from any type object type
//      * Now a Page is used which is an objects with scrollable content*/
//
//     lv_obj_t * scr = lv_page_create(NULL, NULL);
//     lv_scr_load(scr);
//
//     /****************
//      * ADD A TITLE
//      ****************/
//
//     lv_obj_t * label = lv_label_create(scr, NULL); /*First parameters (scr) is the parent*/
//     lv_label_set_text(label, "Autonomous Selection");  /*Set the text*/
//     lv_obj_set_x(label, 50);                        /*Set the x coordinate*/
//
//     /***********************
//      * CREATE TWO BUTTONS
//      ***********************/
//     /*Create a button*/
//     lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);         /*Create a button on the currently loaded screen*/
//     lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_rel_action); /*Set function to be called when the button is released*/
//     lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);  /*Align below the label*/
//
//     /*Create a label on the button (the 'label' variable can be reused)*/
//     label = lv_label_create(btn1, NULL);
//     lv_label_set_text(label, "Button 1");
//
//     /*Copy the previous button*/
//     lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), btn1);        /*Second parameter is an object to copy*/
//     lv_obj_align(btn2, btn1, LV_ALIGN_OUT_RIGHT_MID, 50, 0);    /*Align next to the prev. button.*/
//
//     /*Create a label on the button*/
//     label = lv_label_create(btn2, NULL);
//     lv_label_set_text(label, "Button 2");
//
// }

void autonomousSelection()
{
  if(autonomousSelected)
  {
  // pros::lcd::print(0, "Autonomous %d selected", autonomousMode);
  //   pros::lcd::set_text(1, "Center Btn to deselect");
  //   pros::lcd::register_btn1_cb(unselectAutonomous);
  }
  else
  {
    // pros::lcd::print(0, "Autonomous %d", autonomousMode);
    // pros::lcd::set_text(1, "Center Btn to select");
    // pros::lcd::register_btn0_cb(decreaseAutonomousMode);
    // pros::lcd::register_btn1_cb(selectAutonomous);
    // pros::lcd::register_btn2_cb(increaseAutonomousMode);
  }
}

void decreaseAutonomousMode()
{
  leftButtonPressed = !leftButtonPressed;
  if (leftButtonPressed)
	{
		autonomousMode--;
		if(autonomousMode < 1)
		autonomousMode = 16;
  }
}

void selectAutonomous()
{
  centerButtonPressed = !centerButtonPressed;
  if (centerButtonPressed)
	{
		autonomousSelected = true;
  }
}

void increaseAutonomousMode()
{
  rightButtonPressed = !rightButtonPressed;
  if (rightButtonPressed)
	{
		autonomousMode++;
		if(autonomousMode > 16)
		autonomousMode = 1;
  }
}

void unselectAutonomous()
{
	centerButtonPressed = !centerButtonPressed;
	if(centerButtonPressed)
	{
		autonomousSelected = false;
	}
}

#endif
