#ifndef gui_cpp
#define gui_cpp

#include "headers/gui.h"
#include "headers/general.h"
#include "pros/llemu.hpp"
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static lv_obj_t *g_sb_label;  // sb text label
static lv_obj_t *g_auton_region; //tab view region of the screen
static lv_obj_t *autonLabel; // sets the text for the auton leftButton
static lv_obj_t *leftLabel; //sets label for left auton switcher
static lv_obj_t *rightLabel; //sets label for right auton switcher
static lv_obj_t *autonTxt;
lv_obj_t * scr1 = lv_page_create(NULL, NULL); //creates the first screen
lv_obj_t * scr2 = lv_page_create(NULL, NULL); //creates the second screen
int auton_sel = 1; //changes when gui buttons are pressed to select auton, defaults to first auton

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt) {

  int btn_num = atoi(txt);

  switch (btn_num) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
    auton_sel = 1;
    lv_scr_load(scr2);
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Back Auton");
    lv_label_set_text(autonTxt,
      "If a line become too long it can be automatically broken into multiple lines");
    auton_sel = 2;
    lv_scr_load(scr2);
    break;
  case 3:
    lv_label_set_text(g_sb_label, "Blue Front Auton");
    auton_sel = 3;
    lv_scr_load(scr2);
    break;
  case 4:
    lv_label_set_text(g_sb_label, "Blue Back Auton");
    auton_sel = 4;
    lv_scr_load(scr2);
    break;
  case 5:
    lv_label_set_text(g_sb_label, "Skills Auton1");
    auton_sel = 5;
    lv_scr_load(scr2);
    break;
  case 6:
    lv_label_set_text(g_sb_label, "Skills Auton2");
    auton_sel = 6;
    lv_scr_load(scr2);
    break;
  }

  lv_obj_set_y(g_sb_label, 200); // must be after set_text

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static lv_res_t btn_click_action(lv_obj_t * autonBtn)
{
    lv_scr_load(scr1); //returns to screen 1 after the auton button is pressed
    // lv_obj_set_pos(autonBtn, 325, 300); //fixes problem where button rises after going and selecting new auton

    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t left(lv_obj_t * rightButton)
{

  if (auton_sel == 1)
  {
    auton_sel = 6;
  }
  else
  {
    auton_sel--;
  }

  switch (auton_sel) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Back Auton");
    lv_label_set_text(autonTxt,
      "If a line become too long it can be automatically broken into multiple lines");
    break;
  case 3:
    lv_label_set_text(g_sb_label, "Blue Front Auton");
    break;
  case 4:
    lv_label_set_text(g_sb_label, "Blue Back Auton");
    break;
  case 5:
    lv_label_set_text(g_sb_label, "Skills Auton1");
    break;
  case 6:
    lv_label_set_text(g_sb_label, "Skills Auton2");
    break;
  }

  // lv_obj_set_pos(rightButton, 305, 200);

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

static lv_res_t right(lv_obj_t * leftButton)
{

  if (auton_sel == 6)
  {
    auton_sel = 1;
  }
  else
  {
    auton_sel++;
  }

  switch (auton_sel) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Front Auton");
    lv_label_set_text(autonTxt, "Gets ball from cap by platforms\n"
     "Backs up and shoots top and middle flags\n"
     "Drives Forward and turns bottom flag\n"
     "Backs up, turns, and flips the cap by the flags");
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Back Auton");
    lv_label_set_text(autonTxt,
      "If a line become too long it can be automatically broken into multiple lines");
    break;
  case 3:
    lv_label_set_text(g_sb_label, "Blue Front Auton");
    break;
  case 4:
    lv_label_set_text(g_sb_label, "Blue Back Auton");
    break;
  case 5:
    lv_label_set_text(g_sb_label, "Skills Auton1");
    break;
  case 6:
    lv_label_set_text(g_sb_label, "Skills Auton2");
    break;
  }

  // lv_obj_set_pos(leftButton, 95, 200);

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}


void firstGui(void)
{
    // Create a new screen and load it
     lv_scr_load(scr1);

     //Creates button styles
     static lv_style_t style_btn_rel;
     static lv_style_t style_btn_pr;
     static lv_style_t toggle_btn_rel;
     static lv_style_t toggle_btn_pr;

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
     style_btn_pr.body.border.width = 2;
     style_btn_pr.body.border.opa = LV_OPA_100;
     style_btn_pr.body.radius = 5;

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

     g_auton_region = lv_obj_create(lv_scr_act(), NULL);
     lv_obj_set_size(g_auton_region, lv_obj_get_width(lv_scr_act()),
         lv_obj_get_height(lv_scr_act()) * 0.8);
     lv_obj_set_pos(g_auton_region, 150, 200);
     lv_obj_set_style(g_auton_region, &lv_style_plain);

     g_sb_label = lv_label_create(scr2, NULL);
     lv_obj_set_style(g_sb_label, &style_txt);
     lv_obj_set_x(g_sb_label, 150);


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
     toggle_btn_pr.body.border.width = 2;
     toggle_btn_pr.body.border.opa = LV_OPA_50;
     toggle_btn_pr.body.radius = 5;

     /*Create a normal button*/
     lv_obj_t * autonBtn = lv_btn_create(scr2, NULL);
     lv_btn_set_style(autonBtn, LV_BTN_STYLE_REL, &style_btn_rel);
     lv_btn_set_style(autonBtn, LV_BTN_STYLE_PR, &style_btn_pr);
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
     lv_label_set_text(leftLabel, "<");

     lv_obj_t * rightButton = lv_btn_create(scr2, NULL);
     lv_obj_set_width(rightButton, 50);
     lv_obj_set_height(rightButton, 50);
     lv_btn_set_style(rightButton, LV_BTN_STYLE_REL, &toggle_btn_rel);
     lv_btn_set_style(rightButton, LV_BTN_STYLE_PR, &toggle_btn_pr);
     lv_btn_set_action(rightButton, LV_BTN_ACTION_CLICK, right);
     lv_obj_set_pos(rightButton, 305, 200);

     rightLabel = lv_label_create(rightButton, NULL);
     lv_label_set_text(rightLabel, ">");

     /*Create a new label*/
     autonTxt = lv_label_create(scr2, NULL);
     lv_obj_set_style(autonTxt, &style_txt);                    /*Set the created style*/
     lv_label_set_long_mode(autonTxt, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
     lv_label_set_recolor(autonTxt, true);                      /*Enable re-coloring by commands in the text*/
     lv_label_set_align(autonTxt, LV_LABEL_ALIGN_LEFT);       /*Center aligned lines*/
     lv_obj_set_width(autonTxt, 300);                           /*Set a width*/
     lv_obj_set_pos(autonTxt, 0, 250);

}

#endif
