#ifndef gui_cpp
#define gui_cpp

#include "headers/gui.h"
#include "headers/general.h"
#include "pros/llemu.hpp"
#include "pollSensors.cpp"
#include "main.h"
#include "display/lv_misc/lv_task.h"
#include "robotFunction.cpp"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static lv_obj_t *g_sb_label;  // sb text label
static lv_obj_t *g_auton_region; //tab view region of the screen
static lv_obj_t *autonLabel; // sets the text for the auton leftButton
static lv_obj_t *leftLabel; //sets label for left auton switcher
static lv_obj_t *rightLabel; //sets label for right auton switcher
static lv_obj_t *autonTxt;
static lv_obj_t *confirmTxt;
static lv_obj_t *gyroValue;
static lv_obj_t *gyroResetLbl;
static lv_obj_t *returnTxt;
static lv_obj_t *runAutonTxt;
lv_obj_t * scr1 = lv_page_create(NULL, NULL); //creates the first screen
lv_obj_t * scr2 = lv_page_create(NULL, NULL); //creates the second screen
lv_obj_t * scr3 = lv_page_create(NULL, NULL); //creates the third screen
int auton_sel = 1; //changes when gui buttons are pressed to select auton, defaults to first auton
int position = 0;
int color;
bool gyro = 0;

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt) {

  int btn_num = atoi(txt);

  static lv_style_t red;
  lv_style_copy(&red, &lv_style_scr);
  red.body.main_color = LV_COLOR_RED;
  red.body.grad_color = LV_COLOR_RED;
  red.body.border.color = LV_COLOR_RED;

  static lv_style_t blue;
  lv_style_copy(&blue, &lv_style_scr);
  blue.body.main_color = LV_COLOR_BLUE;
  blue.body.grad_color = LV_COLOR_BLUE;
  blue.body.border.color = LV_COLOR_BLUE;

  switch (btn_num) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
    auton_sel = 1;
    lv_obj_set_style(scr3, &red);
    lv_scr_load(scr2);
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Back Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
      "Turns and shoots top middle flag\n"
      "Turns and parks on alliance platform");
    auton_sel = 2;
    lv_obj_set_style(scr3, &red);
    lv_scr_load(scr2);
    break;
  case 3:
    lv_label_set_text(g_sb_label, "Blue Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
    auton_sel = 3;
    lv_obj_set_style(scr3, &blue);
    lv_scr_load(scr2);
    break;
  case 4:
    lv_label_set_text(g_sb_label, "Blue Back Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
      "Turns and shoots top middle flag\n"
      "Turns and parks on alliance platform");
    auton_sel = 4;
    lv_obj_set_style(scr3, &blue);
    lv_scr_load(scr2);
    break;
  case 5:
    lv_label_set_text(g_sb_label, "Skills Auton1");
    lv_label_set_text(autonTxt, "");
    auton_sel = 5;
    lv_obj_set_style(scr3, &red);
    lv_scr_load(scr2);
    break;
  case 6:
    lv_label_set_text(g_sb_label, "Skills Auton2");
    lv_label_set_text(autonTxt, "");
    auton_sel = 6;
    lv_obj_set_style(scr3, &red);
    lv_scr_load(scr2);
    break;
  }

  if (position == 0) //looks for 0 which is the starting value so the loop only runs the very first time an auton is selected from the first scr
  {
    lv_obj_set_pos(g_auton_region, 150, 200); //helps place the text in the right position for the first time
    position ++; //ensures that this loop will never be run again, was having problems after returning to the main scr to select a new auton
                //and I found that after the set_pos ran for the second time the text was moved to a different location on the scr
  }
  else //returns nothing when int position is larger than zero which will happen after the first run
  {
  }

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static lv_res_t btn_click_action(lv_obj_t * autonBtn)
{
    lv_scr_load(scr1); //returns to screen 1 after the auton button is pressed


    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t left(lv_obj_t * rightButton)
{

  static lv_style_t red;
  lv_style_copy(&red, &lv_style_scr);
  red.body.main_color = LV_COLOR_RED;
  red.body.grad_color = LV_COLOR_RED;
  red.body.border.color = LV_COLOR_RED;

  static lv_style_t blue;
  lv_style_copy(&blue, &lv_style_scr);
  blue.body.main_color = LV_COLOR_BLUE;
  blue.body.grad_color = LV_COLOR_BLUE;
  blue.body.border.color = LV_COLOR_BLUE;

  if (auton_sel == 1) //if rolling list reaches 1, the last value, it will run this loop
  {
    auton_sel = 6; //the value is set back to the top so the list appears to forever be able to scroll through
  }
  else
  {
    auton_sel--; //if the list is not at the bottom, then the int will have 1 taken off each click
  }

  switch (auton_sel) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
     lv_obj_set_style(scr3, &red);
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Back Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
      "Turns and shoots top middle flag\n"
      "Turns and parks on alliance platform");
      lv_obj_set_style(scr3, &red);
    break;
  case 3:
    lv_label_set_text(g_sb_label, "Blue Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
     lv_obj_set_style(scr3, &blue);
    break;
  case 4:
    lv_label_set_text(g_sb_label, "Blue Back Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
      "Turns and shoots top middle flag\n"
      "Turns and parks on alliance platform");
      lv_obj_set_style(scr3, &blue);
    break;
  case 5:
    lv_label_set_text(g_sb_label, "Skills Auton1");
    lv_label_set_text(autonTxt, "");
    lv_obj_set_style(scr3, &red);
    break;
  case 6:
    lv_label_set_text(g_sb_label, "Skills Auton2");
    lv_label_set_text(autonTxt, "");
    lv_obj_set_style(scr3, &red);
    break;
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t right(lv_obj_t * leftButton)
{

  static lv_style_t red;
  lv_style_copy(&red, &lv_style_scr);
  red.body.main_color = LV_COLOR_RED;
  red.body.grad_color = LV_COLOR_RED;
  red.body.border.color = LV_COLOR_RED;

  static lv_style_t blue;
  lv_style_copy(&blue, &lv_style_scr);
  blue.body.main_color = LV_COLOR_BLUE;
  blue.body.grad_color = LV_COLOR_BLUE;
  blue.body.border.color = LV_COLOR_BLUE;

  if (auton_sel == 6) //if int is at 6 it has reached the top value of the list
  {
    auton_sel = 1; //it will reset to the bottom by making the int 1 and create an infinite scroll
  }
  else
  {
    auton_sel++; //if list is not at the top, will add 1 to int every click
  }

  switch (auton_sel) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
     lv_obj_set_style(scr3, &red);
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Back Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
      "Turns and shoots top middle flag\n"
      "Turns and parks on alliance platform");
      lv_obj_set_style(scr3, &red);
    break;
  case 3:
    lv_label_set_text(g_sb_label, "Blue Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
     lv_obj_set_style(scr3, &blue);
    break;
  case 4:
    lv_label_set_text(g_sb_label, "Blue Back Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
      "Turns and shoots top middle flag\n"
      "Turns and parks on alliance platform");
      lv_obj_set_style(scr3, &blue);
    break;
  case 5:
    lv_label_set_text(g_sb_label, "Skills Auton1");
    lv_label_set_text(autonTxt, "");
    lv_obj_set_style(scr3, &red);
    break;
  case 6:
    lv_label_set_text(g_sb_label, "Skills Auton2");
    lv_label_set_text(autonTxt, "");
    lv_obj_set_style(scr3, &red);
    break;
  }

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t confirm(lv_obj_t * confirmBtn)//when the confirm button is pressed
{

  lv_scr_load(scr3);//loads the third scr
  gyro = 1;//sets bool to true so the live gyro values will start showing

  return LV_RES_OK;
}

static lv_res_t gyroReset(lv_obj_t * gyroResetBtn)//when gyro reset button is pressed
{

  resetGyro();//runs the reset gyro function so robot can be readjusted and gyro then rezeroed

  return LV_RES_OK;
}

static lv_res_t returnToScr2(_lv_obj_t *returnBtn)
{

  lv_scr_load(scr2);

  return LV_RES_OK;
}

static lv_res_t runAuton(_lv_obj_t *runAutonBtn)
{

  autonomous(); //runs selected auton when the button is pressed

  return LV_RES_OK;
}

void label_refresher_gyro(void * p) //begins the loop that will autoupdate the gyro value label
{
  static uint32_t prev_value = 0;

  if(prev_value != getGyroSensor())
  {
    if(lv_obj_get_screen(gyroValue) == scr3)
    {
      char buf[32];
      sprintf(buf, "Gyro: %d", int(getGyroSensor()));
      lv_label_set_text(gyroValue, buf);
    }
    prev_value = getGyroSensor();
  }
}

void label_refresher_left_drive(void * p) //begins the loop that will autoupdate the gyro value label
{
  static uint32_t prev_value = 0;

  if(prev_value != getGyroSensor())
  {
    if(lv_obj_get_screen(gyroValue) == scr3)
    {
      char buf[32];
      sprintf(buf, "Gyro: %d", int(getGyroSensor()));
      lv_label_set_text(gyroValue, buf);
    }
    prev_value = getGyroSensor();
  }
}

void label_refresher_right_drive(void * p) //begins the loop that will autoupdate the gyro value label
{
    static uint32_t prev_value = 0; //creates a new value

    if(prev_value != getRawGyro()) //looks if created value is not equal to the gyro's value
    {
        if(lv_obj_get_screen(gyroValue) == scr3) //if label is on scr3
        {
            char buf[32];
            sprintf(buf, "Gyro: %d", int(getRawGyro()));
            lv_label_set_text(gyroValue, buf);
        }
        prev_value = getRawGyro();
    }
}

void gui(void)
{
    // Create a new screen and load it
     lv_scr_load(scr1);

     //Creates button styles
     static lv_style_t style_btn_rel;
     static lv_style_t style_btn_pr;
     static lv_style_t toggle_btn_rel;
     static lv_style_t toggle_btn_pr;
     static lv_style_t confirm_btn_rel;
     static lv_style_t confirm_btn_pr;
     static lv_style_t rezero_btn_rel;
     static lv_style_t rezero_btn_pr;

     lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
     //sets the style for when the button is not pressed
     style_btn_rel.body.main_color = LV_COLOR_GREEN;
     style_btn_rel.body.grad_color = LV_COLOR_GREEN;
     style_btn_rel.body.border.color = LV_COLOR_BLUE;
     style_btn_rel.body.border.width = 2;
     style_btn_rel.body.border.opa = LV_OPA_50;
     style_btn_rel.body.radius = 5;

     lv_style_copy(&style_btn_pr, &style_btn_rel);
     //sets the style for when the button is pressed
     style_btn_pr.body.main_color = LV_COLOR_BLUE;
     style_btn_pr.body.grad_color = LV_COLOR_BLUE;
     style_btn_pr.body.border.color = LV_COLOR_GREEN;
     style_btn_pr.body.border.opa = LV_OPA_100;

     /*Creates a new style for the button matrix back ground to be transparent*/
     static lv_style_t style_bg;
     lv_style_copy(&style_bg, &lv_style_plain);
     style_bg.body.empty = true;
     style_bg.body.border.opa = LV_OPA_TRANSP; //makes border transparent as well

     //Creates a label style so we can see text on the dark background
     static lv_style_t style_txt;
     lv_style_copy(&style_txt, &lv_style_plain);
     style_txt.text.letter_space = 2;
     style_txt.text.line_space = 1;
     style_txt.text.color = LV_COLOR_WHITE;

     // Create a button descriptor string array w/ no repeat "\224"
     static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
                                        "\2244", "\2245", "\2246", "" };

     // Create a default button matrix* no repeat
     lv_obj_t *btnm = lv_btnm_create(scr1, NULL);
     lv_obj_set_size(btnm, 450, 190);
     lv_btnm_set_style(btnm, LV_BTNM_STYLE_BG, &style_bg);
     lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_REL, &style_btn_rel);
     lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_PR, &style_btn_pr);

     lv_btnm_set_map(btnm, btnm_map);
     lv_btnm_set_action(btnm, btnm_action);

     g_auton_region = lv_cont_create(scr2, NULL);
     lv_obj_set_protect(g_auton_region, LV_PROTECT_POS);
     lv_cont_set_fit(g_auton_region, true, true);
     lv_obj_set_pos(g_auton_region, 150, 200);
     lv_obj_set_style(g_auton_region, &style_bg);

     g_sb_label = lv_label_create(g_auton_region, NULL);
     lv_obj_set_protect(g_sb_label, LV_PROTECT_POS);
     lv_obj_set_style(g_sb_label, &style_txt);
     lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0);


     lv_style_copy(&toggle_btn_rel, &lv_style_plain);
     //sets the style for when the button is not pressed
     toggle_btn_rel.body.main_color = LV_COLOR_SILVER;
     toggle_btn_rel.body.grad_color = LV_COLOR_SILVER;
     toggle_btn_rel.body.border.color = LV_COLOR_NAVY;
     toggle_btn_rel.body.border.width = 2;
     toggle_btn_rel.body.border.opa = LV_OPA_50;
     toggle_btn_rel.body.radius = 5;

     lv_style_copy(&toggle_btn_pr, &toggle_btn_rel);
     //sets the style for when the button is pressed
     toggle_btn_pr.body.main_color = LV_COLOR_NAVY;
     toggle_btn_pr.body.grad_color = LV_COLOR_NAVY;
     toggle_btn_pr.body.border.color = LV_COLOR_SILVER;

     /*Create a normal button*/
     lv_obj_t * autonBtn = lv_btn_create(scr2, NULL);
     lv_btn_set_style(autonBtn, LV_BTN_STYLE_REL, &style_btn_rel);
     lv_btn_set_style(autonBtn, LV_BTN_STYLE_PR, &style_btn_pr);
     lv_obj_set_protect(autonBtn, LV_PROTECT_POS);
     lv_cont_set_fit(autonBtn, true, true); /*Enable resizing horizontally and vertically*/
     lv_btn_set_action(autonBtn, LV_BTN_ACTION_CLICK, btn_click_action);
     lv_obj_set_pos(autonBtn, 325, 300);

     /*Add a label to the button*/
     autonLabel = lv_label_create(autonBtn, NULL);
     lv_label_set_text(autonLabel, "Autons");

     lv_obj_t * leftButton = lv_btn_create(scr2, NULL);
     lv_obj_set_width(leftButton, 50);
     lv_obj_set_height(leftButton, 50);
     lv_btn_set_style(leftButton, LV_BTN_STYLE_REL, &toggle_btn_rel);
     lv_btn_set_style(leftButton, LV_BTN_STYLE_PR, &toggle_btn_pr);
     lv_btn_set_action(leftButton, LV_BTN_ACTION_CLICK, left);
     lv_obj_set_pos(leftButton, 95, 200); //y-pos must be 200 to prevent other objects from shifting

     leftLabel = lv_label_create(leftButton, NULL);
     lv_label_set_text(leftLabel, SYMBOL_LEFT);

     lv_obj_t * rightButton = lv_btn_create(scr2, NULL);
     lv_obj_set_width(rightButton, 50);
     lv_obj_set_height(rightButton, 50);
     lv_btn_set_style(rightButton, LV_BTN_STYLE_REL, &toggle_btn_rel);
     lv_btn_set_style(rightButton, LV_BTN_STYLE_PR, &toggle_btn_pr);
     lv_btn_set_action(rightButton, LV_BTN_ACTION_CLICK, right);
     lv_obj_set_pos(rightButton, 320, 200);

     rightLabel = lv_label_create(rightButton, NULL);
     lv_label_set_text(rightLabel, SYMBOL_RIGHT);

     /*Create a new label*/
     autonTxt = lv_label_create(scr2, NULL);
     lv_obj_set_style(autonTxt, &style_txt);                    /*Set the created style*/
     lv_label_set_long_mode(autonTxt, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
     lv_label_set_recolor(autonTxt, true);                      /*Enable re-coloring by commands in the text*/
     lv_label_set_align(autonTxt, LV_LABEL_ALIGN_LEFT);       /*Left aligned lines*/
     lv_obj_set_width(autonTxt, 300);                           /*Set a width*/
     lv_obj_set_pos(autonTxt, 0, 255);
     lv_obj_set_protect(autonTxt, LV_PROTECT_POS);

     lv_style_copy(&confirm_btn_rel, &lv_style_plain);
     //sets the style for when the button is not pressed
     confirm_btn_rel.body.main_color = LV_COLOR_RED;
     confirm_btn_rel.body.grad_color = LV_COLOR_YELLOW;
     confirm_btn_rel.body.border.color = LV_COLOR_SILVER;
     confirm_btn_rel.body.border.width = 2;
     confirm_btn_rel.body.border.opa = LV_OPA_50;
     confirm_btn_rel.body.radius = 5;

     lv_style_copy(&confirm_btn_pr, &confirm_btn_rel);
     //sets the style for when the button is pressed
     confirm_btn_pr.body.main_color = LV_COLOR_YELLOW;
     confirm_btn_pr.body.grad_color = LV_COLOR_RED;

     lv_obj_t * confirmBtn = lv_btn_create(scr2, NULL);
     lv_obj_set_width(confirmBtn, 50);
     lv_obj_set_height(confirmBtn, 50);
     lv_btn_set_style(confirmBtn, LV_BTN_STYLE_REL, &confirm_btn_rel);
     lv_btn_set_style(confirmBtn, LV_BTN_STYLE_PR, &confirm_btn_pr);
     lv_btn_set_action(confirmBtn, LV_BTN_ACTION_CLICK, confirm);
     lv_obj_set_protect(confirmBtn, LV_PROTECT_POS);
     lv_obj_set_pos(confirmBtn, 400, 200);

     confirmTxt = lv_label_create(confirmBtn, NULL);
     lv_label_set_text(confirmTxt, SYMBOL_OK);

     gyroValue = lv_label_create(scr3, NULL);
     lv_obj_set_pos(gyroValue, 10, 0);
     lv_obj_set_style(gyroValue, &style_txt);
     lv_task_create(label_refresher_gyro, 100, LV_TASK_PRIO_MID, NULL);

     lv_style_copy(&rezero_btn_rel, &lv_style_plain);
     //sets the style for when the button is not pressed
     rezero_btn_rel.body.main_color = LV_COLOR_BLACK;
     rezero_btn_rel.body.grad_color = LV_COLOR_BLACK;
     rezero_btn_rel.body.border.color = LV_COLOR_WHITE;
     rezero_btn_rel.body.border.width = 2;
     rezero_btn_rel.body.border.opa = LV_OPA_50;
     rezero_btn_rel.body.radius = 5;

     lv_style_copy(&rezero_btn_pr, &rezero_btn_rel);
     //sets the style for when the button is not pressed
     rezero_btn_pr.body.main_color = LV_COLOR_GRAY;
     rezero_btn_pr.body.grad_color = LV_COLOR_GRAY;

     lv_obj_t * gyroResetBtn = lv_btn_create(scr3, NULL);
     lv_obj_set_height(gyroResetBtn, 40);
     lv_btn_set_style(gyroResetBtn, LV_BTN_STYLE_REL, &rezero_btn_rel);
     lv_btn_set_style(gyroResetBtn, LV_BTN_STYLE_PR, &rezero_btn_pr);
     lv_btn_set_action(gyroResetBtn, LV_BTN_ACTION_CLICK, gyroReset);
     lv_obj_set_protect(gyroResetBtn, LV_PROTECT_POS);
     lv_obj_set_pos(gyroResetBtn, 325, 15);

     gyroResetLbl = lv_label_create(gyroResetBtn, NULL);
     lv_label_set_text(gyroResetLbl, "Zero Gyro");
     lv_obj_set_style(gyroResetLbl, &style_txt);

     lv_obj_t * returnBtn = lv_btn_create(scr3, NULL);
     lv_obj_set_width(returnBtn, 50);
     lv_obj_set_height(returnBtn, 50);
     lv_btn_set_style(returnBtn, LV_BTN_STYLE_REL, &rezero_btn_rel);
     lv_btn_set_style(returnBtn, LV_BTN_STYLE_PR, &rezero_btn_pr);
     lv_btn_set_action(returnBtn, LV_BTN_ACTION_CLICK, returnToScr2);
     lv_obj_set_protect(returnBtn, LV_PROTECT_POS);
     lv_obj_set_pos(returnBtn, 400, 170);

     returnTxt = lv_label_create(returnBtn, NULL);
     lv_label_set_text(returnTxt, SYMBOL_LEFT);
     lv_obj_set_style(returnTxt, &style_txt);

     lv_obj_t * runAutonBtn = lv_btn_create(scr3, NULL);
     lv_cont_set_fit(runAutonBtn, true, false); //allows width to fit label but set the height
     lv_obj_set_height(runAutonBtn, 50);
     lv_btn_set_style(runAutonBtn, LV_BTN_STYLE_REL, &rezero_btn_rel);
     lv_btn_set_style(runAutonBtn, LV_BTN_STYLE_PR, &rezero_btn_pr);
     lv_btn_set_action(runAutonBtn, LV_BTN_ACTION_CLICK, runAuton);
     lv_obj_set_protect(runAutonBtn, LV_PROTECT_POS);
     lv_obj_set_pos(runAutonBtn, 0, 170);

     runAutonTxt = lv_label_create(runAutonBtn, NULL);
     lv_label_set_text(runAutonTxt, "Run Auton");
     lv_obj_set_style(runAutonTxt, &style_txt);

}

#endif
