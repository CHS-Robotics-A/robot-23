#include "display/lv_core/lv_obj.h"
#include "display/lv_core/lv_style.h"
#include "display/lv_objx/lv_label.h"
#include "display/lvgl.h"
#include "../headers/gui/debug.hpp"

void createDisplay() {
    lv_obj_t * head;
    head = lv_label_create(lv_scr_act(), NULL);
    //set title
    lv_label_set_text(head, "Team 1516A Portal");
    //put text in middle
    lv_label_set_align(head, LV_LABEL_ALIGN_CENTER);
    //set style
    lv_label_set_style(head, &lv_style_plain_color);
    //set position
    lv_obj_align(head, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 10);
    //extend body bg
    lv_label_set_long_mode(head, LV_LABEL_LONG_BREAK);
    //set width
    lv_obj_set_width(head, 500);
    //enable body bg
    lv_label_set_body_draw(head, true);

    //create debug button
    DebugScreen::debugButton();
}
