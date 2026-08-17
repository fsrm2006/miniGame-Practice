#include"../slbhr.h"
void SlateMov()
{
	//优先级：非核心
	//设计人：浮生若梦
	//开发人：林宇卿
	//简介：此函数为石板的移动函数，用于逐渐修改石板的坐标
	//实现思路：在游戏主循环中调用此函数，先检遍历测石板是否需要移动SlateFlag（0表示不需要移动，1为需要移动到SlatePos的位置,2表示需要移动到SlatePos2的位置）是否需要移动，
	//根据目标坐标SlateFlag确定移动方向，然后单次移动NowSlatePos一定距离，然后判断是否到达目标位置SlatePos和2，
	//逐步调整石板的位置，直到达到目标位置时将SlateFlag设为0表示不需要移动;
	//有问题记得来交流哦 

	//SlatePos[i][0]表示目标位置左上x坐标
	//SlatePos[i][1]表示目标位置左上y坐标
	//SlatePos[i][2]表示目标位置右下x坐标
	//SlatePos[i][3]表示目标位置右下y坐标
	for (int i = 0; i < SlateNum[NowLevel]; i++)
	{
		if (SlateFlag[i] == 0)
			continue;
		else if (SlateFlag[i] == 1) //需要移动到SlatePos的位置
		{
			//向目标位置移动
			if (NowSlatePos[i][0] < SlatePos[NowLevel][i][0]) //左上x坐标小于目标位置，向右移动
			{
				player1.movflag = 1;
				player2.movflag = 1;
				NowSlatePos[i][0] += 1; //单次移动2个像素
				NowSlatePos[i][2] += 1; //右下x坐标也要移动
			}
			else if (NowSlatePos[i][0] > SlatePos[NowLevel][i][0]) //左上x坐标大于目标位置，向左移动
			{
				player1.movflag = 1;
				player2.movflag = 1;
				NowSlatePos[i][0] -= 1;
				NowSlatePos[i][2] -= 1;
			}
			if (NowSlatePos[i][1] < SlatePos[NowLevel][i][1]) //左上y坐标小于目标位置，向下移动
			{
				player1.movflag = 1;
				player2.movflag = 1;
				NowSlatePos[i][1] += 1;
				NowSlatePos[i][3] += 1;
			}
			else if (NowSlatePos[i][1] > SlatePos[NowLevel][i][1]) //左上y坐标大于目标位置，向上移动
			{
				player1.movflag = 1;
				player2.movflag = 1;
				NowSlatePos[i][1] -= 1;
				NowSlatePos[i][3] -= 1;
			}
			//检查是否到达目标位置
			if (NowSlatePos[i][0] == SlatePos[NowLevel][i][0] && NowSlatePos[i][1] == SlatePos[NowLevel][i][1])
			{
				//PlaySoundEffect(-3);//停止播放石板移动音效
				SlateFlag[i] = 0; //到达目标位置，停止移动
			}
		}
		else if (SlateFlag[i] == 2) //需要移动到SlatePos2的位置
		{
			//向目标位置移动
			if (NowSlatePos[i][0] < SlatePos2[NowLevel][i][0]) //左上x坐标小于目标位置，向右移动
			{
				player1.movflag = 1;
				player2.movflag = 1;
				NowSlatePos[i][0] += 1; //单次移动2个像素
				NowSlatePos[i][2] += 1; //右下x坐标也要移动
			}
			else if (NowSlatePos[i][0] > SlatePos2[NowLevel][i][0]) //左上x坐标大于目标位置，向左移动
			{
				player1.movflag = 1;
				player2.movflag = 1;
				NowSlatePos[i][0] -= 1;
				NowSlatePos[i][2] -= 1;
			}
			if (NowSlatePos[i][1] < SlatePos2[NowLevel][i][1]) //左上y坐标小于目标位置，向下移动
			{
				player1.movflag = 1;
				player2.movflag = 1;
				NowSlatePos[i][1] += 1;
				NowSlatePos[i][3] += 1;
			}
			else if (NowSlatePos[i][1] > SlatePos2[NowLevel][i][1]) //左上y坐标大于目标位置，向上移动
			{
				player1.movflag = 1;
				player2.movflag = 1;
				NowSlatePos[i][1] -= 1;
				NowSlatePos[i][3] -= 1;
			}
			//检查是否到达目标位置
			if (NowSlatePos[i][0] == SlatePos2[NowLevel][i][0] && NowSlatePos[i][1] == SlatePos2[NowLevel][i][1])
			{
				//PlaySoundEffect(-3);//停止播放石板移动音效
				SlateFlag[i] = 0; //到达目标位置，停止移动
			}

		}
	}
}