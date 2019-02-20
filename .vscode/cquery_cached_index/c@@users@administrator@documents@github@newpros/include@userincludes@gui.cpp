#ifndef gui_cpp
#define gui_cpp

#include "headers/gui.h"
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

  /* The button is released.
  * Make something here */

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

/*Called when a button is released ot long pressed*/
static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt)
{
  printf("Button: %s released\n", txt);

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
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

    /*Create a button descriptor string array*/
    static const char * btnm_map[] = {"RedF", "RedB", "BlueF", "BlueB", "\n",
    "RedCap", "BlueCap", "Skills1", "Skills2", ""};

    /*Create a default button matrix*/
    lv_obj_t * btnm1 = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_map(btnm1, btnm_map);
    lv_btnm_set_action(btnm1, btnm_action);
    lv_obj_set_size(btnm1, 450, 190);

    /*Create a new style for the button matrix back ground*/
    static lv_style_t style_bg;
    lv_style_copy(&style_bg, &lv_style_plain);
    style_bg.body.main_color = LV_COLOR_SILVER;
    style_bg.body.grad_color = LV_COLOR_SILVER;
    style_bg.body.padding.hor = 0;
    style_bg.body.padding.ver = 0;
    style_bg.body.padding.inner = 0;

    /*Create 2 button styles*/
    static lv_style_t style_btn_rel;
    static lv_style_t style_btn_pr;
    lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
    style_btn_rel.body.main_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);
    style_btn_rel.body.grad_color = LV_COLOR_BLACK;
    style_btn_rel.body.border.color = LV_COLOR_SILVER;
    style_btn_rel.body.border.width = 1;
    style_btn_rel.body.border.opa = LV_OPA_50;
    style_btn_rel.body.radius = 0;

    // /*Create a normal button*/
    // static lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL);
    // lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
    // lv_obj_align(btn1, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
    // lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
    // lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the button*/
    // label = lv_label_create(btn1, NULL);
    // lv_label_set_text(label, "Front Red");
    //
    // /*Copy the button and set toggled state. (The release action is copied too)*/
    // static lv_obj_t *btn2 = lv_btn_create(lv_scr_act(), btn1);
    // lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
    // // lv_btn_set_state(btn2, LV_BTN_STATE_TGL_REL);  /*Set toggled state*/
    // lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/
    // lv_btn_set_action(btn2, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the toggled button*/
    // label = lv_label_create(btn2, NULL);
    // lv_label_set_text(label, "Back Red");
    //
    // /*Copy the button and set inactive state.*/
    // static lv_obj_t *btn3 = lv_btn_create(lv_scr_act(), btn1);
    // lv_obj_align(btn3, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 10);
    // //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    // lv_obj_set_free_num(btn3, 3);               /*Set a unique number for the button*/
    // lv_btn_set_action(btn3, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the inactive button*/
    // label = lv_label_create(btn3, NULL);
    // lv_label_set_text(label, "Front Blue");
    //
    // /*Copy the button and set inactive state.*/
    // static lv_obj_t *btn4 = lv_btn_create(lv_scr_act(), btn1);
    // lv_obj_align(btn4, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 10);
    // //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    // lv_obj_set_free_num(btn4, 4);               /*Set a unique number for the button*/
    // lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the inactive button*/
    // label = lv_label_create(btn4, NULL);
    // lv_label_set_text(label, "Back Blue");
    //
    // static lv_obj_t *btn5 = lv_btn_create(lv_scr_act(), btn1);
    // lv_obj_align(btn5, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 10);
    // //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    // lv_obj_set_free_num(btn5, 5);               /*Set a unique number for the button*/
    // lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the inactive button*/
    // label = lv_label_create(btn5, NULL);
    // lv_label_set_text(label, "Skills1");
    //
    // static lv_obj_t *btn6 = lv_btn_create(lv_scr_act(), btn1);
    // lv_obj_align(btn6, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 10);
    // //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    // lv_obj_set_free_num(btn6, 6);               /*Set a unique number for the button*/
    // lv_btn_set_action(btn6, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the inactive button*/
    // label = lv_label_create(btn6, NULL);
    // lv_label_set_text(label, "Skills2");

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
