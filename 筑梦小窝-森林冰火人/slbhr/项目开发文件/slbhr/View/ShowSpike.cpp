#include"../slbhr.h"
#include"graphics.h"

void ShowSpike()
{
	int Width[3] = { 40,50,40 };//每一关刺的宽度	
	int Height[3] = { 30,40,30 };//每一关刺的高度
	for (int i = 0; i < SpikeNum[NowLevel]; i++)
	{
		if (SpikeFlag[i])
		{
			IMAGE Spike1, Spike2;
			int *s = SpikeVolume[NowLevel][i];
			loadimage(&Spike1, L"resource\\Image resource\\Spike\\1.jpg", Width[NowLevel], Height[NowLevel]);
			loadimage(&Spike2, L"resource\\Image resource\\Spike\\0.jpg", Width[NowLevel], Height[NowLevel]);
			putimage(s[2], s[1], &Spike2, SRCAND);
			putimage(s[2], s[1], &Spike1, SRCPAINT);
		}
			
	}
}