#include"../slbhr.h"
#include<graphics.h>

void ViewChoiceLevel() {
    //编写人：玲
    /*功能：绘制关卡选择界面：背景、关卡按钮、得分文本（无得分显示 “无”）、返回按钮，然后检测点击选择关卡或返回主菜单
    1.界面绘制：在点击开始游戏后，调用该函数，绘制关卡选择界面，显示不同的关卡，对应关卡下面显示最高得分，
    通过 MaxScores读取最高得分，无最高得分则显示0。（关卡默认初始全部解锁）
    2.鼠标交互，点击后调用MouseClick()函数获取点击按钮序号
    int Buttons[按钮数量][4]
    Butttons的储存格式：{{按钮左上x坐标,按钮左上y坐标,按钮右下x坐标，按钮右下y坐标},{xxx},{},……}，
    根据返回值的不同修改Nowlevel变量然后调用初始化GameInit函数，最后调用ViewMenu函数；
    -若点击返回主菜单，调用ViewMenu函数；
    -若为空白处，则不进行任何处理。
    3.依赖说明：依赖MouseClick函数（判定左键松开有效）、ViewMenu函数（主菜单跳转）、得分存储介质（本地文件/全局变量）
    */
    //void ViewMenu();              // 主菜单函数
    //
    //int MouseClick();			//获取鼠标点击按钮序号，详情见函数描述；
    //MaxScore[]：全局变量数组，存储各关卡最高得分
    //返回值：无

    loadimage(NULL, L"resource\\Image resource\\LevelChoice\\LevelChoice.jpg", 1024, 768);
	setbkmode(TRANSPARENT);
	//显示各关卡最高得分
    settextcolor(0);
    settextstyle(20, 0, L"微软雅黑 Bold");
    wchar_t score[32];
    swprintf(score, 32, L"最高分:%d",MaxScore[0]);
    outtextxy(90, 245, score);

    swprintf(score, 32, L"最高分:%d", MaxScore[1]);
    outtextxy(265, 245, score);

    swprintf(score, 32, L"最高分:%d", MaxScore[2]);
    outtextxy(440, 245, score);

    ExMessage msg;
    while (1)
    {
        
        peekmessage(&msg, EX_MOUSE);
        if (msg.message == WM_LBUTTONDOWN
            && msg.x > 75 && msg.x < 180
            && msg.y>100 && msg.y < 182) {
            NowLevel = 0;
            msg = { 0 };
            PlaySoundEffect(12);//播放点击音效
            GameInit();
            GameView();
        }
        else if (msg.message == WM_LBUTTONDOWN
            && msg.x > 247 && msg.x < 353
            && msg.y> 100 && msg.y < 182) {
            NowLevel = 1;
            msg = { 0 };
            PlaySoundEffect(12);//播放点击音效
            GameInit();
            GameView();
        }
        else if (msg.message == WM_LBUTTONDOWN
            && msg.x > 422 && msg.x < 527
            && msg.y> 100 && msg.y < 182) {
            NowLevel = 2;
            msg = { 0 };
            PlaySoundEffect(12);//播放点击音效
            GameInit();
            GameView();
        }
        /*else if (msg.message == WM_LBUTTONDOWN
            && msg.x > 603 && msg.x < 708
            && msg.y> 100 && msg.y < 182) {
            PlaySoundEffect(12);//播放点击音效
            NowLevel = 3;
            GameInit();
            GameView();
        }*/
        else if (msg.message == WM_LBUTTONDOWN
            && msg.x > 400 && msg.x < 627
            && msg.y> 565 && msg.y < 690) {
            msg = { 0 };
            PlaySoundEffect(12);//播放点击音效
            ViewMenu();
        }
    }
}
       