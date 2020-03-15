#ifndef TK_TRANGLE_BUTTON_H
#define TK_TRANGLE_BUTTON_H

#include "base/widget.h"

BEGIN_C_DECLS

typedef struct _triangle_button_t {
  widget_t widget;
  /* 标记三角形向左还是向右 */
  bool_t is_left;
  /* 标记按钮是否按下 */
  bool_t pressed;
} triangle_button_t;

/**
 * @method triangle_button_create
 * 创建triangle_button对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* triangle_button_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method triangle_button_cast
 * 转换为triangle_button对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget triangle_button对象。
 *
 * @return {widget_t*} triangle_button对象。
 */
widget_t* triangle_button_cast(widget_t* widget);

#define WIDGET_TYPE_TRANGLE_BUTTON "triangle_button"
#define WIDGET_PROP_IS_LEFT "is_left"

#define TRANGLE_BUTTON(widget) ((triangle_button_t*)(widget))

END_C_DECLS

#endif /*TK_TRANGLE_BUTTON_H*/
