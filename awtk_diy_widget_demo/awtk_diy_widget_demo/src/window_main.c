#include "awtk.h"
#include "custom_widgets/triangle_button/triangle_button.h"

ret_t application_init(void);

/**
 * �ݼ���ť�¼�
 */
static ret_t on_click(void* ctx, event_t* e)
{
	widget_t* win = WIDGET(ctx);

	/* ����󵯳�һ���Ի����ʾ�Ѿ���������¼� */
	dialog_toast("on click", 1000);

	return RET_OK;
}

/**
 * �ӿؼ���ʼ��(��Ҫ������click�ص�����ʼ��ʾ��Ϣ)
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
 * ��ʼ�������ϵ��ӿؼ�
 */
static void init_children_widget(widget_t* widget)
{
	widget_foreach(widget, init_widget, widget);
}

/**
 * ��ʼ��
 */
ret_t application_init(void)
{
	/* �� triangle_button �ؼ�ע�ᵽ awtk �Ŀؼ��б��� */
	widget_factory_register(widget_factory(), WIDGET_TYPE_TRANGLE_BUTTON, triangle_button_create);

	widget_t* win = window_open("main");

	if (win)
	{
		init_children_widget(win);
	}

	return RET_OK;
}
