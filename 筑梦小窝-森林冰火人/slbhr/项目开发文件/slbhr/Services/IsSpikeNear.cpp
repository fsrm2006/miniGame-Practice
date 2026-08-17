#include"../slbhr.h"
#include<stdio.h>
bool IsAABBCollide(int l1, int t1, int r1, int b1, int l2, int t2, int r2, int b2);
void IsSpikeNear()
{

	for (int i = 0; i < SpikeNum[NowLevel]; i++)
	{
		int flag = 0;
		int* SpikeShow = SpikeShowVolume[NowLevel][i];
		if (IsAABBCollide(player1.xl,player1.yl, player1.xr, player1.yr,SpikeShow[0], SpikeShow[1], SpikeShow[2], SpikeShow[3]))
		{
			flag = 1;
		}
		if (IsAABBCollide(player2.xl, player2.yl, player2.xr, player2.yr, SpikeShow[0], SpikeShow[1], SpikeShow[2], SpikeShow[3]))
		{
			flag = 1;
		}
		if (flag)
		{
			printf("Debug: Spike %d is near a player.\n", i);
			SpikeFlag[i] = 1;//ÉèÖÃÎªÏÔÊ¾¼â´Ì
		}
		else
		{
			SpikeFlag[i] = 0;//ÉèÖÃÎªÒþ²Ø¼â´Ì
		}
	}
}