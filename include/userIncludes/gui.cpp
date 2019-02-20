#ifndef gui_cpp
#define gui_cpp

#include "headers/gui.h"
#include "headers/general.h"
#include "pros/llemu.hpp"
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static lv_obj_t *g_btn_region; //tab view region of the screen
static lv_obj_t *g_sb_region; //status bar region of the screen
static lv_obj_t *g_sb_label;  // sb text label
static lv_obj_t *homeLabel; // sets the text for the shome button
lv_obj_t * scr1 = lv_page_create(NULL, NULL); //creates the first screen
lv_obj_t * scr2 = lv_page_create(NULL, NULL); //creates the second screen
int auton_sel = 0; //changes when gui buttons are pressed to select auton

static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt) {

  int btn_num = atoi(txt);

  switch (btn_num) {
  case 1:
    lv_label_set_text(g_sb_label, "Red Front Auton");
    auton_sel = 1;
    lv_scr_load(scr2);
    break;
  case 2:
    lv_label_set_text(g_sb_label, "Red Back Auton");
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

  lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static lv_res_t btn_click_action(lv_obj_t * homeBtn)
{
    lv_scr_load(scr1);

    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

// static lv_res_t btn_click_action(lv_obj_t * btn)
// {
//   uint8_t id = lv_obj_get_free_num(btn);
//   lv_scr_load(scr2);
//   printf("Button %d is released", id);
//
//   return LV_RES_OK; /*Return OK if the button is not deleted*/
// }

/*Called when a button is released ot long pressed*/
// static lv_res_t btnm_action(lv_obj_t * btnm1, const char *txt)
// {
//   lv_scr_load(scr2);
//   uint8_t id = lv_obj_get_free_num(btnm1);
//   printf("Button: %s released\n", txt);
//
//   return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
// }




void firstGui(void)
{
    /********************
     * CREATE A SCREEN
     *******************/
    /* Create a new screen and load it
     * Screen can be created from any type object type
     * Now a Page is used which is an objects with scrollable content*/
     lv_scr_load(scr1);

     //Creates button_map style
     static lv_style_t style_btn_rel;
     static lv_style_t style_btn_pr;
     lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
     style_btn_rel.body.main_color = LV_COLOR_GREEN;
     style_btn_rel.body.grad_color = LV_COLOR_GREEN;
     style_btn_rel.body.border.color = LV_COLOR_BLUE;
     style_btn_rel.body.border.width = 2;
     style_btn_rel.body.border.opa = LV_OPA_50;
     style_btn_rel.body.radius = 0;

     //Creates a label style so we can see text on the dark background
     static lv_style_t style_txt;
     lv_style_copy(&style_txt, &lv_style_plain);
     style_txt.text.letter_space = 2;
     style_txt.text.line_space = 1;
     style_txt.text.color = LV_COLOR_WHITE;

     g_btn_region = lv_obj_create(lv_scr_act(), NULL);
     lv_obj_set_size(g_btn_region, lv_obj_get_width(lv_scr_act()),
         lv_obj_get_height(lv_scr_act()));
     lv_obj_align(g_btn_region, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
     lv_obj_set_style(g_btn_region, &lv_style_plain);

     //
     // g_sb_region = lv_obj_create(lv_scr_act(), NULL);
     // lv_obj_set_size(g_sb_region, lv_obj_get_width(lv_scr_act()),
     //     lv_obj_get_height(lv_scr_act()) * 0.2);
     // //set_sb_style(g_sb_region);
     // lv_obj_align(g_sb_region, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
     // lv_obj_set_style(g_sb_region, &lv_style_plain);

     g_sb_label = lv_label_create(scr2, NULL);
     lv_obj_set_style(g_sb_label, &style_txt);
     lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0);

     // Create a button descriptor string array w/ no repeat "\224"
     static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
                                        "\2244", "\2245", "\2246", "" };

     // Create a default button matrix* no repeat
     lv_obj_t *btnm = lv_btnm_create(g_btn_region, NULL);
     lv_obj_set_size(btnm, lv_obj_get_width(g_btn_region),
     lv_obj_get_height(g_btn_region));
     lv_btnm_set_style(btnm, LV_BTNM_STYLE_BG, &style_btn_rel);

     lv_btnm_set_map(btnm, btnm_map);
     lv_btnm_set_action(btnm, btnm_action);

     /*Create a normal button*/
     lv_obj_t * homeBtn = lv_btn_create(scr2, NULL);
     lv_cont_set_fit(homeBtn, true, true); /*Enable resizing horizontally and vertically*/
     lv_obj_align(homeBtn, homeLabel, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 10);
     lv_obj_set_free_num(homeBtn, 1);   /*Set a unique number for the button*/
     lv_btn_set_action(homeBtn, LV_BTN_ACTION_CLICK, btn_click_action);

     /*Add a label to the button*/
     homeLabel = lv_label_create(homeBtn, NULL);
     lv_label_set_text(homeLabel, "Home");

    /*Create a new style for the button matrix back ground*/
    // static lv_style_t style_bg;
    // lv_style_copy(&style_bg, &lv_style_plain);
    // style_bg.body.main_color = LV_COLOR_GRAY;
    // style_bg.body.grad_color = LV_COLOR_GRAY;
    // style_bg.body.border.opa = LV_OPA_TRANSP;
    // style_bg.body.padding.hor = 0;
    // style_bg.body.padding.ver = 0;
    // style_bg.body.padding.inner = 0;
    //

    //
    // /*Create a button descriptor string array*/
    // static const char * btnm_map[] = {"RedF", "RedB", "BlueF", "BlueB", "\n",
    // "RedCap", "BlueCap", "Skills1", "Skills2", ""};
    //
    // /*Create a default button matrix*/
    // lv_obj_t * btnm1 = lv_btnm_create(scr1, NULL);
    // lv_btnm_set_map(btnm1, btnm_map);
    // lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BTN_REL, &style_btn_rel);
    // lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BG, &style_bg);
    // lv_btnm_set_action(btnm1, btnm_action);
    // lv_obj_align(btnm1, btnm1, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_set_size(btnm1, 450, 190);

    // lv_obj_t * label = lv_label_create(scr1, NULL);
    // lv_label_set_text(label, "Default buttons");
    // lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
    //
    // static lv_obj_t *btn1 = lv_btn_create(scr1, NULL);
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
    // static lv_obj_t *btn2 = lv_btn_create(scr1, btn1);
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
    // static lv_obj_t *btn3 = lv_btn_create(scr1, btn1);
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
    // static lv_obj_t *btn4 = lv_btn_create(scr1, btn1);
    // lv_obj_align(btn4, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 10);
    // //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    // lv_obj_set_free_num(btn4, 4);               /*Set a unique number for the button*/
    // lv_btn_set_action(btn4, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the inactive button*/
    // label = lv_label_create(btn4, NULL);
    // lv_label_set_text(label, "Back Blue");
    //
    // static lv_obj_t *btn5 = lv_btn_create(scr1, btn1);
    // lv_obj_align(btn5, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 10);
    // //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    // lv_obj_set_free_num(btn5, 5);               /*Set a unique number for the button*/
    // lv_btn_set_action(btn5, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the inactive button*/
    // label = lv_label_create(btn5, NULL);
    // lv_label_set_text(label, "Skills1");
    //
    // static lv_obj_t *btn6 = lv_btn_create(scr1, btn1);
    // lv_obj_align(btn6, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 10);
    // //lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    // lv_obj_set_free_num(btn6, 6);               /*Set a unique number for the button*/
    // lv_btn_set_action(btn6, LV_BTN_ACTION_CLICK, btn_click_action);
    //
    // /*Add a label to the inactive button*/
    // label = lv_label_create(btn6, NULL);
    // lv_label_set_text(label, "Skills2");
    //


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

#endif
