#include<graphics.h>
#include"..\slbhr.h"
void GameInit() {
	//编写人：玲
	//负责人：玲
	/*功能：1.在选择完关卡(关卡存在NowLevel)，调用对应关卡函数时，在关卡函数中调用该函数，加载当前关卡的初始配置；
			2.在胜利/暂停/失败界面点击重玩时，调用该函数，清空屏幕，恢复所有记录数据变量到初始值
	逻辑处理：- 清空绘图屏幕（避免残留上一轮界面元素）；
			  - 恢复所有游戏数据变量到初始值（钻石数量、人物初始坐标、时间、石砖位置NowSlatePos等）；
			  -坐标系约定（通常取 y 向下为正，x向右为正）

	3. 依赖说明：
	   - 依赖该关卡专属的游戏状态变量（如人物左上角像素坐标、钻石数量及位置、地图数据）；
	   - 依赖EasyX的清屏接口（如EasyX的cleardevice()）；

	*/
	//清屏函数清屏
	//其他变量：人物在该关卡的初始左上角像素坐标 
	//该地图及道具的数组数据
	//已收集的钻石数量countdiammond初始化为0
	//时间time初始化为0
	//返回值：无
	score = 0;
	countdiamond = 0;
	gametime = 0;
	gameStartTime = 0;
	pauseAccumulate = 0;
	pauseStartTime = 0;
	isPaused = 0;
	DoorFlag[0] = 0;
	DoorFlag[1] = 0;
	FirstKeyPress = 0;//用于表示F或者0键是否为第一次按下，防止重复判断
	keyLeft_player1 = 0;   // A键（玩家1左移）
	keyRight_player1 = 0;  // D键（玩家1右移）
	keyJump_player1 = 0;   // W键（玩家1跳跃）
	keyLeft_player2 = 0;   // ←键（玩家2左移）
	keyRight_player2 = 0;  // →键（玩家2右移）
	keyJump_player2 = 0;   // ↑键（玩家2跳跃）
	hasJumped_player1 = 0;
	hasJumped_player2 = 0;
	keySwitch_player1 = 0;  // F键（玩家1操作开关）
	keySwitch_player2 = 0;  // 小键盘0键（玩家2操作开关）
	hasTriggeredSwitch = 0; // 开关单次触发保护（避免按住时重复执行）
	msg = { 0 };
	for (int i = 0; i < DiamondNum[NowLevel]; i++) {	//初始化钻石状态
		DiamondFlag[i] = 0;
	}
	for (int i = 0; i < SwitchNum[NowLevel]; i++) {	//初始化开关状态
		SwitchFlag[i] = 0;
	}
	for (int j = 0; j < SlateNum[NowLevel]; j++) {	//初始化石板状态
		SlateFlag[j] = 0;
	}
	for (int i = 0; i < PanelNum[NowLevel]; i++){ //初始化压力板状态
		PanelFlag[i] = 0;
	}
	for (int i = 0; i < SpikeNum[NowLevel]; i++)
	{
		SpikeFlag[i] = 0;
	}
	for (int j = 0; j < SlateNum[NowLevel]; j++) {
		NowSlatePos[j][0] = SlatePos[NowLevel][j][0];
		NowSlatePos[j][1] = SlatePos[NowLevel][j][1];
		NowSlatePos[j][2] = SlatePos[NowLevel][j][2];
		NowSlatePos[j][3] = SlatePos[NowLevel][j][3];
	}
	player1.xl = PlayerInitPos[NowLevel][0][0];
	player1.yl = PlayerInitPos[NowLevel][0][1];
	player1.xr = PlayerInitPos[NowLevel][0][2];
	player1.yr = PlayerInitPos[NowLevel][0][3];
	player1.xm = (player1.xl + player1.xr) / 2;
	player1.ItemType = 0;
	player1.jumptimes = 0;
	player1.movdire = 0;
	player1.movflag = 1;

	player2.xl = PlayerInitPos[NowLevel][1][0];
	player2.yl = PlayerInitPos[NowLevel][1][1];
	player2.xr = PlayerInitPos[NowLevel][1][2];
	player2.yr = PlayerInitPos[NowLevel][1][3];
	player2.xm = (player2.xl + player2.xr) / 2;
	player2.ItemType = 0;
	player2.jumptimes = 0;
	player2.movdire = 0;
	player2.movflag = 1;
	CountTime(-1);
}