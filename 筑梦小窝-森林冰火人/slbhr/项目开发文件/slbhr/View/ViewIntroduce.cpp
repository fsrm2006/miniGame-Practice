#include <stdio.h>
#include <easyx.h>
#include <graphics.h>
#include"../slbhr.h"
void putziimg();
void changejie(int n);
int jie = 0;


void ViewIntroduce() {
	/*非核心
	* 编写人：望年
	* 负责人：
		输入值：无
		返回值：无
		函数内变量：int Buttons[按钮数量][4]  检测到鼠标点击调用MouseClick()函数获取点击按钮序号
			Butttons的储存格式：{{按钮左上x坐标,按钮左上y坐标,按钮右下x坐标，按钮右下y坐标},{xxx},{},……}
		功能：
		1.展示游戏基本玩法介绍，键位操作，通关要求以及开发人员介绍
		2.底部设置一个返回按钮
		3.让后检测鼠标点击，点击后调用MouseClick()函数获取点击按钮序号
		int Buttons[按钮数量][4]
		Butttons的储存格式：{{按钮左上x坐标,按钮左上y坐标,按钮右下x坐标，按钮右下y坐标},{xxx},{},……}

	*/
	BeginBatchDraw();
	while (1) {
		char arr[100];
		sprintf(arr, "image/%d.jpg", jie);
		ExMessage msg = { 0 };
		peekmessage(&msg, EX_MOUSE);
		IMAGE img[4];
		putziimg();
		FlushBatchDraw();
	}

}

void changejie(int n) {

	switch (n) {
	case 0:
		PlaySoundEffect(12);//播放点击音效
		EndBatchDraw();
		ViewMenu();
		break;
	case 1:
		if (jie <= 2 && jie >= 0) {
			PlaySoundEffect(12);//播放点击音效
			jie++;
		}
		else if (jie == 3) {
			PlaySoundEffect(12);//播放点击音效
			jie--;
		}
		break;
	case 2:
		PlaySoundEffect(12);//播放点击音效
		jie--;
		break;
	default:
		break;
	}

}

void putziimg() {


	settextstyle(30, 0, L"华文楷体");
	settextcolor(BROWN);
	setbkmode(TRANSPARENT);

	//上一页
	int shangye[4] = { 0, 360, 84, 390 };
	//下一页
	int xiaye[4] = { 940, 360, 1024, 390 };
	//返回
	int caidan[4] = { 950, 20, 1004, 50 };
	int VMButtons0[2][4] = { { 950, 20, 1004, 50 },{ 940, 360, 1024, 390 } };
	int VMButtons1[3][4] = { { 950, 20, 1004, 50 }, { 940, 360, 1024, 390 }, { 0, 360, 84, 390 } };
	int VMButtons2[3][4] = { { 950, 20, 1004, 50 }, { 940, 360, 1024, 390 }, { 0, 360, 84, 390 } };
	int VMButtons3[2][4] = { { 950, 20, 1004, 50 }, { 0, 360, 84, 390 } };
	BeginBatchDraw();
	IMAGE img[11];
	/*《森林冰火人》是一款解谜冒险游戏，玩家需要操控两个具有冰火两种特殊能力的角色，通过合作解决各种谜题。游戏玩法包括：
		角色互动：两个冰火人不能接触与自己不同颜色的液体，需利用各自的能力来推动石块，铺路让另一角色通过。
		1
		解谜机制：玩家需要利用水火兄弟的能力，如融化冰块、引燃火焰等，来解开谜题，闯过关卡。
		1
		合作机制：游戏强调双人合作，玩家需协调行动以克服障碍和陷阱
		*/
	switch (jie) {
	case 0:
		loadimage(img, L"resource/Image resource/introduce/0.jpg", 1024, 768);
		putimage(0, 0, img);
		outtextxy(420, 20, L"游戏基本玩法");
		settextcolor(MAGENTA);
		outtextxy(30, 500, L"《森林冰火人》是一款双人冒险游戏");
		outtextxy(30, 540, L"玩家需要操控冰人和火人");
		outtextxy(30, 580, L"通过合作解决各种谜题，最终抵达终点");
		outtextxy(30, 620, L"游戏尽可能的还原了原作的特色，并且在原作的基础上加入了少量新元素");
		outtextxy(30, 660, L"欢迎大家探索此作品");
		outtextxy(30, 700, L"入门作品还有很多不足，还请大家多多包涵");
		settextcolor(BROWN);
		outtextxy(940, 360, L"下一页");
		outtextxy(950, 20, L"菜单");
		EndBatchDraw();
		changejie(MouseClick(VMButtons0, 2));
		break;
	case 1:

		loadimage(img + 1, L"resource/Image resource/introduce/1.jpg", 1024, 768);
		putimage(0, 0, img + 1);
		outtextxy(450, 40, L"键位操作");
		settextcolor(RGB(29, 136, 232));
		outtextxy(300, 100, L"游戏控制方式采用键盘");
		outtextxy(300, 150, L"通过W，A，D键来控制冰人移动");
		outtextxy(300, 200, L"即向左用A，向右用D，跳跃用W");
		outtextxy(300, 250, L"通过↑，←，→来控制火人移动");
		outtextxy(300, 300, L"即↑跳跃，←向左移动，→向右移动");
		outtextxy(300, 350, L"其他键位操作在第一关均有详细介绍");
		outtextxy(300, 400, L"其他介绍：");
		outtextxy(300, 450, L"人物靠近尖刺时才会显示，人物踩到尖刺会死亡");
		outtextxy(300, 500, L"分数=10*获得钻石数 + 游戏时间少于300秒的秒数");
		settextcolor(MAGENTA);
		outtextxy(950, 20, L"菜单");
		outtextxy(20, 360, L"上一页");
		outtextxy(940, 360, L"下一页");
		EndBatchDraw();
		changejie(MouseClick(VMButtons1, 3));
		break;
	case 2:

		loadimage(img + 2, L"resource/Image resource/introduce/2.jpg", 500, 768);
		loadimage(img + 3, L"resource/Image resource/introduce/5.jpg", 262, 256);
		loadimage(img + 4, L"resource/Image resource/introduce/6.jpg", 50, 50);
		loadimage(img + 5, L"resource/Image resource/introduce/7.jpg", 262, 256);
		loadimage(img + 6, L"resource/Image resource/introduce/8.jpg", 262, 256);
		loadimage(img + 7, L"resource/Image resource/introduce/9.jpg", 262, 256);
		loadimage(img + 8, L"resource/Image resource/introduce/10.jpg", 262, 256);
		loadimage(img + 9, L"resource/Image resource/introduce/11.jpg", 262, 256);
		putimage(0, 0, img + 2);
		putimage(130, 300, img + 4);
		putimage(500, 0, img + 3);
		putimage(762, 0, img + 9);
		putimage(500, 256, img + 5);
		putimage(762, 256, img + 6);
		putimage(500, 512, img + 7);
		putimage(762, 512, img + 8);
		putimage(762, 0, img + 9);


		outtextxy(450, 20, L"通关要求");
		settextcolor(RED);
		outtextxy(13, 80, L"冰人，火人操作机关、越过障碍到达终点");
		settextcolor(YELLOW);
		outtextxy(950, 20, L"菜单");
		outtextxy(20, 360, L"上一页");
		outtextxy(940, 360, L"下一页");
		EndBatchDraw();
		changejie(MouseClick(VMButtons2, 3));
		break;
	case 3:
		loadimage(img + 10, L"resource/Image resource/introduce/3.jpg", 1024, 768);
		putimage(0, 0, img + 10);
		settextcolor(YELLOW);
		outtextxy(430, 40, L"开发人员介绍");
		settextcolor(0xE7CEAA);
		outtextxy(360, 120, L"浮生若梦：组长 监督官 项目负责人");
		outtextxy(360, 160, L"林宇卿：副组长 监督官");
		outtextxy(360, 200, L"望年：技术官 架构师");
		outtextxy(360, 240, L"无相欠：技术官 架构师");
		outtextxy(360, 280, L"白的黑：技术官 架构师");
		outtextxy(360, 320, L"玲：技术官 架构师");
		outtextxy(360, 360, L"清绪：产品经理");
		outtextxy(360, 400, L"阏逢：产品经理");
		outtextxy(360, 440, L"椰丝黄豆：友情出演");

		settextcolor(YELLOW);
		outtextxy(950, 20, L"菜单");
		outtextxy(20, 360, L"上一页");
		EndBatchDraw();
		changejie(MouseClick(VMButtons3, 2));
		break;
	}
}