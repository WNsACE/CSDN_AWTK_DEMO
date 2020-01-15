#include "awtk.h"
#include "awtk.h"
extern ret_t application_init(void);

widget_t* label_4_btn = NULL;	//������ֵlabel�ؼ�ָ��
widget_t* label_4_edit = NULL;	//��ʾ�ı���label�ؼ�ָ��

/**
 * Label�ı�����ֵ + offset
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
 * ������ť�¼�
 */
static ret_t on_inc_click(void* ctx, event_t* e)
{
	label_add(label_4_btn, 1);

	return RET_OK;
}

/**
 * �ݼ���ť�¼�
 */
static ret_t on_dec_click(void* ctx, event_t* e)
{
	label_add(label_4_btn, -1);

	return RET_OK;
}

/**
 * ���ڱ༭�¼�
 */
static ret_t on_changing(void* ctx, event_t* evt)
{
	widget_t* target = WIDGET(evt->target);
	widget_set_text(label_4_edit, target->text.str);

	return RET_OK;
}

/**
 * ��ʼ��
 */
ret_t application_init(void)
{
	widget_t* win = window_create(NULL, 0, 0, 0, 0);

	/* �����ı���*/
	label_4_edit = label_create(win, 160, 96, 480, 40);
	widget_set_text(label_4_edit, L"hello world");
	widget_set_name(label_4_edit, "label_4_edit");

	/* �����༭�� */
	widget_t* edit = edit_create(win, 160, 196, 480, 40);
	edit_set_input_type(edit, INPUT_TEXT);
	widget_set_text(edit, L"hello world");
	widget_on(edit, EVT_VALUE_CHANGING, on_changing, NULL);

	/* �����ݼ���ť */
	widget_t* dec_btn = button_create(win, 160, 288, 160, 40);
	widget_set_text(dec_btn, L"dec");
	widget_on(dec_btn, EVT_CLICK, on_dec_click, NULL);

	/* ����label��ʾ������ֵ */
	label_4_btn = label_create(win, 320, 288, 160, 40);
	widget_set_text(label_4_btn, L"88");
	widget_set_name(label_4_btn, "label_4_btn");

	/* ����������ť */
	widget_t* inc_btn = button_create(win, 480, 288, 160, 40);
	widget_set_text(inc_btn, L"inc");
	widget_on(inc_btn, EVT_CLICK, on_inc_click, NULL);

	return RET_OK;
}
