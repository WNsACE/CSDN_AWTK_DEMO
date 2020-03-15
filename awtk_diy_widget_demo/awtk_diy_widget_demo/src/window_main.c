#include "awtk.h"
#include "custom_widgets/triangle_button/triangle_button.h"

ret_t application_init(void);

/**
 * ��ʼ��
 */
ret_t application_init(void)
{
	/* �� triangle_button �ؼ�ע�ᵽ awtk �Ŀؼ��б��� */
	widget_factory_register(widget_factory(), WIDGET_TYPE_TRANGLE_BUTTON, triangle_button_create);

	widget_t* win = window_open("main");

	return RET_OK;
}
