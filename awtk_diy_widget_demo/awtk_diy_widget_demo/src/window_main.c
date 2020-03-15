#include "awtk.h"
#include "custom_widgets/triangle_button/triangle_button.h"

ret_t application_init(void);

/**
 * 递减按钮事件
 */
static ret_t on_click(void* ctx, event_t* e)
{
	widget_t* win = WIDGET(ctx);

	/* 点击后弹出一个对话框表示已经触发点击事件 */
	dialog_toast("on click", 1000);

	return RET_OK;
}

/**
 * 子控件初始化(主要是设置click回调、初始显示信息)
 */
static ret_t init_widget(void* ctx, const void* iter)
{
	(void)ctx;
	widget_t* widget = WIDGET(iter);
	widget_t* win = widget_get_window(widget);

	const char* type = widget->vt->type;
	if (tk_str_eq(type, WIDGET_TYPE_TRANGLE_BUTTON))
	{
		widget_on(widget, EVT_CLICK, on_click, win);
	}

	return RET_OK;
}

/**
 * 初始化窗口上的子控件
 */
static void init_children_widget(widget_t* widget)
{
	widget_foreach(widget, init_widget, widget);
}

/**
 * 初始化
 */
ret_t application_init(void)
{
	/* 把 triangle_button 控件注册到 awtk 的控件列表中 */
	widget_factory_register(widget_factory(), WIDGET_TYPE_TRANGLE_BUTTON, triangle_button_create);

	widget_t* win = window_open("main");

	if (win)
	{
		init_children_widget(win);
	}

	return RET_OK;
}
