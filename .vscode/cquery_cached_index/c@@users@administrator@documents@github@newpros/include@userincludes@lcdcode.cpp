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

// int count;
// int middle = 0;
// char *auton;
//
// static lv_res_t blueFront(lv_obj_t * btn)
// {
//   static bool pressed = true;
//   delay(100);
//   if (pressed)
//   {
//     middle = 1;
//     pressed = false;
//     count = 1;
//     auton = "BLUE FRONT";
//   }
//   return LV_RES_OK;
// }
//
// static lv_res_t redFront(lv_obj_t * btn)
// {
//   static bool pressed = true;
//   delay(100);
//   if (pressed)
//   {
//     middle = 1;
//     pressed = false;
//     count = 0;
//     auton = "RED FRONT";
//   }
//   return LV_RES_OK;
// }
//
// static lv_res_t blueBack(lv_obj_t * btn)
// {
//   static bool pressed = true;
//   delay(100);
//   if (pressed)
//   {
//     middle = 1;
//     pressed = false;
//     count = 3;
//     auton = "BLUE BACK";
//   }
//   return LV_RES_OK;
// }
//
// static lv_res_t redBack(lv_obj_t * btn)
// {
//   static bool pressed = true;
//   delay(100);
//   if (pressed)
//   {
//     middle = 1;
//     pressed = false;
//     count = 2;
//     auton = "RED BACK";
//   }
//   return LV_RES_OK;
// }

static lv_res_t btn_click_action(lv_obj_t * btn)
{
  static lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  uint8_t id = lv_obj_get_free_num(btn);
  char mytext[64];

  sprintf(mytext, "Button %d is released\n", id);
  lv_label_set_text(label, mytext);
  lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 5);

  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}


void gui(void)
{
    /********************
     * CREATE A SCREEN
     *******************/
    /* Create a new screen and load it
     * Screen can be created from any type object type
     * Now a Page is used which is an objects with scrollable content*/

    lv_obj_t * scr = lv_page_create(NULL, NULL);
    lv_scr_load(scr);

    /****************
     * ADD A TITLE
     ****************/

    lv_obj_t * label = lv_label_create(lv_scr_act(), NULL); /*First parameters (scr) is the parent*/
    lv_label_set_text(label, "Autonomous Selection");  /*Set the text*/
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    /*Create a normal button*/
    static lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
    lv_obj_align(btn1, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
    lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
    lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

    /*Add a label to the button*/
    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Choice 1");

    /*Copy the button and set toggled state. (The release action is copied too)*/
    static lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), btn1);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
    // lv_btn_set_state(btn2, LV_BTN_STATE_TGL_REL);  /*Set toggled state*/
    lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
    lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);

    /*Add a label to the toggled button*/
    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Choice 2");

    /*Copy the button and set inactive state.*/
    static lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), btn1);
    lv_obj_align(btn3, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 10);
    //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    lv_obj_set_free_num(btn3, 3);               /*Set a unique number for the button*/
    lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);

    /*Add a label to the inactive button*/
    label = lv_label_create(btn3, NULL);
    lv_label_set_text(label, "Choice 3");

    // /*Create a button*/
    // lv_obj_t * blueF = lv_btn_create(lv_scr_act(), NULL);         /*Create a button on the currently loaded screen*/
    // lv_btn_set_action(blueF, LV_BTN_ACTION_CLICK, blueFront); /*Set function to be called when the button is released*/
    // lv_obj_align(blueF, blueF, LV_ALIGN_OUT_BOTTOM_LEFT, 100, 35);  /*Align below the label*/
    //
    // /*Create a label on the button (the 'label' variable can be reused)*/
    // label = lv_label_create(blueF, NULL);
    // lv_label_set_text(label, "Blue Front");
    //
    // // Creates a button for the red front auton //
    // lv_obj_t * redF = lv_btn_create(lv_scr_act(), NULL);
    // lv_btn_set_action(blueF, LV_BTN_ACTION_CLICK, redFront);
    // lv_obj_align(redF, blueF, LV_ALIGN_CENTER, 150, 0);
    //
    // label = lv_label_create(redF, NULL);
    // lv_label_set_text(label, "RED FRONT");
    //
    // // Create a button for the red back auton //
    // lv_obj_t *redB = lv_btn_create(lv_scr_act(),NULL);
    // lv_btn_set_action(blueF, LV_BTN_ACTION_CLICK, redBack);
    // lv_obj_align(redB,blueF,LV_ALIGN_OUT_BOTTOM_MID,0,10);
    //
    // label = lv_label_create(redB,NULL);
    // lv_label_set_text(label,"RED BACK");
    //
    // // Create a button for the blue back auton //
    // lv_obj_t *blueB = lv_btn_create(lv_scr_act(),NULL);
    // lv_btn_set_action(blueF, LV_BTN_ACTION_CLICK, blueBack);
    // lv_obj_align(blueB,redF,LV_ALIGN_OUT_BOTTOM_MID,0,10);
    //
    // label = lv_label_create(blueB,NULL);
    // lv_label_set_text(label,"BLUE BACK");



}

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
