#include "awtk.h"

extern ret_t application_init(void);

int main(void)
{
	int lcd_w = 800;
	int lcd_h = 480;

	/* 
	* ��ʼ�� AWTK
	* ���� APP_DESKTOP Ϊ���� window ������ģʽ 
	* ���� "res" Ϊ������ԴĿ¼·��Ϊ������Ŀ¼��"res"
	*/
	tk_init(lcd_w, lcd_h, APP_DESKTOP, NULL, "res");

	/* Ԥ������Ϊ default.tff ��������Դ */
	assets_manager_preload(assets_manager(), ASSET_TYPE_FONT, "default");
	/* Ԥ������Ϊ default.bin �ķ����Դ */
	assets_manager_preload(assets_manager(), ASSET_TYPE_STYLE, "default");

	/* ��ʼ����Դ */
	tk_init_assets();

	/* ������Ļ */
	application_init();

	/* ����awtk�¼�ѭ�� */
	tk_run();

	return 0;
}
