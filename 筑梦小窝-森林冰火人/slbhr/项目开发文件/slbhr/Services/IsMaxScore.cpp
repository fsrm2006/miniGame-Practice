#include"../slbhr.h">
void IsMaxScore(int score)//传入这一关的得分
{
	//优先级：非核心
	//设计人：浮生若梦
		//负责人：阏逢
		//函数描述：此函数用于判断并修改每一关分数的最大值
		//逻辑说明：根据NowLevel变量获取关卡数和这一关的历史最高分MaxScore[3]；
		//自动替换为最高分
		//如有疑问欢迎询问
		//返回值：无
	if (NowLevel < 0 || NowLevel > 2) {
		return;
	}
	if (score > MaxScore[NowLevel]) {
		MaxScore[NowLevel] = score;
	}
}