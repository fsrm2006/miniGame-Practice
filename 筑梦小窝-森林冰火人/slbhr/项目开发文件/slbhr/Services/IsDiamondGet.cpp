#include"../slbhr.h"
void IsDiamondGet(int player)
//player 表示哪个玩家 1表示玩家1,2表示玩家2
{
	//优先级：非核心；
		//设计人：浮生若梦
		//负责人：
		//函数描述：此函数用于检测人物是否吃到钻石，;
		//逻辑说明：遍历对应关卡的DiamondVolume[3][10][4], 钻石数量在DiamondNum[3]；若人物和钻石的体积判定框重叠，并且钻石类型和人物匹配，
		//就更新钻石状态DiamondFlag[]，然后钻石计数DiamondCount加1；
		//如有疑问欢迎询问
		//返回值：无
	struct player* p;
	if (player == 1)
		p = &player1;
	else
		p = &player2;
	for (int i = 0; i < DiamondNum[NowLevel]; i++)
	{
		if (DiamondFlag[i] == 0 && i%2==(player-1))
		{
			if ((DiamondVolume[NowLevel][i][0] >= p->xl && DiamondVolume[NowLevel][i][0] <= p->xr
				|| DiamondVolume[NowLevel][i][2] >= p->xl && DiamondVolume[NowLevel][i][2] <= p->xr)
				&& (DiamondVolume[NowLevel][i][1] >= p->yl && DiamondVolume[NowLevel][i][1] <= p->yr
					|| DiamondVolume[NowLevel][i][3] >= p->yl && DiamondVolume[NowLevel][i][3] <= p->yr))
			{
				PlaySoundEffect(11);
				DiamondFlag[i] = 1;
				countdiamond++;
			}
				
		}
	}
}