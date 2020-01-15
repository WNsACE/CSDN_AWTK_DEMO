#include "awtk.h"

extern ret_t application_init(void);

int main(void)
{
	int lcd_w = 800;
	int lcd_h = 480;

	/* 
	* 初始化 AWTK
	* 参数 APP_DESKTOP 为设置 window 的桌面模式 
	* 参数 "res" 为设置资源目录路径为程序工作目录下"res"
	*/
	tk_init(lcd_w, lcd_h, APP_DESKTOP, NULL, "res");

	/* 预加载名为 default.tff 的字体资源 */
	assets_manager_preload(assets_manager(), ASSET_TYPE_FONT, "default");
	/* 预加载名为 default.bin 的风格资源 */
	assets_manager_preload(assets_manager(), ASSET_TYPE_STYLE, "default");

	/* 初始化资源 */
	tk_init_assets();

	/* 打开主屏幕 */
	application_init();

	/* 进入awtk事件循环 */
	tk_run();

	return 0;
}
