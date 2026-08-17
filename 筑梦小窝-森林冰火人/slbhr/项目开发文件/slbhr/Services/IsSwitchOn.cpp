#include"../slbhr.h"
#include<stdio.h>
bool IsAABBCollide(int l1, int t1, int r1, int b1, int l2, int t2, int r2, int b2);

void IsSwitchOn()
//
{
	//优先级：非核心；
		//设计人：浮生若梦
		//负责人：
		//函数描述：此函数需在玩家按下"F"键或者"小键盘"0"键时使用，用于检测人物是否在开关附近，如果在某个开关附近，则操作对应开关的石板;
		//逻辑说明：遍历对应关卡的SwitchVolume[3][10][5]，开关数量在SwitchNum[3]；
		//若人物和开关的体积判定框重叠，说明玩家正在操作此开关，
		// 此时更新开关对应石板NowSlatePos[10][5]为SlatePos2[3][10][4];（开关对应石板为SwitchVolume[3][10][5]中第五个数据）；
		//拓展：可以使用SlateMov()函数来逐渐移动石板到目标位置，需要设置SlateFlag[10]为2表示需要移动到目标位置；
		//返回值：无
		//如有疑问欢迎询问
    if (keySwitch_player1 && !hasTriggeredSwitch) {
        for (int i = 0; i < SwitchNum[NowLevel]; i++) {
            // 检测玩家1与当前开关的碰撞（AABB碰撞）
            if (IsAABBCollide(
                player1.xl, player1.yl, player1.xr, player1.yr,
                SwitchVolume[NowLevel][i][0], SwitchVolume[NowLevel][i][1],
                SwitchVolume[NowLevel][i][2], SwitchVolume[NowLevel][i][3])) {
                int slateindex = SwitchVolume[NowLevel][i][4]; // 开关对应的石板索引
                // 切换开关状态 + 对应石板状态
                if (SwitchFlag[i] == 0) {
					PlaySoundEffect(3); // 播放开关声音效果
                    SwitchFlag[i] = 1;
                    SlateFlag[slateindex] = 2; // 石板移动到目标位置
                }
                else if (SwitchFlag[i] == 1) {
                    PlaySoundEffect(3); // 播放开关声音效果
                    SwitchFlag[i] = 0;
                    SlateFlag[slateindex] = 1; // 石板恢复原位置
                }
                hasTriggeredSwitch = 1; // 标记为已触发，避免重复切换
                break; // 只操作最近的一个开关，避免同时触发多个（可根据需求删除）
            }
        }
    }

    // 玩家2：按小键盘0键（keySwitch_player2=1）且未触发过 → 检测碰撞
    else if (keySwitch_player2 && !hasTriggeredSwitch) {
        for (int i = 0; i < SwitchNum[NowLevel]; i++) {
            // 检测玩家2与当前开关的碰撞（AABB碰撞）
            if (IsAABBCollide(
                player2.xl, player2.yl, player2.xr, player2.yr,
                SwitchVolume[NowLevel][i][0], SwitchVolume[NowLevel][i][1],
                SwitchVolume[NowLevel][i][2], SwitchVolume[NowLevel][i][3])) {
                int slateindex = SwitchVolume[NowLevel][i][4];
                // 切换开关状态 + 对应石板状态
                if (SwitchFlag[i] == 0) {
                    PlaySoundEffect(3); // 播放开关声音效果
                    SwitchFlag[i] = 1;
                    SlateFlag[slateindex] = 2;
                }
                else if (SwitchFlag[i] == 1) {
                    PlaySoundEffect(3); // 播放开关声音效果
                    SwitchFlag[i] = 0;
                    SlateFlag[slateindex] = 1;
                }
                hasTriggeredSwitch = 1; // 标记为已触发
                break; // 只操作最近的一个开关
            }
        }
    }
	
	
}