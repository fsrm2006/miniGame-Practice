#include <graphics.h>
#include<conio.h>
#include "..\slbhr.h"
#include<stdio.h>

void DeathView() {
	/*	优先级：核心
		设计人：无相欠
		负责人：
		功能:死亡画面
		参考逻辑：清屏，打印失败信息(分数,通关时间,钻石数量），打印失败图案，打印游戏选项（重新开始，返回主菜单）
		让后检测鼠标点击，点击后调用MouseClick()函数获取点击按钮序号
		返回值:void
	*/
	int Buttons[2][4] = {
	{450,500,610,540},
	{450,580,700,620}
	};
	PlaySoundEffect(7);
	//输出失败表头
	cleardevice();
	loadimage(NULL, L"resource\\Image resource\\overbg\\bg.jpg", 1024, 820);
	settextcolor(WHITE);
	setbkcolor(0x306A83);
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, L"华文行楷");
	outtextxy(390, 250, L"挑战失败！");

	//输出通关时间（秒 -> 分:秒）
	settextstyle(30, 0, L"黑体");
	outtextxy(450, 350, L"用时：");
	int minutes = gametime / 60;
	int seconds = gametime % 60;
	wchar_t buftime[32];
	swprintf(buftime, 32, L"%d分%02d秒", minutes, seconds);
	outtextxy(550, 350, buftime);

	//输出钻石数量
	settextstyle(30, 0, L"黑体");
	outtextxy(450, 410, L"钻石：");
	wchar_t bufdiamond[32];
	swprintf(bufdiamond, 32, L"%d颗", countdiamond);
	outtextxy(550, 410, bufdiamond);

	//输出重新开始按钮
	settextstyle(40, 0, L"宋体");
	outtextxy(450, 500, L"重新开始");

	//输出返回菜单按钮
	settextstyle(40, 0, L"宋体");
	outtextxy(450, 580, L"返回菜单");

	//检测鼠标点击
	while (1)
	{
		int index = MouseClick(Buttons, 2);
		if (index==0)
		{
			GameInit(); //重新开始
			GameView();
			break;
		}
		else if(index == 1)
		{
			ViewMenu(); //返回菜单
			break;
		}

	}
}
