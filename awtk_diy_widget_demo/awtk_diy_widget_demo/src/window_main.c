#include "awtk.h"
#include "custom_widgets/triangle_button/triangle_button.h"

ret_t application_init(void);

/**
 * 初始化
 */
ret_t application_init(void)
{
	/* 把 triangle_button 控件注册到 awtk 的控件列表中 */
	widget_factory_register(widget_factory(), WIDGET_TYPE_TRANGLE_BUTTON, triangle_button_create);

	widget_t* win = window_open("main");

	return RET_OK;
}
