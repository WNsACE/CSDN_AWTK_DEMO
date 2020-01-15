#include "awtk.h"
#include "awtk.h"
extern ret_t application_init(void);

widget_t* label_4_btn = NULL;	//递增数值label控件指针
widget_t* label_4_edit = NULL;	//显示文本框label控件指针

/**
 * Label文本的数值 + offset
 */
static ret_t label_add(widget_t* label, int32_t offset)
{
	if (label)
	{
		int32_t val = 0;
		if (wstr_to_int(&(label->text), &val) == RET_OK)
		{
			char text[32];
			val += offset;
			val = tk_max(-200, tk_min(val, 200));
			tk_snprintf(text, sizeof(text), "%d", val);
			widget_set_text_utf8(label, text);

			return RET_OK;
		}
	}

	return RET_FAIL;
}

/**
 * 递增按钮事件
 */
static ret_t on_inc_click(void* ctx, event_t* e)
{
	label_add(label_4_btn, 1);

	return RET_OK;
}

/**
 * 递减按钮事件
 */
static ret_t on_dec_click(void* ctx, event_t* e)
{
	label_add(label_4_btn, -1);

	return RET_OK;
}

/**
 * 正在编辑事件
 */
static ret_t on_changing(void* ctx, event_t* evt)
{
	widget_t* target = WIDGET(evt->target);
	widget_set_text(label_4_edit, target->text.str);

	return RET_OK;
}

/**
 * 初始化
 */
ret_t application_init(void)
{
	widget_t* win = window_create(NULL, 0, 0, 0, 0);

	/* 创建文本框*/
	label_4_edit = label_create(win, 160, 96, 480, 40);
	widget_set_text(label_4_edit, L"hello world");
	widget_set_name(label_4_edit, "label_4_edit");

	/* 创建编辑框 */
	widget_t* edit = edit_create(win, 160, 196, 480, 40);
	edit_set_input_type(edit, INPUT_TEXT);
	widget_set_text(edit, L"hello world");
	widget_on(edit, EVT_VALUE_CHANGING, on_changing, NULL);

	/* 创建递减按钮 */
	widget_t* dec_btn = button_create(win, 160, 288, 160, 40);
	widget_set_text(dec_btn, L"dec");
	widget_on(dec_btn, EVT_CLICK, on_dec_click, NULL);

	/* 创建label显示递增数值 */
	label_4_btn = label_create(win, 320, 288, 160, 40);
	widget_set_text(label_4_btn, L"88");
	widget_set_name(label_4_btn, "label_4_btn");

	/* 创建递增按钮 */
	widget_t* inc_btn = button_create(win, 480, 288, 160, 40);
	widget_set_text(inc_btn, L"inc");
	widget_on(inc_btn, EVT_CLICK, on_inc_click, NULL);

	return RET_OK;
}
