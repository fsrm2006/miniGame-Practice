#include <iostream>
#include <graphics.h>
#include<conio.h>
#include "..\slbhr.h"
void ViewStop() {
    /*
    优先级：非核心
    设计人：白的黑
    功能：
    展示界面：
    1.重置
    2.返回菜单
    3.设置
    4.返回游戏(直接调用GameView函数)
    鼠标交互：检测点击后调用MouseClick函数获取点击按钮序号
    int Buttons[按钮数量][4]
    Butttons的储存格式：{{按钮左上x坐标,按钮左上y坐标,按钮右下x坐标，按钮右下y坐标},{xxx},{},……}
    */
    CountTime(1);//暂停计时
    //设置按钮坐标数组
    int Buttons[4][4] = {
        {460,340,570,400}, //重置
        {460,410,570,470}, //菜单
        {460,480,570,540}, //设置
        {405,550,630,610}  //返回游戏
    };
    //生成暂停提示
    cleardevice();
    loadimage(NULL, L"resource\\Image resource\\overbg\\bg.jpg", 1024, 820);
    settextcolor(WHITE);
    setbkcolor(0x306A83);
    setbkmode(TRANSPARENT);
    settextstyle(80, 30, L"华文行楷");
    outtextxy(430, 250, L"暂停");

    //生成重置按钮
    settextstyle(60, 0, L"华文行楷");
    outtextxy(410, 340, L"重新开始");

    //生成返回菜单按钮
    settextstyle(60, 0, L"华文行楷");
    outtextxy(460, 410, L"菜单");

    //生成设置按钮
    settextstyle(60, 0, L"华文行楷");
    outtextxy(460, 480, L"设置");

    //生成返回游戏按钮
    settextstyle(60, 0, L"华文行楷");
    outtextxy(405, 550, L"返回游戏");

    while (1)
    {
        int index = MouseClick(Buttons, 4);
        if (index == 0) //重新开始
        {
            GameInit();
            flushmessage(EX_MOUSE);
            msg = { 0 };
			GameView();
            break;
        }
        else if (index == 1) // 菜单
        {
            ViewMenu();
            break;
        }
        else if (index == 2) // 设置
        {
            ViewSettings(1);
            break;
        }
        else if (index == 3) // 返回游戏
        {
            CountTime(0);//继续计时 
            msg = { 0 };
            // 重置按键状态，避免暂停后人物继续移动
            keyLeft_player1 = keyRight_player1 = keyJump_player1 = keySwitch_player1 = 0;
            keyLeft_player2 = keyRight_player2 = keyJump_player2 = keySwitch_player2 = 0;
			GameView();
            break;
        }
    }
}
