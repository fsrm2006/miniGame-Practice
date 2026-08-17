#include <iostream>
#include <graphics.h>
#include<conio.h>
#include "..\slbhr.h"
void WinView() {
	/*	优先级：核心
	设计人：无相欠
	负责人：
	功能:胜利画面
	参考逻辑：清屏，打印胜利界面背景，打印胜利信息(分数,通关时间,钻石数量），将分数传给IsMaxScore函数自动更新最高分
	，打印游戏选项（重新开始，下一关（需要修改NowLevel)，返回主菜单）
	让后检测鼠标点击，点击后调用MouseClick()函数获取点击按钮序号
	int Buttons[按钮数量][4]
	Butttons的储存格式：{{按钮左上x坐标,按钮左上y坐标,按钮右下x坐标，按钮右下y坐标},{xxx},{},……}
	返回值:void
*/

	int Buttons[3][4] = {
		{450, 480, 590, 520}, // 下一关
		{450, 530, 610, 570}, // 重新开始
	{ 450, 580, 610, 620 }  // 返回菜单	
	};

	PlaySoundEffect(5 + (NowLevel + 1) % 2);//播放胜利音效1,2
	//输出失败表头
	cleardevice();
	loadimage(NULL, L"resource\\Image resource\\overbg\\bg.jpg", 1024,820);
	settextcolor(WHITE);
	setbkcolor(0x306A83);
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, L"华文行楷");
	outtextxy(390, 250, L"游戏胜利！");


	//输出通关时间（秒 -> 分:秒）
	settextstyle(30, 0, L"黑体");
	outtextxy(450, 370, L"用时：");
	int minutes = gametime / 60;
	int seconds = gametime % 60;
	wchar_t buftime[32];
	swprintf(buftime, 32, L"%d分%02d秒", minutes, seconds);
	outtextxy(550, 370, buftime);

	//计算并输出得分 一颗钻石10分  时间180秒内，每少1秒给1分
	score += countdiamond * 10;
	if (gametime <= 180)
		score += (180 - gametime);
	IsMaxScore(score);//检查并更新最高分
	settextstyle(30, 0, L"黑体");
	outtextxy(450, 330, L"得分：");
	wchar_t bufscore[32];
	swprintf(bufscore, 32, L"%d分", score);
	outtextxy(550, 330, bufscore);

	//输出钻石数量
	settextstyle(30, 0, L"黑体");
	outtextxy(450, 410, L"钻石：");
	wchar_t bufdiamond[32];
	swprintf(bufdiamond, 32, L"%d颗", countdiamond);
	outtextxy(550, 410, bufdiamond);
	if (NowLevel<2)
	//输出下一关按钮
	{
		settextstyle(40, 0, L"宋体");
		outtextxy(450, 480, L"下一关 ");
	}

	//输出重新开始按钮
	settextstyle(40, 0, L"宋体");
	outtextxy(450, 530, L"重新开始");

	//输出返回菜单按钮
	settextstyle(40, 0, L"宋体");
	outtextxy(450, 580, L"返回菜单");
	setbkcolor(0);
	while (1)
	{
		if(MouseClick(Buttons, 3)==0) // 下一关
		{
			NowLevel++;
			GameInit();
			break;
		}
		else if (MouseClick(Buttons, 3) == 1) // 重新开始
		{
			GameInit();
			break;
		}
		else if (MouseClick(Buttons, 3) == 2) // 返回菜单
		{
			ViewMenu();
			break;
		}

	}
}
