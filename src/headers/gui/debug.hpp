#include "display/lv_core/lv_obj.h"
#include "display/lv_core/lv_style.h"
#include "display/lv_objx/lv_label.h"
#include "display/lvgl.h"
#include <string>

class DebugScreen {

  static lv_obj_t *win;
  static lv_obj_t *text;
  static std::string internalText;

  static bool pressed;

  static void createWin();

  static lv_res_t btn_click_action(lv_obj_t *btn);

  static lv_res_t log_close_action(lv_obj_t *win);

  static lv_res_t internal_clear(lv_obj_t *btn);

  public:

  static void debugButton();
};