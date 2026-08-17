#include"..\slbhr.h"
bool IsAABBCollide(int l1, int t1, int r1, int b1, int l2, int t2, int r2, int b2);

void IsDoorNear(int player)
//player 表示哪个玩家 1表示玩家1,2表示玩家2
{
	//优先级：核心；
		//设计人：浮生若梦
		//负责人：浮生若梦
		//函数描述：此函数用于检测人物是否在门周围，若人物和门的体积判定重叠，以及更新门的状态;
		//逻辑说明：遍历对应关卡的DoorVolume[3][2][4], 矩形数量为DoorNum；人物体积框的上下左右边框都需要判断是否触地
		//如果人物体积判定框（左下右下的两个点）在任何一个矩形内部则将把对应的门的状态设置为开全局变量doorflag[2]；
		//如有疑问欢迎询问
		//返回值：无
	struct player* p;
	if (player == 1)
		p = &player1;
	else
		p = &player2;
	for (int i = 0; i < DoorNum[NowLevel]; i++)
	{
		if (i + 1 == player)
		{
			if (IsAABBCollide(p->xl,p->yl,p->xr,p->yr,
				DoorVolume[NowLevel][i][0], DoorVolume[NowLevel][i][1],
				DoorVolume[NowLevel][i][2], DoorVolume[NowLevel][i][3]))
				DoorFlag[i] = 1;
			else
				DoorFlag[i] = 0;
		}
	}
}