#include<conio.h>
#include"slbhr.h"
#include<stdio.h>
#include<graphics.h>
int main()
{
	initgraph(1024, 768);
	PlayBGM(9);//播放跳伞
	selectedMusic = 10;
	VolumeChange(2); //设置为中等音量
	ViewMenu();
	return 0;
}
