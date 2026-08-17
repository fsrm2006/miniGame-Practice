#include"../slbhr.h"
#include<graphics.h>
//IMAGE Slate, doorR, doorB, pSlate, panel, switch1, diamondR, diamondB, skinR, skinB;
void GameDraw()
{
	//优先级：核心
	//设计人：吴向前
	//负责人：
		//函数描述：此函数用于绘制游戏界面，包括背景、人物（人物图片路径用Player1ImgPath，Player2ImgPath）、机关（石板、门、压力板等）、钻石等元素的绘制；
		//逻辑说明：先绘制背景，然后根据NowSlatePos数组绘制石板，根据DoorFlag数组绘制门的状态，
		//根据PanelFlag和SwitchFlag数组绘制压力板和开关的状态，然后根据DiamondFlag数组绘制钻石的状态，最后绘制人物；
		//如有疑问欢迎询问
		//返回值：无

	BeginBatchDraw();

	int len, wid, i;
	if (NowLevel == 0) {
		loadimage(NULL, L"resource\\Image resource\\maps\\map1.jpg", 1024, 768);
		len = 100;
		wid = 30;
	}
	else if (NowLevel == 1) {
		len = 80;
		wid = 30;
		loadimage(NULL, L"resource\\Image resource\\maps\\map2.jpg", 1024, 768);
	}
	else {
		len = 80;
		wid = 25;
		loadimage(NULL, L"resource\\Image resource\\maps\\map3.jpg", 1024, 768);
	}
	IMAGE Slate, Slate2, SlateV, SlateV2;
	if (NowLevel == 2) {
		loadimage(&SlateV, L"resource\\Image resource\\Switch and Slate\\switch slate virtical.jpg", wid, len);
		loadimage(&SlateV2, L"resource\\Image resource\\Switch and Slate\\switch slate virtical2.jpg", wid, len);
		putimage(NowSlatePos[1][0], NowSlatePos[1][1], &SlateV2, SRCAND);
		putimage(NowSlatePos[1][0], NowSlatePos[1][1], &SlateV, SRCPAINT);
		for (i = 0; i < SwitchNum[NowLevel]; i++) {
			if (i != 1) {
				loadimage(&Slate, L"resource\\Image resource\\Switch and Slate\\switch slate.jpg", len, wid);
				loadimage(&Slate2, L"resource\\Image resource\\Switch and Slate\\switch slate2.jpg", len, wid);
				putimage(NowSlatePos[i][0], NowSlatePos[i][1], &Slate2, SRCAND);
				putimage(NowSlatePos[i][0], NowSlatePos[i][1], &Slate, SRCPAINT);
			}
		}
	}
	else {
		for (i = 0; i < SwitchNum[NowLevel]; i++) {
			loadimage(&Slate, L"resource\\Image resource\\Switch and Slate\\switch slate.jpg", len, wid);
			loadimage(&Slate2, L"resource\\Image resource\\Switch and Slate\\switch slate2.jpg", len, wid);
			putimage(NowSlatePos[i][0], NowSlatePos[i][1], &Slate2, SRCAND);
			putimage(NowSlatePos[i][0], NowSlatePos[i][1], &Slate, SRCPAINT);
		}
	}

	IMAGE doorR, doorB, doorR2, doorB2;
	if (NowLevel == 0) {
		if (DoorFlag[0] == 0) {
			loadimage(&doorB, L"resource\\Image resource\\Door\\blue door.jpg", 60, 70);
			loadimage(&doorB2, L"resource\\Image resource\\Door\\blue door2.jpg", 60, 70);
		}
		else {
			loadimage(&doorB, L"resource/Image resource/Door/door open.jpg", 60, 70);
			loadimage(&doorB2, L"resource/Image resource/Door/door open2.jpg", 60, 70);
		}
		if (DoorFlag[1] == 0) {
			loadimage(&doorR, L"resource\\Image resource\\Door\\red door.jpg", 60, 70);
			loadimage(&doorR2, L"resource\\Image resource\\Door\\red door2.jpg", 60, 70);
		}
		else {
			loadimage(&doorR, L"resource/Image resource/Door/door open.jpg", 60, 70);
			loadimage(&doorR2, L"resource/Image resource/Door/door open2.jpg", 60, 70);
		}
		putimage(DoorVolume[NowLevel][1][0], DoorVolume[NowLevel][1][1], &doorR2, SRCAND);
		putimage(DoorVolume[NowLevel][1][0], DoorVolume[NowLevel][1][1], &doorR, SRCPAINT);
		putimage(DoorVolume[NowLevel][0][0], DoorVolume[NowLevel][0][1], &doorB2, SRCAND);
		putimage(DoorVolume[NowLevel][0][0], DoorVolume[NowLevel][0][1], &doorB, SRCPAINT);
	}
	else if (NowLevel == 1) {
		if (DoorFlag[0] == 1) {
			loadimage(&doorB, L"resource/Image resource/Door/map3 door open.jpg", 72, 80);
			loadimage(&doorB2, L"resource/Image resource/Door/map2 door open2.jpg", 72, 80);
		}
		if (DoorFlag[1] == 1) {
			loadimage(&doorR, L"resource/Image resource/Door/map3 door open.jpg", 72, 80);
			loadimage(&doorR2, L"resource/Image resource/Door/map2 door open2.jpg", 72, 80);
		}
		putimage(DoorVolume[NowLevel][1][0], DoorVolume[NowLevel][1][1], &doorR2, SRCPAINT);
		putimage(DoorVolume[NowLevel][1][0], DoorVolume[NowLevel][1][1], &doorR, SRCAND);
		putimage(DoorVolume[NowLevel][0][0], DoorVolume[NowLevel][0][1], &doorB2, SRCPAINT);
		putimage(DoorVolume[NowLevel][0][0], DoorVolume[NowLevel][0][1], &doorB, SRCAND);
	}
	else if (NowLevel == 2) {
		if (DoorFlag[0] == 1) {
			loadimage(&doorB, L"resource/Image resource/Door/map3 door open.jpg", 72, 77);
			loadimage(&doorB2, L"resource/Image resource/Door/map3 door open2.jpg", 72, 77);
		}
		if (DoorFlag[1] == 1) {
			loadimage(&doorR, L"resource/Image resource/Door/map3 door open.jpg", 72, 77);
			loadimage(&doorR2, L"resource/Image resource/Door/map3 door open2.jpg", 72, 77);
		}
		putimage(DoorVolume[NowLevel][1][0], DoorVolume[NowLevel][1][1], &doorR2, SRCPAINT);
		putimage(DoorVolume[NowLevel][1][0], DoorVolume[NowLevel][1][1], &doorR, SRCAND);
		putimage(DoorVolume[NowLevel][0][0], DoorVolume[NowLevel][0][1], &doorB2, SRCPAINT);
		putimage(DoorVolume[NowLevel][0][0], DoorVolume[NowLevel][0][1], &doorB, SRCAND);
	}

	

	if (NowLevel == 0) {
		len = 100;
		wid = 30;
	}
	else if (NowLevel == 1) {
		len = 90;
		wid = 33;
	}
	else {
		len = 80;
		wid = 15;
	}
	IMAGE pSlate, pSlate2;
	loadimage(&pSlate, L"resource\\Image resource\\Panel and Slate\\panel slate.jpg", len, wid);
	loadimage(&pSlate2, L"resource\\Image resource\\Panel and Slate\\panel slate2.jpg", len, wid);
	for (i = 0; (i + SwitchSlateNum[NowLevel]) < SlateNum[NowLevel]; i++) {
		putimage(NowSlatePos[i + SwitchSlateNum[NowLevel]][0], NowSlatePos[i + SwitchSlateNum[NowLevel]][1], &pSlate2, SRCAND);
		putimage(NowSlatePos[i + SwitchSlateNum[NowLevel]][0], NowSlatePos[i + SwitchSlateNum[NowLevel]][1], &pSlate, SRCPAINT);
	}
	if (NowLevel == 0) {
		len = 50;
		wid = 16;
	}
	else if (NowLevel == 1) {
		len = 55;
		wid = 20;
	}
	else {
		len = 48;
		wid = 20;
	}
	IMAGE panel, panel2;
	for (i = 0; i < PanelNum[NowLevel]; i++) {
		if (PanelFlag[i] == 1) {
			loadimage(&panel, L"resource\\Image resource\\Panel and Slate\\panel down.jpg", len, wid);
			loadimage(&panel2, L"resource\\Image resource\\Panel and Slate\\panel down2.jpg", len, wid);
		}
		else {
			loadimage(&panel, L"resource\\Image resource\\Panel and Slate\\panel.jpg", len, wid);
			loadimage(&panel2, L"resource\\Image resource\\Panel and Slate\\panel2.jpg", len, wid);
		}
		putimage(PanelVolume[NowLevel][i][0], PanelVolume[NowLevel][i][1], &panel2, SRCAND);
		putimage(PanelVolume[NowLevel][i][0], PanelVolume[NowLevel][i][1], &panel, SRCPAINT);
	}

	IMAGE switch1, switch2;
	for (i = 0; i < SwitchNum[NowLevel]; i++) {
		if (SwitchFlag[i]) {
			loadimage(&switch1, L"resource\\Image resource\\Switch and Slate\\switch on.jpg", 50, 40);
			loadimage(&switch2, L"resource\\Image resource\\Switch and Slate\\switch on2.jpg", 50, 40);
		}
		else {
			loadimage(&switch1, L"resource\\Image resource\\Switch and Slate\\switch off.jpg", 50, 40);
			loadimage(&switch2, L"resource\\Image resource\\Switch and Slate\\switch off2.jpg", 50, 40);
		}
		putimage(SwitchVolume[NowLevel][i][0], SwitchVolume[NowLevel][i][1], &switch2, SRCAND);
		putimage(SwitchVolume[NowLevel][i][0], SwitchVolume[NowLevel][i][1], &switch1, SRCPAINT);
	}


	IMAGE diamondR, diamondB, diamondR2, diamondB2;
	loadimage(&diamondR, L"resource\\Image resource\\Diamond\\blue diamond.jpg", 35, 30);
	loadimage(&diamondB, L"resource\\Image resource\\Diamond\\red diamond.jpg", 35, 30);
	loadimage(&diamondR2, L"resource\\Image resource\\Diamond\\blue diamond2.jpg", 35, 30);
	loadimage(&diamondB2, L"resource\\Image resource\\Diamond\\red diamond2.jpg", 35, 30);
	for (i = 0; i < DiamondNum[NowLevel]; i++) {
		if (!DiamondFlag[i]) {
			if (i % 2 == 0) {
				putimage(DiamondVolume[NowLevel][i][0], DiamondVolume[NowLevel][i][1], &diamondR2, SRCAND);
				putimage(DiamondVolume[NowLevel][i][0], DiamondVolume[NowLevel][i][1], &diamondR, SRCPAINT);
			}
			else {
				putimage(DiamondVolume[NowLevel][i][0], DiamondVolume[NowLevel][i][1], &diamondB2, SRCAND);
				putimage(DiamondVolume[NowLevel][i][0], DiamondVolume[NowLevel][i][1], &diamondB, SRCPAINT);
			}
		}
	}

	// 显示尖刺
	ShowSpike(); 

	//显示人物
	IMAGE skinR, skinB, skinR2, skinB2;
	if (player1.ItemType == -1) {

		if (player1.jumptimes > 0) {
			if (player1.movdire == 1) {
				loadimage(&skinB, L"resource\\Image resource\\Skins\\blue leftjump.jpg", 53, 57);
				loadimage(&skinB2, L"resource\\Image resource\\Skins\\blue leftjump2.jpg", 53, 57);
			}
			else if (player1.movdire == 2) {
				loadimage(&skinB, L"resource/Image resource/Skins/blue rightjump.jpg", 53, 57);
				loadimage(&skinB2, L"resource/Image resource/Skins/blue rightjump2.jpg", 53, 57);
			}
			else if (player1.movdire == 0) {
				loadimage(&skinB, L"resource/Image resource/Skins/blue.jpg", 35, 57);
				loadimage(&skinB2, L"resource/Image resource/Skins/blue2.jpg", 35, 57);
			}
		}
		else if (player1.jumptimes == 0) {
			if (player1.movdire == 1) {
				loadimage(&skinB2, L"resource/Image resource/Skins/blue leftdown2.jpg", 40, 60);
				loadimage(&skinB, L"resource/Image resource/Skins/blue leftdown.jpg", 40, 60);
			}
			else if (player1.movdire == 2) {
				loadimage(&skinB, L"resource/Image resource/Skins/blue rightdown.jpg", 40, 60);
				loadimage(&skinB2, L"resource/Image resource/Skins/blue rightdown2.jpg", 40, 60);
			}
			else if (player1.movdire == 0) {
				loadimage(&skinB, L"resource/Image resource/Skins/blue.jpg", 35, 57);
				loadimage(&skinB2, L"resource/Image resource/Skins/blue2.jpg", 35, 57);
			}
		}
	}
	else if (player1.ItemType != -1) {
		if (player1.movdire == 1) {
			loadimage(&skinB, L"resource/Image resource/Skins/blue left.jpg", 53, 57);
			loadimage(&skinB2, L"resource/Image resource/Skins/blue left2.jpg", 53, 57);
		}
		else if (player1.movdire == 2) {
			loadimage(&skinB, L"resource/Image resource/Skins/blue right.jpg", 53, 57);
			loadimage(&skinB2, L"resource/Image resource/Skins/blue right2.jpg", 53, 57);
		}
		else if (player1.movdire == 0) {
			loadimage(&skinB, L"resource/Image resource/Skins/blue.jpg", 35, 57);
			loadimage(&skinB2, L"resource/Image resource/Skins/blue2.jpg", 35, 57);
		}
	}
	if (player2.ItemType == -1) {
		if (player2.jumptimes > 0) {
			if (player2.movdire == 1) {
				loadimage(&skinR, L"resource/Image resource/Skins/red leftjump.jpg", 45, 60);
				loadimage(&skinR2, L"resource/Image resource/Skins/red leftjump2.jpg", 45, 60);
			}
			else if (player2.movdire == 2) {
				loadimage(&skinR, L"resource/Image resource/Skins/red rightjump.jpg", 45, 60);
				loadimage(&skinR2, L"resource/Image resource/Skins/red rightjump2.jpg", 45, 60);
			}
			else if (player2.movdire == 0) {
				loadimage(&skinR, L"resource/Image resource/Skins/red.jpg", 35, 57);
				loadimage(&skinR2, L"resource/Image resource/Skins/red2.jpg", 35, 57);
			}
		}
		else if (player2.jumptimes == 0) {
			if (player2.movdire == 1) {
				loadimage(&skinR, L"resource/Image resource/Skins/red leftdown.jpg", 50, 60);
				loadimage(&skinR2, L"resource/Image resource/Skins/red leftdown2.jpg", 50, 60);
			}
			else if (player2.movdire == 2) {
				loadimage(&skinR, L"resource/Image resource/Skins/red rightdown.jpg", 50, 60);
				loadimage(&skinR2, L"resource/Image resource/Skins/red rightdown2.jpg", 50, 60);
			}
			else if (player2.movdire == 0) {
				loadimage(&skinR, L"resource/Image resource/Skins/red.jpg", 35, 57);
				loadimage(&skinR2, L"resource/Image resource/Skins/red2.jpg", 35, 57);
			}
		}
	}
	else if (player2.ItemType !=-1) {
		if (player2.movdire == 1) {
			loadimage(&skinR, L"resource/Image resource/Skins/red left.jpg", 50, 57);
			loadimage(&skinR2, L"resource/Image resource/Skins/red left2.jpg", 50, 57);
		}
		else if (player2.movdire == 2) {
			loadimage(&skinR, L"resource/Image resource/Skins/red right.jpg", 50, 57);
			loadimage(&skinR2, L"resource/Image resource/Skins/red right2.jpg", 50, 57);
		}
		else if (player2.movdire == 0) {
			loadimage(&skinR, L"resource/Image resource/Skins/red.jpg", 35, 57);
			loadimage(&skinR2, L"resource/Image resource/Skins/red2.jpg", 35, 57);
		}
	}
	putimage(player2.xl, player2.yl-10, &skinR2, SRCAND);
	putimage(player2.xl, player2.yl-10, &skinR, SRCPAINT);
	putimage(player1.xl, player1.yl-10, &skinB2, SRCAND);
	putimage(player1.xl, player1.yl-10, &skinB, SRCPAINT);
	FlushBatchDraw();
	EndBatchDraw();
}