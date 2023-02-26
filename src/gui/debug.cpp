#include "../headers/gui/debug.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_core/lv_style.h"
#include "display/lv_misc/lv_symbol_def.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_label.h"
#include "display/lv_objx/lv_win.h"
#include "display/lvgl.h"
#include <cstdio>
#include <memory>

lv_obj_t *DebugScreen::win;

lv_obj_t *DebugScreen::text;

std::string DebugScreen::internalText;

bool DebugScreen::pressed;

void DebugScreen::createWin() {
    /*Create a scroll bar style*/;
    static lv_style_t style_sb;
    lv_style_copy(&style_sb, &lv_style_plain_color);
    style_sb.body.main_color = LV_COLOR_BLACK;
    style_sb.body.grad_color = LV_COLOR_BLACK;
    style_sb.body.border.color = LV_COLOR_WHITE;
    style_sb.body.border.width = 5;
    style_sb.body.border.opa = LV_OPA_70;
    style_sb.body.radius = LV_RADIUS_CIRCLE;
    style_sb.body.opa = LV_OPA_60;

    static lv_style_t style_head;
    lv_style_copy(&style_head, &lv_style_plain_color);
    style_head.body.border.width = 0;
    

    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Debug Log");
    lv_obj_set_hidden(win, true);
    lv_win_set_style(win, LV_WIN_STYLE_SB, &style_sb); 
    lv_win_set_style(win, LV_WIN_STYLE_HEADER, &style_head);    
    lv_win_set_style(win, LV_WIN_STYLE_BG, &lv_style_plain);
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);
    lv_win_set_sb_mode(win, LV_SB_MODE_AUTO);

    lv_win_add_btn(win, SYMBOL_CLOSE, log_close_action);
    lv_win_add_btn(win, SYMBOL_TRASH, internal_clear);
    lv_win_set_btn_size(win, 30);


    text = lv_label_create(win, NULL);
    lv_label_set_style(win, &lv_style_plain_color);
    lv_label_set_long_mode(text, LV_LABEL_LONG_EXPAND);
    lv_obj_align(text, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_label_set_text(text, "1516A Terminal");
    lv_label_set_align(text, LV_LABEL_ALIGN_LEFT);
    lv_obj_set_width(text, lv_win_get_width(win));



}

lv_res_t DebugScreen::internal_clear(lv_obj_t *btn) {
    internalText = "";
    lv_label_set_text(text, "");
    return LV_RES_OK;
};

lv_res_t DebugScreen::log_close_action(lv_obj_t *btn) {
    lv_obj_t* localWin = lv_win_get_from_btn(btn);
    lv_obj_set_hidden(localWin, true);
    return LV_RES_OK;
};

lv_res_t DebugScreen::btn_click_action(lv_obj_t *btn) {
  uint8_t id = lv_obj_get_free_num(btn);
    lv_obj_set_hidden(win, false);
    printf("Button %d is released\n", id);

  return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void DebugScreen::debugButton() {

  lv_obj_t *dbg;
  dbg = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(dbg, 150, 40);
  // lv_btn_set_style(dbg, LV_BTN_STYLE_TGL_REL, &lv_style_plain_color);
  lv_obj_align(dbg, NULL, LV_ALIGN_IN_LEFT_MID, 40, 15);
  lv_btn_set_toggle(dbg, true);
  lv_obj_set_free_num(dbg, 1);
  lv_btn_set_action(dbg, LV_BTN_ACTION_CLICK, btn_click_action);

  lv_obj_t *debugText;
  debugText = lv_label_create(dbg, NULL);
  lv_label_set_text(debugText, "Debug Log");
  lv_label_set_style(debugText, &lv_style_plain_color);

  if (win == nullptr)
    createWin();
}
