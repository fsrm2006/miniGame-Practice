#include "../slbhr.h"
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
void GameView() //无需参数直接调用
{
	/*	优先级：核心
		设计人：无相欠
		负责人：
		功能：游戏核心函数  其中需整合 调用其他函数，如关卡画面函数 胜利判断 死亡判断 人物移动函数 交互函数 游戏刷新函数 
		先调用初始化函数GameInit() 然后进入游戏主循环while(1)，调用GameDraw()函数绘制游戏画面，
		检测键盘输入
		如果输入为移动键,要区分是ADW方向键还是左右上方向键，区分之后获得人物编号
			如果输入的是方向键调用水平移动函数HorizontalMov()和跳跃函数JumpMov()（如果人物ItemType=0人在地面才能跳跃）实现人物移动  
			实现人物移动后调用IsWall()函数实现碰撞检测 
			接着先调用IsDeath()函数实现死亡检测
			再调用IsDiamondGet()函数实现钻石拾取检测 
			然后调用IsPanelDown()函数实现压力板按下和石板移动
			调用IsDoorNear()函数实现靠近门开门检测 
		如果输入的是F键	调用IsSwitchOn()函数实现开关操作以及石板移动

		然后调用IsWin()函数实现胜利检测
		如果游戏胜利
			非核心：调用DoorMov()函数实现门的开关动画
			非核心：调用JoinDoor()函数显示进门动画 
		然后调用WinView()函数实现胜利界面
		
		同时检测鼠标点击，如果点击暂停按钮则调用暂停界面    实现游戏暂停

		参考逻辑：清屏，接收鼠标信息，检测是否点击暂停按钮
		返回值:void
	*/

	const double target_fps = 300;                // 目标帧率
	const double frame_delay = 1000 / target_fps; // 每帧目标耗时（ms）
	DWORD start_time, frame_time;
	GameDraw();
	while (1) {
		start_time = GetTickCount();
		player1.movdire = 0;//初始化人物移动方向为0表示静止
		player2.movdire = 0;
        while (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
            if (msg.message == WM_KEYDOWN) { // 按键按下：标记为1
                if (msg.vkcode == 'A') {
                    keyLeft_player1 = 1;
                }
                else if (msg.vkcode == 'D') {
                    keyRight_player1 = 1;
                }
                else if (msg.vkcode == 'W') {
                    keyJump_player1 = 1;
                }
                else if (msg.vkcode == 37) { // ←键
                    keyLeft_player2 = 1;
                }
                else if (msg.vkcode == 39) { // →键
                    keyRight_player2 = 1;
                }
                else if (msg.vkcode == 38) { // ↑键
                    keyJump_player2 = 1;
                }
                else if (msg.vkcode == 70) { // F键（玩家1）
                    keySwitch_player1 = 1;
                }
                else if (msg.vkcode == 96) { // 小键盘0键（玩家2）
                    keySwitch_player2 = 1;
                }
            }
            else if (msg.message == WM_KEYUP) { // 按键松开：标记为0
                if (msg.vkcode == 'A') {
                    keyLeft_player1 = 0;
                    player1.movdire = 0; // 停止左移，恢复静止
                    player1.movflag = 0;
                }
                else if (msg.vkcode == 'D') {
                    keyRight_player1 = 0;
                    player1.movdire = 0; // 停止右移，恢复静止
                    player1.movflag = 0;
                }
                else if (msg.vkcode == 'W') {
                    keyJump_player1 = 0;
                }
                else if (msg.vkcode == 37) { // ←键
                    keyLeft_player2 = 0;
                    player2.movdire = 0;
                    player2.movflag = 0;
                }
                else if (msg.vkcode == 39) { // →键
                    keyRight_player2 = 0;
                    player2.movdire = 0;
                    player2.movflag = 0;
                }
                else if (msg.vkcode == 38) { // ↑键
                    keyJump_player2 = 0;
                }
                else if (msg.vkcode == 70) { // F键松开
                    keySwitch_player1 = 0;
                    hasTriggeredSwitch = 0; // 允许下次触发
                    FirstKeyPress = 0;
                }
                else if (msg.vkcode == 96) { // 小键盘0松开
                    keySwitch_player2 = 0;
                    hasTriggeredSwitch = 0; // 允许下次触发
                    FirstKeyPress = 0;
                }
            }
            else if (msg.message == WM_LBUTTONDOWN) { // 鼠标左键点击
                // 检测是否点击暂停按钮（确保StopButton格式为[x1,y1,x2,y2]）
                if (msg.x >= StopButton[NowLevel][0] && msg.x <= StopButton[NowLevel][2] &&
                    msg.y >= StopButton[NowLevel][1] && msg.y <= StopButton[NowLevel][3]) {
                    PlaySoundEffect(12);
                    CountTime(1);
                    ViewStop(); // 调用暂停界面
                    msg = { 0 }; // 清空消息，避免重复触发
                }
            }
        }
		
		HorizontalMov();
		JumpMov();
        IsSwitchOn();
		SlateMov(); //石板移动函数
		GravityMov(1); 
		GravityMov(2);
        if (player1.movflag + player2.movflag)
        {
            IsSpikeNear();
        }
		if (player1.movflag == 1)
		{
			IsWall(1);
			IsDiamondGet(1);
			IsPanelDown();
			IsDoorNear(1);
			player1.movflag = 0;
		}
		if (player2.movflag == 1)
		{
			IsWall(2);
			IsDiamondGet(2);
			IsPanelDown();
			IsDoorNear(2);
			player2.movflag = 0;
		}
        
		if (IsDeath(1) || IsDeath(2)) {
			PlaySoundEffect(10); // 播放死亡音效
			Sleep(500); // 死亡后暂停300毫秒，提升用户体验
			CountTime(-1);
			DeathView();
		}
		if (IsWin() == 1) {
			//DoorMov();
			//EnterDoor();
            GameDraw();
            Sleep(300);
			CountTime(-1);
			WinView();
		}
		GameDraw();
		frame_time = GetTickCount() - start_time; // 计算当前帧耗时
		if (frame_time < frame_delay) {           // 若耗时不足，休眠补足
			Sleep(frame_delay - frame_time);
		}
	}
}
