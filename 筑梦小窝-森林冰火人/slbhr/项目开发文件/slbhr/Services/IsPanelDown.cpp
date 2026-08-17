#include"../slbhr.h"
#include<stdio.h>
void IsPanelDown()
//
{
	//优先级：非核心；
		//设计人：浮生若梦
		//负责人：
		//函数描述：此函数用于检测人物是否踩在压力板上方，如果人物踩在压力板上方，则更新压力板对应石板位置;
		//逻辑说明：遍历对应关卡的PanelVolume[3][10][5], 压力板数量在PanelNum[3]；
		//若人物和压力板的体积判定框重叠，则更新压力板状态PanelFlag[10];
		//并且更新石砖的位置NowSlatePos[10][4]为SlatePos2[3][10][4]（压力板对应石板见PanelVolume[3][10][5]中数据）;
		//如有疑问欢迎询问
		//返回值：无
	int SlateMovFlag[10] = { 0 };
	//石板对应序号压力板是否踩下，用于判断石板是否需要移动；

	for (int i = 0; i < PanelNum[NowLevel]; i++)
	{
		int index = PanelVolume[NowLevel][i][4];
		int flag = 0;
		if (player1.xm >= PanelVolume[NowLevel][i][0] && player1.xm <= PanelVolume[NowLevel][i][2] &&
			player1.yr >= PanelVolume[NowLevel][i][1] && player1.yr <= PanelVolume[NowLevel][i][3])
		{
			SlateMovFlag[index]++;
			flag = 1;
		}
		if (player2.xm >= PanelVolume[NowLevel][i][0] && player2.xm <= PanelVolume[NowLevel][i][2] &&
			player2.yr >= PanelVolume[NowLevel][i][1] && player2.yr <= PanelVolume[NowLevel][i][3])
		{
			SlateMovFlag[index]++;
			flag = 1;
		}
		if (flag)
		{
			if (PanelFlag[i] == 0)
			{
				PlaySoundEffect(3);//播放压力板被踩下的声音效果
			}
			PanelFlag[i] = 1;//压力板被踩下
		}
		else
		{
			PanelFlag[i] = 0;//压力板未被踩下
		}
	}
	for (int i = 0; i < SlateNum[NowLevel]; i++)
	{
		if (SlateMovFlag[i])
		{
			SlateFlag[i] = 2;//设置为需要移动到目标位置
		}
		else
		{
			int flag = 0;
			for (int j = 0; j < PanelNum[NowLevel]; j++)
			{
				if (PanelVolume[NowLevel][j][4] == i)
				{
					flag = 1;
					break;
				}
			}
			if (flag)
			{
				SlateFlag[i] = 1;//设置为需要移动到初始位置
			}
		
		}
	}
}