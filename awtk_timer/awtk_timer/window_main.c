#include "awtk.h"
#include "awtk.h"
extern ret_t application_init(void);

// 计时器 ID，可以用来外部删除计时器。
uint32_t timer_id = 0;
// 开始时间
uint32_t start_time = 0;
// 动画总时长
uint32_t anim_time = 5 * 1000;
// 控件 X 轴移动的最大距离
int32_t label_move_x_duration = 300;
// 控件在左边还是在右边
bool_t is_left = FALSE;
// 控件最开始的 x 坐标
int32_t start_widget_x = 0;

/**
 * 计时器中移动控件的触发事件
 */
ret_t timer_move_func(const timer_info_t* timer)
{
	easing_func_t easing;
	float_t time_percent = 0.0f;
	widget_t* label = WIDGET(timer->ctx);

	/* 
	* easing_get 函数可以获取 AWTK 内置的数学函数，
	* 通过数学函数来计算动画的移动效果，
	* 这样可以让移动看起来更加舒服一些。
	*/
	easing = easing_get(EASING_QUADRATIC_IN);

	/* 计算时间进度的百分比 */
	time_percent = ((float_t)(timer->now - start_time)) / anim_time;

	if (time_percent > 1.0f)
	{
		time_percent = 1.0f;
	}

	/* 移动控件 */
	if (is_left)
	{
		/* 控件在左边的话，就往右移 */
		widget_move(label, start_widget_x - easing(time_percent) * label_move_x_duration, label->y);
	}
	else
	{
		/* 控件在右边的话，就往左移 */
		widget_move(label, easing(time_percent) * label_move_x_duration, label->y);
	}
	
	/* 时间已经到了 */
	if (time_percent == 1.0f)
	{
		timer_id = 0;
		widget_set_text_utf8(label, "stop");
		/* 当然这里也可以返回常用的 RET_OK 类型 */
		return RET_REMOVE;
	}

	widget_set_text_utf8(label, "runing");
	return RET_REPEAT;
}

/**
 * 开启计时器按钮事件
 */
static ret_t on_click_start_timer(void* ctx, event_t* e)
{
	widget_t* label = WIDGET(ctx);
	if (timer_id == 0)
	{
		/*
		* 每16毫秒触发一次动画，一秒有60帧移动的效果，这样看起就像动画了
		* 这里的上下文 ctx 就是 label 控件。
		*/
		timer_id = timer_add(timer_move_func, ctx, 16);
		start_time = timer_manager()->get_time();

		/* 判断控件在左边还是在右边 */
		is_left = label->x > 0;
		/* 记录控件最开始的 x 坐标 */
		start_widget_x = label->x;
	}

	return RET_OK;
}

/**
 * 初始化
 */
ret_t application_init(void)
{
	widget_t* win = window_create(NULL, 0, 0, 0, 0);

	/* 创建文本框*/
	widget_t* label = label_create(win, 0, 0, 0, 0);
	widget_set_self_layout_params(label, "0", "m", "100", "40");
	widget_set_text(label, L"stop");

	/* 创建按钮 */
	widget_t* button = button_create(win, 0, 0, 0, 0);
	widget_set_self_layout_params(button, "c", "b", "100", "40");
	widget_set_text_utf8(button, "start timer");
	widget_on(button, EVT_CLICK, on_click_start_timer, label);

	return RET_OK;
}
