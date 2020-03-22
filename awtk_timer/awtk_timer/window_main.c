#include "awtk.h"
#include "awtk.h"
extern ret_t application_init(void);

// ��ʱ�� ID�����������ⲿɾ����ʱ����
uint32_t timer_id = 0;
// ��ʼʱ��
uint32_t start_time = 0;
// ������ʱ��
uint32_t anim_time = 5 * 1000;
// �ؼ� X ���ƶ���������
int32_t label_move_x_duration = 300;
// �ؼ�����߻������ұ�
bool_t is_left = FALSE;
// �ؼ��ʼ�� x ����
int32_t start_widget_x = 0;

/**
 * ��ʱ�����ƶ��ؼ��Ĵ����¼�
 */
ret_t timer_move_func(const timer_info_t* timer)
{
	easing_func_t easing;
	float_t time_percent = 0.0f;
	widget_t* label = WIDGET(timer->ctx);

	/* 
	* easing_get �������Ի�ȡ AWTK ���õ���ѧ������
	* ͨ����ѧ���������㶯�����ƶ�Ч����
	* �����������ƶ��������������һЩ��
	*/
	easing = easing_get(EASING_QUADRATIC_IN);

	/* ����ʱ����ȵİٷֱ� */
	time_percent = ((float_t)(timer->now - start_time)) / anim_time;

	if (time_percent > 1.0f)
	{
		time_percent = 1.0f;
	}

	/* �ƶ��ؼ� */
	if (is_left)
	{
		/* �ؼ�����ߵĻ����������� */
		widget_move(label, start_widget_x - easing(time_percent) * label_move_x_duration, label->y);
	}
	else
	{
		/* �ؼ����ұߵĻ����������� */
		widget_move(label, easing(time_percent) * label_move_x_duration, label->y);
	}
	
	/* ʱ���Ѿ����� */
	if (time_percent == 1.0f)
	{
		timer_id = 0;
		widget_set_text_utf8(label, "stop");
		/* ��Ȼ����Ҳ���Է��س��õ� RET_OK ���� */
		return RET_REMOVE;
	}

	widget_set_text_utf8(label, "runing");
	return RET_REPEAT;
}

/**
 * ������ʱ����ť�¼�
 */
static ret_t on_click_start_timer(void* ctx, event_t* e)
{
	widget_t* label = WIDGET(ctx);
	if (timer_id == 0)
	{
		/*
		* ÿ16���봥��һ�ζ�����һ����60֡�ƶ���Ч��������������񶯻���
		* ����������� ctx ���� label �ؼ���
		*/
		timer_id = timer_add(timer_move_func, ctx, 16);
		start_time = timer_manager()->get_time();

		/* �жϿؼ�����߻������ұ� */
		is_left = label->x > 0;
		/* ��¼�ؼ��ʼ�� x ���� */
		start_widget_x = label->x;
	}

	return RET_OK;
}

/**
 * ��ʼ��
 */
ret_t application_init(void)
{
	widget_t* win = window_create(NULL, 0, 0, 0, 0);

	/* �����ı���*/
	widget_t* label = label_create(win, 0, 0, 0, 0);
	widget_set_self_layout_params(label, "0", "m", "100", "40");
	widget_set_text(label, L"stop");

	/* ������ť */
	widget_t* button = button_create(win, 0, 0, 0, 0);
	widget_set_self_layout_params(button, "c", "b", "100", "40");
	widget_set_text_utf8(button, "start timer");
	widget_on(button, EVT_CLICK, on_click_start_timer, label);

	return RET_OK;
}
