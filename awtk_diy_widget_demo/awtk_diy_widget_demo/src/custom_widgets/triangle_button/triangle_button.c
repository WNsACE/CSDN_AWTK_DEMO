#include "tkc/mem.h"
#include "triangle_button.h"
#include "base/widget_vtable.h"

static ret_t triangle_button_on_paint_self(widget_t* widget, canvas_t* c)
{
	/* 不想使用默认的画图方法 */
	return RET_OK;
}

/* 因为在风格中定义了背景色，默认的 on_paint_background 函数会根据风格中的 bg_color 或者 fg_color 填充整个控件 */
/* 因为这个控件是想让按钮呈现三角形的样子，所以就选择重载 on_paint_background 函数 */
static ret_t triangle_button_on_paint_background(widget_t* widget, canvas_t* c)
{
	xy_t left_part_x = 0;
	xy_t right_part_x = 0;
	/* 获取控件风格 */
	style_t* style = widget->astyle;
	color_t trans = color_init(0, 0, 0, 0);
	vgcanvas_t* vg = canvas_get_vgcanvas(c);
	triangle_button_t* triangle_button = TRANGLE_BUTTON(widget);
	/* 获取风格中设置的 bg_color 颜色值 */
	color_t color = style_get_color(style, STYLE_ID_BG_COLOR, trans);

	return_value_if_fail(triangle_button != NULL, RET_BAD_PARAMS);


	if (color.rgba.a > 0)
	{
		if (triangle_button->is_left)
		{
			left_part_x = widget->w;
			right_part_x = 0;
		}
		else
		{
			left_part_x = 0;
			right_part_x = widget->w;
		}
		/* 保存之前 vgcanvas 的状态 */
		vgcanvas_save(vg);

		/* 使用 vgcanvas 来画出三角形的样子 */
		vgcanvas_begin_path(vg);
		/* 因为 vgcanvas 画图的坐标是绝对坐标，相对整个程序来说的 */
		/* 而 c->ox 等于控件的获取绝对坐标，y坐标同理 */
		vgcanvas_move_to(vg, c->ox + left_part_x, c->oy + widget->h / 2);
		vgcanvas_line_to(vg, c->ox + right_part_x, c->oy);
		vgcanvas_line_to(vg, c->ox + right_part_x, c->oy + widget->h);
		vgcanvas_close_path(vg);

		/* 设置填充颜色 */
		vgcanvas_set_fill_color(vg, color);
		/* 开始填充 */
		vgcanvas_fill(vg);

		/* 还原到之前 vgcanvas 的状态 */
		vgcanvas_restore(vg);
	}


	return RET_OK;
}

static ret_t triangle_button_get_prop(widget_t* widget, const char* name, value_t* v)
{
	triangle_button_t* triangle_button = TRANGLE_BUTTON(widget);
	return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

	if (tk_str_eq(name, WIDGET_PROP_IS_LEFT))
	{
		/* 获取控件中的 is_left 属性 */
		value_set_bool(v, triangle_button->is_left);
		return RET_OK;
	}

	return RET_NOT_FOUND;
}

static ret_t triangle_button_set_prop(widget_t* widget, const char* name, const value_t* v)
{
	triangle_button_t* triangle_button = TRANGLE_BUTTON(widget);
	return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

	if (tk_str_eq(name, WIDGET_PROP_IS_LEFT))
	{
		/* 根据 UI 的 xml 文件中的属性设置控件中的 is_left 属性 */
		triangle_button->is_left = value_bool(v);
		return RET_OK;
	}

	return RET_NOT_FOUND;
}

static ret_t triangle_button_on_event(widget_t* widget, event_t* e)
{
	uint16_t type = e->type;
	return_value_if_fail(widget != NULL, RET_BAD_PARAMS);

	/* 如果鼠标点击在控件上面，会设置其风格状态，让其改变 bg_color 的颜色 */
	switch (type)
	{
	case EVT_POINTER_DOWN: {
		widget_set_state(widget, WIDGET_STATE_PRESSED);
		widget_grab(widget->parent, widget);
		break;
	}
	case EVT_POINTER_DOWN_ABORT:
	case EVT_POINTER_UP:
	case EVT_POINTER_LEAVE:
		widget_set_state(widget, WIDGET_STATE_NORMAL);
		break;
	default:
		break;
	}

	return RET_OK;
}

static const char* const s_triangle_button_properties[] = { WIDGET_PROP_IS_LEFT, NULL };


const widget_vtable_t g_triangle_button_vtable = { 
.size = sizeof(triangle_button_t), /* size 成员变量是给控件开辟内存时候使用的 */
.type = WIDGET_TYPE_TRANGLE_BUTTON, /* type 用来获取风格属性用来的 */
.create = triangle_button_create,  /* 重载 create 函数指针 */
.persistent_properties = s_triangle_button_properties, /* 标记永久保存成员变量 */
.on_event = triangle_button_on_event, /* 重载 on_event 函数指针 */
.set_prop = triangle_button_set_prop, /* 重载 set_prop 函数指针 */
.get_prop = triangle_button_get_prop, /* 重载 get_prop 函数指针 */
.on_paint_self = triangle_button_on_paint_self, /* 重载 on_paint_self 函数指针 */
.on_paint_background = triangle_button_on_paint_background /* 重载 on_paint_background 函数指针 */
};

widget_t* triangle_button_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h)
{
	return widget_create(parent, &g_triangle_button_vtable, x, y, w, h);
}

widget_t* triangle_button_cast(widget_t* widget)
{
	return_value_if_fail(widget_is_instance_of(widget, &g_triangle_button_vtable), NULL);

	return widget;
}
