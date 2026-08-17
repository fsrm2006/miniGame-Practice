#include"../slbhr.h"
void GravityMov(int player)
{
	double upspeed = 4;
	double downspeed = 3;
	struct player* p;
	if (player == 1)
	{
		p = &player1;
	}
	else
	{
		p = &player2;
	}
	if (p->jumptimes > 0) 
	{
		p->jumptimes--;			
		p->yl-=upspeed;
		p->yr-=upspeed;
		p->movflag = 1;
	}
	else if(p->ItemType== -1 || p->ItemType==1 || p->ItemType == 2 || p->ItemType == 3){
		if (p->movdire != 0)
			downspeed = 2;
		p->yl+=downspeed;
		p->yr+=downspeed;
		p->movflag = 1;
	}
}
//优先级：核心
//设计人：浮生若梦
//开发人：
//介绍：用于控制两个人物的下坠和跳跃
//实现逻辑：跳跃函数调用时可以设置一个jumptimes（比如jumptimes==60，60帧的游戏刚好跳跃1秒）,然后如果检测到人物脚下的Itemtype为-1（空中）
//先检测jumptimes是否>0，>0说明要跳跃，改变一次人物竖直高度的坐标yl,yr（增加），jumptimes--；
//如果jumptimes==0那么说明人物未在跳跃状态而且在空中，那就每秒改变一次人物yl,yr（减少）;
//jumptimes为全局变量；
//返回值：无
