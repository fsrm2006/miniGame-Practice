#include "../slbhr.h"
int JumpHeight[3] = { 25,33,30 };
void JumpMov()
{

    // 玩家1跳跃：仅在「按键按住+未触发过+满足条件」时触发
    if (keyJump_player1 && !hasJumped_player1 && (player1.ItemType == 0 || player1.ItemType == 4 || player1.ItemType == 5)) {
		PlaySoundEffect(2); // 播放跳跃音效
        player1.jumptimes = JumpHeight[NowLevel];
        hasJumped_player1 = 1; // 标记为已触发
    }
    // 按键松开时重置标记（允许下次跳跃）
    if (!keyJump_player1) {
        hasJumped_player1 = 0;
    }

    // 玩家2跳跃：同理
    if (keyJump_player2 && !hasJumped_player2 && (player2.ItemType == 0 || player2.ItemType == 4 || player2.ItemType == 5)) {
        PlaySoundEffect(1); // 播放跳跃音效
        player2.jumptimes = JumpHeight[NowLevel];
        hasJumped_player2 = 1;
    }
    if (!keyJump_player2) {
        hasJumped_player2 = 0;
    }
}

	/*	优先级：核心
		设计人：无相欠
		负责人：
		功能：根据键盘传入的消息，’W‘则人物1碰撞箱所有纵坐标减小
			  根据键盘传入的消息，’↑‘则人物1碰撞箱所有纵坐标减小
		参考逻辑：
		返回值:void
	*/