#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define USER_FILE "game_records.txt"
#define MAX_NAME_LEN 32

void gotoXY(int x, int y)
{

	COORD c;
	c.X = x - 1;
	c.Y = y - 1;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setPrintColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Mention:各块负责人之后讨论决定
//chw 
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_ORANGE  "\033[38;5;208m" // 橙色
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_CYAN    "\033[1;36m"     // 青色
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_PURPLE  "\033[1;35m"  
#define COLOR_MAGENTA "\033[36m"
//chw
int art=0;
//lyq 
int lyq;
char name2[100];
//lyq
//------黄豆
int flag = 0;
int c = 0;
int q = 0;
int arrcheck[8][2] = { {1,0},{0,-1},{-1,0},{0,1},{1,1},{-1,-1},{1,-1},{-1,1} };//x,y四周检索
int xcheck[2][400], ycheck[2][400];
int ghost();
int sarr[15][15];
int huang=0;//0游客

//------黄豆
//------cjq
int turn;
int bian=0;//init 
//------cjq
//lz 
int a3 = 1;
//lz 
//zdl 
//lz
int js1 = 2; int js2 = 1;
//lz
int Zdl1 = 2;
char Zdl2, Zdl3, Zdl3;
int volume=1000;//目前游戏音量
void wozhenshuaiguangbiao();//我真帅光标
void chuangbiao();
void suijibiao();
//zdl
//--------------------数据设计-----------------------
/*
	地图:
		根据难度或模式不同init不同地图的大小
		n变量记录
		(i,j)范围随地图大小改变
*/
int board[15][15];//背盘  0表示空格 1-8表示数字 666及以上表示地雷   

int boom;//地雷数量
int open;//打开格子数量
int total;//格子总数


int front_map[15][15];//用户输出的表盘 用户看到的界面  


int open_map[15][15];//用于标记已经打开过的格子的背盘2  每显示一个格子就标记对应的格子为1  防止重复打开


int flag_map[15][15];//插旗位置的表盘  

/*
	闯关模式游戏关卡地图
	选中关卡后 将对应元素值 赋值给map
	比如选中第3关 将chooseMap[2]的内容 赋值给map
*/

//记录步数
int step;

//--------------------数据设计-----------------------
//--------------------service-----------------------
/*核心
	负责人：陈家褀
	功能:初始化游戏数据
		给背盘board赋值相应关卡的值（优先设计闯关模式已经预设好的地图）（到时候拓展设计随机模式随机地图）
		step,time初始化
		根据不同关卡初始化boom和open以及total;
	参数:
		设置变量不同关卡
		i代表类型(挑战模式和随机模式均用数字表示)//闯关模式：1-5数字，随机模式：简单：6 普通：7 困难：8；

	返回值:void
*/
void init(int i);
/*核心
* 负责人：椰丝黄豆
	功能:打开此格子
		如果是空格,探索周围格子扩散显示
		如果不是炸弹，就返回0
		如果是炸弹，就返回1
		记录步数
	返回值 0/1
	参数：
*/
int explorer(int x, int y);
/*
	负责人：
	功能：胜利判断
	如果打开的棋盘数等于总棋盘数减去地雷数量就判断为胜利
*/
int isWin();
//--------------------service-----------------------
//--------------------view--------------------------

/*核心
* 负责人：吴向前

	功能:展示主菜单界面
		while(1){
			1. 展示选项
			2. 用户输入ws选择选项（高光处理）
			3. 根据输入进行对应处理{
				*1.开始游戏 调用游戏界面函数
				*2.游戏设置 调用设置界面函数
				3.排行榜  调用排行榜界面函数
				4.注册  调用注册界面函数
				5.团队介绍  调用介绍界面函数
				*6.退出exit(0);
		}
		参数:void
		返回值:void
		开发的时候界面都写上吧，相应界面没有的就打印个敬请期待好了
*/
void view_menu();
/*非核心
* 负责人：陈韩伟
	功能:展示团队人员及特别鸣谢 内容可以按照原型图来打印
	参数:void
	返回值:void
*/
void view_Introduce();
/*非核心
* 负责人：钟德铃
	功能:展示模式界面
		while(1){
			1.闯关模式
			2.随机模式
			3.趣味模式
		}
		while(1){
			难度选择/模式选择
		}
*/
void view_choice();
/*核心
	负责人：王星耀
	游戏界面
	功能:
		1.打印表盘，用中文以及数字表示
	拓展2.插旗
		2.记录步数
	拓展	3.道具使用(暂定)
		4.计时
		5.判断胜负
*/
void view_game();
/*核心
	负责人：李嘉伟
	功能:1.展示最终界面
		{
		胜利/失败-----您用时,走了sum步
		}
		2.反悔
		3.再玩/游戏菜单
	参数:i
		0表示胜利
		1表示失败(多打印反悔)
	参数:sum
		传入步数
*/
void view_Final(int i, int sum);
int sign(const char* name, int i);
void save_game_record(const char* name, int steps);
void show_game_records();
void view_sign();
void view_timeout();
void Setting(int i);
void view_Setting();
void soybean();
void setting_bgmbiao();
void setting_guang();
int plant_flag(int x, int y);
void game_prop();
void view_Setting2();
//--------------------view-----------------------

int main(){
	Setting(11);
    view_menu();
	return 0;
}

void soybean() {
	step = 0;
	for (int i = 0;i<15;i++) {
		for (int j = 0;j<15;j++) {
			front_map[i][j] = 0;
		}
	}
	if (turn >= 6 && turn <= 8)init(turn);
	view_game();
}
void view_menu()
{
	caidan:system("cls");
	int n = 0, t = 1, c2;
	int line = 2;
	int choice = 1;
	char confirm = 'm';
	printf("=========================================\n");
	printf("||       ");//8
	setPrintColor(0x0C);
	printf("扫雷");
	setPrintColor(0x0E);
	printf("v2.0 ");
	setPrintColor(0x0A);
	printf("by.");
	setPrintColor(0x09);
	printf("筑梦小窝");
	setPrintColor(0x07);
	printf("         ||\n");
	printf("||            "); printf("\033[1;31;43m1.开始游戏\033[0m"); printf("              ||\n");//14  16//   \033[1;31;44m    //  \033[0m\n  //              ||
	printf("||          2.注册新的用户名          ||\n");//12   12
	printf("||              3.设置                ||\n");//16   18
	printf("||             4.排行榜               ||\n");//15   17
	printf("||       5.制作者名单和特别鸣谢       ||\n");//9    9
	printf("||              6.退出                ||\n");//17   18
	printf("||");
	printf(COLOR_PURPLE"	    W/S选择 回车确定          "COLOR_RESET);
	printf("||\n");
	printf("=========================================");
	gotoXY(1, line + 1);
	while (1) {
	start:

		c2 = _getch();
		//向上移动

		switch (c2) {
		case 'w':
		case 'W':

			if(t>1)
			t--;
			if (choice > 1) 
			{
				choice--; if (choice == 5)
				{
					printf("\r");
					printf("||              6.退出                ||");

					line--;
					printf("\r");
					gotoXY(10, choice + 2);

					printf("\033[1;31;43m5.制作者名单和特别鸣谢\033[0m"); printf("       ||");
				}
				if (choice == 4)
				{
					printf("\r");
					printf("||       5.制作者名单和特别鸣谢       ||");
					line--;
					printf("\r");
					gotoXY(16, choice + 2);

					printf("\033[1;31;43m4.排行榜\033[0m"); printf("               ||");
				}
				if (choice == 3) 
				{
					printf("\r");
					printf("||             4.排行榜               ||");
					line--;
					printf("\r");
					gotoXY(17, choice + 2);

					printf("\033[1;31;43m3.设置\033[0m"); printf("                ||");
				}if (choice == 2) {
					printf("\r");
					printf("||              3.设置                ||");
					line--;
					printf("\r");
					gotoXY(13, choice + 2);

					printf("\033[1;31;43m2.注册新的用户名\033[0m"); printf("          ||");
				} if (choice == 1) {
					printf("\r");
					printf("||          2.注册新的用户名          ||");
					line--;
					printf("\r");
					gotoXY(15, choice + 2);

					printf("\033[1;31;43m1.开始游戏\033[0m"); printf("              ||");

				}

				break;
			}
			break;
			//向下移动
		case 's':
		case 'S':
			if (t<6)
				t++; 
			if (choice < 6) {
				choice++;
				if (choice == 2) {

					printf("\r");
					printf("||            1.开始游戏              ||");
					line++;
					printf("\r");
					gotoXY(13, choice + 2);

					printf("\033[1;31;43m2.注册新的用户名\033[0m"); printf("          ||");

				}
				if (choice == 3) {
					printf("\r");
					printf("||          2.注册新的用户名          ||");

					line++;
					printf("\r");
					gotoXY(17, choice + 2);

					printf("\033[1;31;43m3.设置\033[0m"); printf("                ||");

				}
				if (choice == 4) {
					printf("\r");
					printf("||              3.设置                ||");

					line++;
					printf("\r");
					gotoXY(16, choice + 2);

					printf("\033[1;31;43m4.排行榜\033[0m"); printf("               ||");

				}if (choice == 5) {
					printf("\r");
					printf("||             4.排行榜               ||");

					line++;
					printf("\r");
					gotoXY(10, choice + 2);

					printf("\033[1;31;43m5.制作者名单和特别鸣谢\033[0m"); printf("       ||");

				} if (choice == 6) {
					printf("\r");
					printf("||       5.制作者名单和特别鸣谢       ||");
					line++;
					printf("\r");
					gotoXY(17, choice + 2);

					printf("\033[1;31;43m6.退出\033[0m"); printf("                ||");

				}


			}

			break;

		case'\r':

			if (t == 1) {
				view_choice();
				break;
			}
			if (t == 2) {
				view_sign();
				//注册界面函数
				break;
			}
			if (t == 3) {
				view_Setting();
				//设置界面；
				break;
			}
			if (t == 4) {
				system("cls");
				printf("该功能开发中，敬请期待，将在2秒后返回");
				Sleep(1800);
				goto caidan;
				break;
			}
			if (t == 5) {
				view_Introduce();
			}
			if (t == 6) {
				system("cls");
				printf("欢迎下次光临");
				exit(0); break;
			}
			break;
		}
	}
}

void view_Setting() 
{
	system("cls");
	js1 = 2;
	printf("=======================================\n");
	printf("||");
	printf(COLOR_CYAN"             设置界面:             "COLOR_RESET);
	printf("||\n");
	printf("||            1. 选择BGM             ||\n");
	printf("||            2. 关闭BGM             ||\n");
	printf("||            3. 开启音效            ||\n");
	printf("||            4. 关闭音效            ||\n");
	printf("||            5. 调节音量            ||\n");
	printf("||             6. 返回               ||\n");
	printf("||");
	printf(COLOR_PURPLE"	    W/S选择 回车确定         "COLOR_RESET);
	printf("||\n");
	printf("=======================================\n");
	setting_guang();
	gotoXY(15, js1 + 1);
	while (1) {
		char confirmsetting = 'm';
		confirmsetting = _getch();
		switch (confirmsetting) {
		case 'w':
		case 'W':
			if (js1 <= 2) {
				js1++;
			}
			js1--;
			setting_guang();
			break;
		case 's':
		case 'S':
			if (js1 >= 7) {
				js1--;
			}
			js1++;
			setting_guang();
			break;
		case '\r':
			switch (js1) {
			case 2:
				goto bgm; // 切换BGM
				break;
			case 3:
				Setting(-1); // 关闭BGM
				view_Setting();
				break;
			case 4:
				Setting(1); // 开启音效
				view_Setting();
				break;
			case 5:
				Setting(-2); // 关闭音效
				view_Setting();
				break;
			case 6:
				Setting(3); // 调节音量
				view_Setting();
				break;
			case 7:
				system("cls");
				view_menu(); // 返回主界面
				break;
			default:
				printf("输入错误，请重试。\n");
				Sleep(1000); // 暂停
				break;
			}



		}
	}
bgm:    system("cls");
	wchar_t cmd[128];
	int j, ret;
	printf("=====================================\n");
	printf("||");
	printf(COLOR_CYAN"            歌单如下             "COLOR_RESET);
	printf("||\n");
	printf("||           1. 又活了一天         ||\n");
	printf("||           2. 出山               ||\n");
	printf("||           3. 辞·九门回忆        ||\n");
	printf("||           4. こんにちは太陽     ||\n");
	printf("||           5. 光辉岁月           ||\n");
	printf("||           6. 跳伞               ||\n");
	printf("||           7. 神秘彩蛋           ||\n");
	printf("||           8. See you again      ||\n");
	printf("||           9. 坤坤进行曲         ||\n");
	printf("||           10. The des Alize     ||\n");
	printf("||           11. 返回              ||\n");
	printf("||           请选择BGM:            ||\n");
	printf("||");
	printf(COLOR_PURPLE"	   W/S选择 回车确定        "COLOR_RESET);
	printf("||\n");
	printf("=====================================\n");
	for (j = 1; j <= 10; j++) {
		swprintf(cmd, 128, L"close bgm%d", j);
		mciSendString(cmd, NULL, 0, NULL);
	}
	setting_bgmbiao();
	gotoXY(14, js1 + 1);
	while (1)
	{
		char confirmchuang = 'm';
		confirmchuang = _getch();
		switch (confirmchuang) 
		{
		case 'w':
		case 'W':
			if (js1 <= 2) {
				js1++;
			}
			js1--;
			setting_bgmbiao();
			break;
		case 's':
		case 'S':
			if (js1 >= 12) {
				js1--;
			}
			js1++;
			setting_bgmbiao();
			break;
		case '\r':
			switch (js1) 
			{
			case 2:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
					ret = mciSendString(L"open \"bgm1.mp3\" alias bgm1", NULL, 0, NULL);
					if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
					mciSendString(L"play bgm1 repeat", NULL, 0, NULL);
					for (j = 1; j <= 10; j++) {
						swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
						mciSendString(cmd, NULL, 0, NULL);
					}
					break;
			case 3:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm2.mp3\" alias bgm2", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm2 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
			case 4:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm3.mp3\" alias bgm3", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm3 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
			case 5:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm4.mp3\" alias bgm4", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm4 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
			case 6:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm5.mp3\" alias bgm5", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm5 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
			case 7:

				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm6.mp3\" alias bgm6", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm6 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
			case 8:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm7.mp3\" alias bgm7", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm7 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
				//加的：
			case 9:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm8.mp3\" alias bgm8", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm8 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
			case 10:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm9.mp3\" alias bgm9", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm9 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
			case 11:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm10.mp3\" alias bgm10", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm10 repeat", NULL, 0, NULL);
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
					mciSendString(cmd, NULL, 0, NULL);
				}
				break;
			case 12:
				view_Setting();
				break;
			default:
				printf("输入错误，请重试。\n");
				Sleep(1000);
			}
				break;
		}
	}
}


void setting_guang()
{
	switch (js1) {
	case 2:
		printf("\r");
		gotoXY(15, js1 + 2);
		printf("2. 关闭BGM");
		printf("\r");
		gotoXY(15, js1 + 1);
		printf("\033[1;31;43m1. 选择BGM\033[0m");
		break;
	case 3:
		printf("\r");
		gotoXY(15, js1);
		printf("1. 选择BGM");
		printf("\r");
		gotoXY(15, js1 + 2);
		printf("3. 开启音效");
		printf("\r");
		gotoXY(15, js1 + 1);
		printf("\033[1;31;43m2. 关闭BGM\033[0m");
		break;
	case 4:
		printf("\r");
		gotoXY(15, js1);
		printf("2. 关闭BGM");
		printf("\r");
		gotoXY(15, js1 + 2);
		printf("4. 关闭音效");
		printf("\r");
		gotoXY(15, js1 + 1);
		printf("\033[1;31;43m3. 开启音效\033[0m");
		break;
	case 5:
		printf("\r");
		gotoXY(15, js1);
		printf("3. 开启音效");
		printf("\r");
		gotoXY(15, js1 + 2);
		printf("5. 调节音量");
		printf("\r");
		gotoXY(15, js1 + 1);
		printf("\033[1;31;43m4. 关闭音效\033[0m");
		break;
	case 6:
		printf("\r");
		gotoXY(15, js1);
		printf("4. 关闭音效");
		printf("\r");
		gotoXY(16, js1 + 2);
		printf("6. 返回");
		printf("\r");
		gotoXY(15, js1 + 1);
		printf("\033[1;31;43m5. 调节音量\033[0m");
		break;
	case 7:
		printf("\r");
		gotoXY(15, js1);
		printf("5. 调节音量");
		printf("\r");
		gotoXY(16, js1 + 1);
		printf("\033[1;31;43m6. 返回\033[0m");
		break;
	default:
		Sleep(1);
		break;
	}
}

void setting_bgmbiao()
{
	switch (js1) {
	case 2:
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("2. 出山");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m1. 又活了一天\033[0m");
		break;
	case 3:
		printf("\r");
		gotoXY(14, js1);
		printf("1. 又活了一天");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("3. 辞·九门回忆");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m2. 出山\033[0m");
		break;
	case 4:
		printf("\r");
		gotoXY(14, js1);
		printf("2. 出山");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("4. こんにちは太陽");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m3. 辞·九门回忆\033[0m");
		break;
	case 5:
		printf("\r");
		gotoXY(14, js1);
		printf("3. 辞·九门回忆");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("5. 光辉岁月");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m4. こんにちは太陽\033[0m");
		break;
	case 6:
		printf("\r");
		gotoXY(14, js1);
		printf("4. こんにちは太陽");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("6. 跳伞");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m5. 光辉岁月\033[0m");
		break;
	case 7:
		printf("\r");
		gotoXY(14, js1);
		printf("5. 光辉岁月");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("7. 神秘彩蛋");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m6. 跳伞\033[0m");
		break;
	case 8:
		printf("\r");
		gotoXY(14, js1);
		printf("6. 跳伞");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("8. See you again");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m7. 神秘彩蛋\033[0m");
		break;
	case 9:
		printf("\r");
		gotoXY(14, js1);
		printf("7. 神秘彩蛋");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("9. 坤坤进行曲");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m8. See you again\033[0m");
		break;
	case 10:
		printf("\r");
		gotoXY(14, js1);
		printf("8. See you again");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("10. The des Alize");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m9. 坤坤进行曲\033[0m");
		break;
	case 11:
		printf("\r");
		gotoXY(14, js1);
		printf("9. 坤坤进行曲");
		printf("\r");
		gotoXY(14, js1 + 2);
		printf("11. 返回");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m10. The des Alize\033[0m");
		break;
	case 12:
		printf("\r");
		gotoXY(14, js1);
		printf("10. The des Alize");
		printf("\r");
		gotoXY(14, js1 + 1);
		printf("\033[1;31;43m11. 返回\033[0m");
		break;
	default:
		Sleep(1);
		break;
	}
}

void Setting(int i)
{
	int j, ret;
	wchar_t cmd[128];
	switch (i) {

	case 1:
		system("cls");
		js2 = 1;
		printf("开启音效成功\n");
		Sleep(1000);
		break;
	case -1:
		system("cls");
		for (j = 1; j <= 10; j++) {
			swprintf(cmd, 128, L"close bgm%d", j);
			mciSendString(cmd, NULL, 0, NULL);
		}
		printf("BGM已关闭。\n");
		Sleep(1000);
		break;
	case -2:
		system("cls");
		js2 = 0;
		printf("关闭音效成功\n");
		Sleep(1000);
		break;
	case 3:
		system("cls");
		printf("请输入音量(0~1000): ");
		scanf_s("%d", &volume);
		system("cls");
		if (volume > 1000 || volume < 0)
		{
			printf("调节音量失败，请输入范围内的数值");
		}
		else
			printf("调节音量成功");
		for (j = 1; j <= 10; j++) {
			swprintf(cmd, 128, L"setaudio bgm%d volume to %d", j, volume);
			mciSendString(cmd, NULL, 0, NULL);
		}
		Sleep(1000);
		break;
	case 7:
		if (js2 == 0) break;
		mciSendString(L"close boom", NULL, 0, NULL); // 先关闭,避免音效重叠
		ret = mciSendString(L"open \"boom.mp3\" type mpegvideo alias boom", NULL, 0, NULL);
		if (ret != 0) printf("打开音效失败，错误码：%d\n", ret);
		mciSendString(L"play boom", NULL, 0, NULL);
		break;
	case 8:
		if (js2 == 0) break;
		mciSendString(L"close succeed", NULL, 0, NULL);
		ret = mciSendString(L"open \"succeed.mp3\" type mpegvideo alias succeed", NULL, 0, NULL);
		if (ret != 0) printf("打开音效失败，错误码：%d\n", ret);
		mciSendString(L"play succeed", NULL, 0, NULL);
		break;
	case 9:
		if (js2 == 0) break;
		for (j = 1; j <= 7; j++) {
			swprintf(cmd, 128, L"close bgm%d", j);
			mciSendString(cmd, NULL, 0, NULL);
		}
		mciSendString(L"close bgm7", NULL, 0, NULL);
		ret = mciSendString(L"open \"bgm7.mp3\" type mpegvideo alias bgm7", NULL, 0, NULL);
		if (ret != 0) printf("打开音效失败，错误码：%d\n", ret);
		mciSendString(L"play bgm7 repeat", NULL, 0, NULL);
		break;
	case 10:
		if (js2 == 0) break;
		mciSendString(L"close click", NULL, 0, NULL);
		ret = mciSendString(L"open \"click.mp3\" type mpegvideo alias click", NULL, 0, NULL);
		if (ret != 0) printf("打开音效失败，错误码：%d\n", ret);
		mciSendString(L"play click", NULL, 0, NULL);
		break;
	case 11:
		ret = mciSendString(L"open \"bgm6.mp3\" alias bgm6", NULL, 0, NULL);
		if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
		mciSendString(L"play bgm6 repeat", NULL, 0, NULL);
		break;
	}

}

int sign(const char* name, int i) {
	FILE* fp;
	char buf[MAX_NAME_LEN];  //是用来保存每次从文件读取的用户名字符串，为后续的字符串比较和查找做准备
	int exists = 0;

	// 检查用户名是否存在
	fp = fopen(USER_FILE, "r");
	if (fp) {
		while (fgets(buf, sizeof(buf), fp)) {
			buf[strcspn(buf, "\r\n")] = 0;
			//strcspn(buf, "\r\n") 的作用是查找 buf 中第一个出现 \r 或 \n 的位置
			//buf[...] = 0; 就是在这个位置上放一个字符串结束符 \0，把换行或回车截断掉
			//这样处理后，buf 只保留用户名本身，没有结尾的换行或回车，便于后续用 strcmp(buf, name) 进行字符串比较
			//PS:此处问的AI
			if (strcmp(buf, name) == 0) {
				exists = 1;
				break;
			}
		}
		fclose(fp);
	}

	if (i == 0) { // 登录
		if (exists) {
			printf("登录成功！\n");
			huang = 0;
			return 0;
		}
		else {
			printf("登录失败，用户名不存在。\n");
			huang = 1;
			return 1;
		}
	}
	else if (i == 1) { // 注册
		if (exists) {
			printf("注册失败，用户名已存在。\n");
			huang = 1;
			return 1;
		}
		else {
			fp = fopen(USER_FILE, "a");
			if (!fp) {
				printf("无法打开用户文件。\n");
				huang = 1;
				return 1;
			}
			fprintf(fp, "%s\n", name);
			fclose(fp);
			printf("注册成功！\n");
			huang = 0;
			return 0;
		}
	}
	printf("参数错误。\n");
	huang = 1;
	return 1;
}

void view_sign() {
	int userChoose = 0;
	char name[MAX_NAME_LEN];

	system("cls");
	while (1) {
		// 打印界面
		gotoXY(10, 2);
		printf("=====================");
		gotoXY(10, 3);
		printf("||                 ||");
		gotoXY(10, 4);
		printf("||                 ||");
		gotoXY(10, 5);
		printf("||                 ||");
		gotoXY(10, 6);
		printf("||                 ||");
		gotoXY(10, 7);
		printf("||                 ||");
		gotoXY(10, 8);
		printf("=====================");
		gotoXY(10, 9);
		printf(COLOR_PURPLE"请选择操作（w/s切换，回车确认"COLOR_RESET);
		gotoXY(10, 10);
		printf(COLOR_CYAN"ESC返回"COLOR_RESET);

		// 高亮当前选项
		if (userChoose == 0) {
			gotoXY(16, 4);
			setPrintColor(0x6f);
			printf("1.登录");
			setPrintColor(0x0f);
			gotoXY(16, 6);
			printf("2.注册");
		}
		else {
			gotoXY(16, 4);
			printf("1.登录");
			gotoXY(16, 6);
			setPrintColor(0x6f);
			printf("2.注册");
			setPrintColor(0x0f);
		}

		// 接收用户输入
		char input = _getch();
		if (input == 'w' || input == 'W') {
			userChoose = (userChoose == 0) ? 1 : 0;
		}
		else if (input == 's' || input == 'S') {
			userChoose = (userChoose == 1) ? 0 : 1;
		}
		else if (input == 0x1B) {
			view_menu();
		}
		else if (input == '\r') {
			system("cls");
			printf("请输入用户名：");
			scanf("%31s", name);
			//失败1
			if (userChoose == 0) {
				lyq = sign(name, 0);
			}
			else {
				lyq = sign(name, 1);
			}
			Sleep(2000);
			view_sign();
			break;
		}
	}
}

void view_Introduce()
{
    // 清屏
    system("cls");

    printf("=======================================================\n");

    printf("||                                                   ||\n");

    printf("||");
    printf(COLOR_ORANGE "                     扫雷v2.0                      " COLOR_RESET);
    printf("||\n");

    printf("||                                                   ||\n");

    printf("||");
    printf(COLOR_YELLOW "                开发团队：筑梦小窝                 " COLOR_RESET);
    printf("||\n");

    printf("||");
    printf(COLOR_GREEN "                     开发人员：                    " COLOR_RESET);
    printf("||\n");

    printf("||");
    printf(COLOR_CYAN "                  组长：浮生若梦                   " COLOR_RESET);
    printf("||\n");

    printf("||");
    printf(COLOR_BLUE "                  副组长：林宇卿                   " COLOR_RESET);
    printf("||\n");

    printf("||");
    printf(COLOR_PURPLE "                   信息官：居士                    " COLOR_RESET);
    printf("||\n");

    printf("||");
    printf(COLOR_RED "       技术官：椰丝黄豆，白的黑，无相欠，望年      " COLOR_RESET);
    printf("||\n");

    printf("||");
    printf(COLOR_ORANGE "              产品经理：无言，Ricardo              " COLOR_RESET);
    printf("||\n");

    printf("||");
    printf(COLOR_YELLOW "        特别鸣谢：01星球以及01星球全体学长         " COLOR_RESET);
    printf("||\n");

    printf("||");
    printf(COLOR_GREEN "                  感谢您的游玩！                   " COLOR_RESET);
    printf("||\n");

    printf("||                                                   ||\n");

	printf("||");
	printf(COLOR_CYAN "               按ESC键返回上一界面                 " COLOR_RESET);
	printf("||\n");

	printf("||                                                   ||\n");


	printf("||");
	printf("                    开发分工：                     " );
	printf("||\n");

	printf("||                                                   ||\n");


	printf("||");
	printf(COLOR_RED "    浮生若梦：初始化，插旗，游戏道具，界面美化     " COLOR_RESET);
	printf("||\n");

	printf("||");
	printf(COLOR_ORANGE "     林宇卿：游戏注册，游戏排行榜，文件操作        " COLOR_RESET);
	printf("||\n");

	printf("||");
	printf(COLOR_YELLOW " 椰丝黄豆：扩散算法，暂停界面，揭开格子，代码整合  " COLOR_RESET);
	printf("||\n");

	printf("||");
	printf(COLOR_GREEN "            无相欠：游戏菜单，光标算法             " COLOR_RESET);
	printf("||\n");

	printf("||");
	printf(COLOR_CYAN "          白的黑：胜利/失败界面，光标算法          " COLOR_RESET);
	printf("||\n");

	printf("||");
	printf(COLOR_BLUE "        望年：游戏界面，光标移动，键入检测         " COLOR_RESET);
	printf("||\n");

	printf("||");
	printf(COLOR_PURPLE "        居士：设置界面，光标算法，音乐播放         " COLOR_RESET);
	printf("||\n");

	printf("||");
	printf(COLOR_ORANGE "          Ricardo：胜利判定，特别鸣谢界面          " COLOR_RESET);
	printf("||\n");

	printf("||");
	printf(COLOR_GREEN "            无言：模式选择界面，光标算法           " COLOR_RESET);
	printf("||\n");




    printf("||                                                   ||\n");

    printf("=======================================================\n");

    // 等待回车键
    while (1) {
        char ch = _getch();
        switch (ch) {
        case 0x1B:
            system("cls");
			view_menu();
            break;
        }
    }
}

void view_choice()
{
	system("cls");
	Zdl1 = 2;
	printf("========================================\n");
	printf("||");
	printf(COLOR_CYAN"         请选择你的游戏模式：       "COLOR_RESET);
	printf("||\n");
	printf("||             "); printf("\033[1;31;43m1.闯关模式\033[0m"); printf("             || \n");                  // \033[1;31;43m     \033[0m
	printf("||             2.随机模式             ||\n");
	printf("||             3.趣味模式             ||\n");
	printf("||               4.返回               ||\n");
	printf("||");
	printf(COLOR_PURPLE"	    W/S选择 回车确定          "COLOR_RESET);
	printf("||\n");
	if(huang == 1)printf("||          当前状态：游客            ||\n");
	else printf("||          当前状态：用户            ||\n");
	printf("========================================\n");
	gotoXY(16, Zdl1 + 1);
	while (1) {
		char confirm = 'm';
		confirm = _getch();
		switch (confirm) {
		case 'w':
		case 'W':
			if (Zdl1 <= 2) {
				Zdl1++;
			}
			Zdl1--;
			wozhenshuaiguangbiao();
			break;
		case 's':
		case 'S':
			if (Zdl1 >= 5) {
				Zdl1--;
			}
			Zdl1++;
			wozhenshuaiguangbiao();
			break;
		case '\r':
			switch (Zdl1) {
			case 2:
				goto chuangguan;
				break;
			case 3:
				system("cls");
				goto suiji;
				break;
			case 4:
				init(9);
				view_game();
				break;
			case 5:
				system("cls");
				view_menu();
				break;
			default:
				Sleep(1);
				break;
			}
			break;
		default:
			Sleep(1);
			break;
		}
	}

chuangguan:system("cls");
	Zdl1 = 2;
	printf("=======================================\n");
	printf("||");
	printf(COLOR_CYAN"          请选择您的关卡：         "COLOR_RESET);
	printf("||\n");
	printf("||              1.第一关             ||\n");
	printf("||             2.第二关              ||\n");
	printf("||             3.第三关              ||\n");
	printf("||             4.第四关              ||\n");
	printf("||             5.第五关              ||\n");
	printf("||              6.返回               ||\n");
	printf("||");
	printf(COLOR_PURPLE"	    W/S选择 回车确定         "COLOR_RESET);
	printf("||\n");
	printf("=======================================\n");
	chuangbiao();
	gotoXY(16, Zdl1 + 1);
	while (1) {
		char confirmchuang = 'm';
		confirmchuang = _getch();
		switch (confirmchuang) {
		case 'w':
		case 'W':
			if (Zdl1 <= 2) {
				Zdl1++;
			}
			Zdl1--;
			chuangbiao();
			break;
		case 's':
		case 'S':
			if (Zdl1 >= 7) {
				Zdl1--;
			}
			Zdl1++;
			chuangbiao();
			break;
		case '\r':
			switch (Zdl1) {
			case 2:
				system("cls");
				init(1);
				view_game();
				break;
			case 3:
				system("cls");
				init(2);
				view_game();
				break;
			case 4:
				system("cls");
				init(3);
				view_game();
				break;
			case 5:
				system("cls");
				init(4);
				view_game();
				break;
			case 6:
				system("cls");
				init(5);
				view_game();
				break;
			case 7:
				system("cls");
				view_choice();
			default:
				Sleep(1);
				break;
			}
		default:
			Sleep(1);
			break;
		}

	}
suiji:system("cls");
	Zdl1 = 2;
	printf("========================================\n");
	printf("||");
	printf(COLOR_CYAN"           请选择你的难度：         "COLOR_RESET);
	printf("||\n");
	printf("||             "); printf("\033[1;31;43m1.简单（5x5)\033[0m           ||\n");
	printf("||             2.普通（9x9）          ||\n");
	printf("||             3.困难（13x13）        ||\n");
	printf("||              4.返回                ||\n");
	printf("||");
	printf(COLOR_PURPLE"	    W/S选择 回车确定          "COLOR_RESET);
	printf("||\n");
	printf("========================================\n");
	gotoXY(16, Zdl1 + 1);
	while (1) {
		char confirm = 'm';
		confirm = _getch();
		switch (confirm) {
		case 'w':
		case 'W':
			if (Zdl1 <= 2) {
				Zdl1++;
			}
			Zdl1--;
			suijibiao();
			break;
		case 's':
		case 'S':
			if (Zdl1 >= 5) {
				Zdl1--;
			}
			Zdl1++;
			suijibiao();
			break;
		case '\r':
			switch (Zdl1) {
			case 2:
				system("cls");
				init(6);
				view_game();
				break;
			case 3:
				system("cls");
				init(7);
				view_game();
				break;
			case 4:
				system("cls");
				init(8);
				view_game();
				break;
			case 5:
				system("cls");
				view_choice();
			default:
				Sleep(1);
			}
			break;
		default:
			Sleep(1);
			break;
		}

	}
}

void wozhenshuaiguangbiao() {
	switch (Zdl1) {
	case 2:
		printf("\r");
		gotoXY(16, Zdl1 + 2);
		printf("2.随机模式");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m1.闯关模式\033[0m");
		break;
	case 3:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("1.闯关模式");
		printf("\r");
		gotoXY(16, Zdl1 + 2);
		printf("3.趣味模式");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m2.随机模式\033[0m");
		break;
	case 4:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("2.随机模式");
		printf("\r");
		gotoXY(18, Zdl1 + 2);
		printf("4.返回");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m3.趣味模式\033[0m");
		break;
	case 5:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("3.趣味模式");
		printf("\r");
		gotoXY(18, Zdl1 + 1);
		printf("\033[1;31;43m4.返回\033[0m");
		break;
	default:
		Sleep(1);
		break;
	}
}


void chuangbiao() {
	switch (Zdl1) {
	case 2:
		printf("\r");
		gotoXY(16, Zdl1 + 2);
		printf("2.第二关");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m1.第一关\033[0m");
		break;
	case 3:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("1.第一关");
		printf("\r");
		gotoXY(16, Zdl1 + 2);
		printf("3.第三关");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m2.第二关\033[0m");
		break;
	case 4:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("2.第二关");
		printf("\r");
		gotoXY(16, Zdl1 + 2);
		printf("4.第四关");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m3.第三关\033[0m");
		break;
	case 5:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("3.第三关");
		printf("\r");
		gotoXY(16, Zdl1 + 2);
		printf("5.第五关");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m4.第四关\033[0m");
		break;
	case 6:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("4.第四关");
		printf("\r");
		gotoXY(17, Zdl1 + 2);
		printf("6.返回");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m5.第五关\033[0m");
		break;
	case 7:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("5.第五关");
		printf("\r");
		gotoXY(17, Zdl1 + 1);
		printf("\033[1;31;43m6.返回\033[0m");
		break;
	default:
		Sleep(1);
		break;
	}
}
void suijibiao() {
	switch (Zdl1) {
	case 2:
		printf("\r");
		gotoXY(16, Zdl1 + 2);
		printf("2.普通（9x9)");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m1.简单（5x5)\033[0m");
		break;
	case 3:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("1.简单（5x5)");
		printf("\r");
		gotoXY(16, Zdl1 + 2);
		printf("3.困难（13x13)");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m2.普通（9x9)\033[0m");
		break;
	case 4:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("2.普通（9x9)");
		printf("\r");
		gotoXY(17, Zdl1 + 2);
		printf("4.返回");
		printf("\r");
		gotoXY(16, Zdl1 + 1);
		printf("\033[1;31;43m3.困难（13x13)\033[0m");
		break;
	case 5:
		printf("\r");
		gotoXY(16, Zdl1);
		printf("3.困难（13x13)");
		printf("\r");
		gotoXY(17, Zdl1 + 1);
		printf("\033[1;31;43m4.返回\033[0m");
		break;
	default:
		Sleep(1);
		break;
	}
}

void init(int i)
{
	for (int i = 0;i<bian;i++) {
		for (int j = 0;j<bian;j++) {
			front_map[i][j] = 0;
		}
	}
	turn = i;
	i--;
	int c_board[5][15][15] = {
	{{1,1,1,0,0,0},
	{1,666,2,1,1,0},
	{1,1,2,666,1,0},
	{0,1,2,2,2,0},
	{0,1,666,1,0,0},
	{0,1,1,1,0,0}
	},//第一关 3雷 6*6
	{{1,1,1,0,0,0,0 },
	 {1,666,1,0,1,1,1 },
	 {2,2,2,0,1,666,1 },
	 {1,666,1,1,2,2,1 },
	 {1,1,1,1,666,1,0 },
	 {0,0,1,2,2,1,0},
	 {0,0,1,666,1,0,0}
	},//第二关	5雷 7*7
	{{0,1,1,1,0,0,0,0,0},
	{0,1,666,1,0,0,1,1,1},
	{1,2,2,1,0,0,1,666,1},
	{1,666,1,0,1,1,2,1,1},
	{1,1,2,1,2,666,1,0,0},
	{0,0,1,666,2,1,1,0,0},
	{0,1,2,2,2,1,1,0,0},
	{0,1,666,1,1,666,1,0,0},
	{0,1,1,1,1,1,1,0,0},
	},//第三关 7雷 9*9
	{{0,0,0,0,0,1,1,1,0,0,0},
	{0,1,1,1,0,1,666,1,0,0,0},
	{0,1,666,1,1,2,3,2,1,0,0},
	{1,2,2,1,1,666,2,666,1,0,0},
	{1,666,1,0,2,2,3,1,1,1,1},
	{1,1,1,0,1,666,1,0,0,1,666},
	{0,1,1,1,1,1,1,0,0,1,1},
	{0,1,666,2,1,0,0,0,0,0,0},
	{0,1,2,666,1,0,1,1,1,0,0},
	{0,0,1,1,1,0,1,666,1,0,0},
	{0,0,0,0,0,0,1,1,1,0,0},
	},//第四关 10雷 11*11  
	{{0,0,0,0,0,1,1,1,0,0,1,1,1,0,0},
	{1,1,1,0,0,1,666,1,0,0,1,666,1,0,0},
	{1,666,2,2,1,2,1,1,0,0,1,1,1,0,0},
	{1,2,666,2,666,1,0,0,1,1,1,0,0,0,0},
	{0,1,1,2,2,2,1,0,1,666,1,0,1,1,1},
	{0,0,0,0,1,666,1,0,1,1,1,0,1,666,1},
	{0,0,1,1,2,1,2,1,1,0,0,0,1,1,1},
	{0,0,1,666,1,0,2,666,2,0,0,0,0,0,0},
	{0,0,1,1,1,0,2,666,2,0,1,1,1,0,0},
	{0,0,0,0,0,0,1,1,2,2,3,666,1,0,0},
	{0,0,1,1,1,0,0,0,1,666,666,2,1,0,0},
	{0,0,1,666,1,0,0,0,1,2,2,1,0,0,0},
	{0,0,1,1,2,1,1,0,0,0,1,1,1,0,0},
	{0,0,0,0,1,666,1,0,0,0,1,666,1,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0}
	} //第五关  17雷  15*15
	};
	int bians[9] = { 6,7,9,11,15,5,9,13,6 };
	int booms[9] = { 3,5,7,10,17,3,10,17,999 };
	boom = booms[i];
	bian = bians[i];
	step = 0;
	total = bian * bian;
	if (i <= 4 && i >= 0)//闯关模式初始化
	{
		for (int j = 0; j < bians[i]; j++)
		{
			for (int k = 0; k < bians[i]; k++)
				board[j][k] = c_board[i][j][k];
		}
	}
	else if (i >= 5 && i <= 7)
	{
		for (int j = 0; j < bians[i]; j++)
		{
			for (int k = 0; k < bians[i]; k++)
				board[j][k] = 0;
		}
		int count = 0;
		int x, y;
		srand(time(NULL));
		while (count < boom)
		{
			x = rand() % (bian);
			y = rand() % (bian);
			if (board[x][y] < 9)
			{
				board[x][y] = 666;
				board[x + 1][y + 1]++;
				board[x + 1][y]++;
				board[x][y + 1]++;
				if (x > 0)
				{
					board[x - 1][y]++;
					board[x - 1][y + 1]++;
				}
				if (y > 0)
				{
					board[x][y - 1]++;
					board[x + 1][y - 1]++;
				}
				if (x > 0 && y > 0)
				{
					board[x - 1][y - 1]++;
				}
				count++;
			}
		}
		for (int j = 0; j < bians[i]; j++)
		{
			for (int k = 0; k < bians[i]; k++)
			{
				if (board[j][k] > 666)
					board[j][k] = 666;
			}

		}

	}
	else if (i == 8)
	{
		int fun_board[6][6] = { {666,666,666,666,666,666},
			{666,666,666,666,666,666},
			{666,666,666,666,666,666},
			{666,666,666,666,666,666},
			{666,666,666,666,666,666},
			{666,666,666,666,666,666} };
		for (int j = 0; j < bians[i]; j++)
		{
			for (int k = 0; k < bians[i]; k++)
				board[j][k] = fun_board[j][k];

		}
	}
}

int isWin()
{
	int temp = 0;
	for (int i = 0; i < bian; i++)
	{
		for (int j = 0; j < bian; j++)
		{
			if (front_map[i][j] == 0||(front_map[i][j]==10&&board[i][j]==666))
			{
				temp++;//遍历表盘寻找未打开格子的个数
			}
		}
	}
	open = total - temp;

	if (open == total - boom)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int plant_flag(int x, int y)
{
	if (front_map[x][y] == 0)
	{
		front_map[x][y] = 10;
		return 0;
	}
	else if (front_map[x][y] == 10)
	{
		front_map[x][y] = 0;
		return 0;
	}
	else
		return 1;

}

void game_prop()
{
	for (int i = 0; i < bian; i++)
	{
		for (int j = 0; j < bian; j++)
		{
			if (board[i][j] >= 666 && front_map[i][j] != 10)
			{
				front_map[i][j] = 10;
				return 0;
			}
		}
	}
}

void view_game()
{

	int x = 1, y = 1;
	char ch;
	int time = 0;
	while (1) {
	m:    system("cls");
		if (turn > 0 && turn <= 5)
		{
			printf(COLOR_RED"扫雷"COLOR_RESET);
			printf(COLOR_BLUE" 闯关模式"COLOR_RESET);
			printf(COLOR_YELLOW" 第%d关\n"COLOR_RESET,turn);
		}
		if (turn >= 6 && turn <= 8) {
			if (turn == 6) 
			{ 
				printf(COLOR_RED"扫雷"COLOR_RESET);
				printf(COLOR_BLUE" 随机模式"COLOR_RESET);
				printf(COLOR_GREEN" 简单\n"COLOR_RESET);
			}

			else if (turn == 7)
			{
				printf(COLOR_RED"扫雷"COLOR_RESET);
				printf(COLOR_BLUE" 随机模式"COLOR_RESET);
				printf(COLOR_CYAN" 普通\n"COLOR_RESET);
			}
			else if (turn == 8) 
			{
				printf(COLOR_RED"扫雷"COLOR_RESET);
				printf(COLOR_BLUE" 随机模式"COLOR_RESET);
				printf(COLOR_RED" 困难\n"COLOR_RESET);
			}
		}
		if (turn == 9)
		{
			printf(COLOR_RED"扫雷"COLOR_RESET);
			printf(COLOR_BLUE" 趣味模式\n"COLOR_RESET);
		}
		printf(COLOR_ORANGE"---累计步数：%d步---\n"COLOR_RESET, step);
		for (int i = 0; i < bian; i++) {
			for (int j = 0; j < bian; j++) {
				gotoXY(j * 2 + 2, 3 + i);
				if (front_map[i][j] == 0)printf("*");
				else if (front_map[i][j] == 9)printf(" ");
				else if (front_map[i][j] == 10)printf(COLOR_RED"Q"COLOR_RESET);
				else
				{
					if (front_map[i][j]==1)printf(COLOR_BLUE"%d"COLOR_RESET, front_map[i][j]);
					else if (front_map[i][j] == 2)printf(COLOR_GREEN"%d"COLOR_RESET, front_map[i][j]);
					else if (front_map[i][j] == 3)printf(COLOR_RED"%d"COLOR_RESET, front_map[i][j]);
					else if (front_map[i][j] > 3 && front_map[i][j] < 9)printf(COLOR_CYAN"%d"COLOR_RESET, front_map[i][j]);
				}
			}
			printf("\n");
		}
		printf("本关共有%d颗雷\n", boom);
		printf(COLOR_PURPLE"键位提示：\n"COLOR_RESET);
		printf(COLOR_RED"WASD--移动光标\n"COLOR_RESET);
		printf(COLOR_YELLOW"回车--打开格子\n"COLOR_RESET);
		printf(COLOR_GREEN"ESC--游戏暂停界面\n"COLOR_RESET);
		printf(COLOR_CYAN"I--插旗和取消插旗\n"COLOR_RESET);
		printf(COLOR_BLUE"G--游戏道具:展示附近未插旗的一个雷\n"COLOR_RESET);
		printf(COLOR_PURPLE"注:棋盘内 !或X表示地雷 Q表示插旗 "COLOR_RESET);
		printf(COLOR_PURPLE"数字表示周围八格内地雷的数量\n"COLOR_RESET);
		printf(COLOR_ORANGE"游戏规则：打开所有非雷格即为胜利，踩雷即为失败\n"COLOR_RESET);
		gotoXY(2 * x, y + 2);
		if (front_map[y-1][x-1] == 0)printf("\033[4;30;47m*\033[0m");
		else if (front_map[y-1][x-1] == 9)printf("\033[4;30;47m \033[0m");
		else if (front_map[y - 1][x - 1] == 10)printf("\033[4;30;47mQ\033[0m");
		else printf("\033[4;30;47m%d\033[0m", front_map[y-1][x-1]);
		char input = _getch();
		switch (input) {
		case 'w':
		case 'W':
			y--;
			if (y < 1)y = bian;
			//goto m;
			break;
		case 'a':
		case 'A':
			x--;
			if (x < 1)x = bian;
			//goto m;
			break;
		case 's':
		case 'S':
			y++;
			if (y > bian)y = 1;
			//goto m;
			break;
		case 'd':
		case 'D':
			x++;
			if (x > bian)x = 1;
			//goto m;
			break;
		case 0x1B:
			system("cls");
			view_timeout();
			goto m;
		case 'i':
		case 'I':
			plant_flag(y - 1, x - 1);
			break;
		case 'g':
		case 'G':
			game_prop();
			break;
		case'\r':
			Setting(10);
			step++;
			if (explorer(x, y) == 1) {
				Setting(7);
				system("cls");
				printf("------------------------------\n");
				for (int i = 0; i < bian; i++) {
					for (int j = 0; j < bian; j++) {
						gotoXY(j * 2 + 2, 3 + i);
						if (board[i][j] == 0)printf(" ");
						else if (board[i][j] == 666)printf(COLOR_RED"X"COLOR_RESET);
						else printf("%d", board[i][j]);
					}
					printf("\n");
				}
				printf("------------------------------\n");
				gotoXY((x-1)*2+2,2+y);
				setPrintColor(0x6f);
				printf(COLOR_RED"!"COLOR_RESET);
				setPrintColor(0x0f);
				Sleep(1800);
				view_Final(0, step);
			}
			if (explorer(x, y) == 0) 
			{
				if (isWin() == 0) 
				{
					system("cls");
					if (turn > 0 && turn <= 5)
					{
						printf(COLOR_RED"扫雷"COLOR_RESET);
						printf(COLOR_BLUE" 闯关模式"COLOR_RESET);
						printf(COLOR_YELLOW" 第%d关\n"COLOR_RESET, turn);
					}
					if (turn >= 6 && turn <= 8) {
						if (turn == 6)
						{
							printf(COLOR_RED"扫雷"COLOR_RESET);
							printf(COLOR_BLUE" 随机模式"COLOR_RESET);
							printf(COLOR_GREEN" 简单\n"COLOR_RESET);
						}

						else if (turn == 7)
						{
							printf(COLOR_RED"扫雷"COLOR_RESET);
							printf(COLOR_BLUE" 随机模式"COLOR_RESET);
							printf(COLOR_CYAN" 普通\n"COLOR_RESET);
						}
						else if (turn == 8)
						{
							printf(COLOR_RED"扫雷"COLOR_RESET);
							printf(COLOR_BLUE" 随机模式"COLOR_RESET);
							printf(COLOR_MAGENTA" 困难\n"COLOR_RESET);
						}
					}
					if (turn == 9)
					{
						printf(COLOR_RED"扫雷"COLOR_RESET);
						printf(COLOR_BLUE" 趣味模式\n"COLOR_RESET);
					}
					printf(COLOR_ORANGE"---累计步数：%d步---\n"COLOR_RESET, step);
					for (int i = 0; i < bian; i++) {
						for (int j = 0; j < bian; j++) {
							gotoXY(j * 2 + 2, 3 + i);
							if (front_map[i][j] == 0)printf("*");
							else if (front_map[i][j] == 9)printf(" ");
							else if (front_map[i][j] == 10)printf(COLOR_RED"Q"COLOR_RESET);
							else
							{
								if (front_map[i][j] == 1)printf(COLOR_BLUE"%d"COLOR_RESET, front_map[i][j]);
								else if (front_map[i][j] == 2)printf(COLOR_GREEN"%d"COLOR_RESET, front_map[i][j]);
								else if (front_map[i][j] == 3)printf(COLOR_RED"%d"COLOR_RESET, front_map[i][j]);
								else if (front_map[i][j] > 3 && front_map[i][j] < 9)printf(COLOR_CYAN"%d"COLOR_RESET, front_map[i][j]);
							}
						}
						printf("\n");
					}
					printf("本关共有%d颗雷\n", boom);
					printf(COLOR_PURPLE"键位提示：\n"COLOR_RESET);
					printf(COLOR_RED"WASD--移动光标\n"COLOR_RESET);
					printf(COLOR_YELLOW"回车--打开格子\n"COLOR_RESET);
					printf(COLOR_GREEN"ESC--游戏暂停界面\n"COLOR_RESET);
					printf(COLOR_CYAN"I--插旗和取消插旗\n"COLOR_RESET);
					printf(COLOR_BLUE"G--游戏道具:展示附近未插旗的一个雷\n"COLOR_RESET);
					printf(COLOR_PURPLE"注:棋盘内 !表示地雷 Q表示插旗 "COLOR_RESET);
					printf(COLOR_PURPLE"数字表示周围八格内地雷的数量\n"COLOR_RESET);
					printf(COLOR_ORANGE"游戏规则：打开所有非雷格即为胜利，踩雷即为失败\n"COLOR_RESET);
					Sleep(600);
					Setting(8);
					view_Final(1, step);
				}
				system("cls");
				//goto m;
				break;
			}
		}
		//}
	}
}


void view_Final(int i, int sum)
{
	system("cls");
	gotoXY(8, 4);
	printf("=========================================================");
	gotoXY(8, 26);
	printf("=========================================================");
	for (int j = 5; j < 27; j++)
	{
		gotoXY(8, j);
		printf("||");
		gotoXY(63, j);
		printf("||");

	}

	int userChoose = 0;
	while (1)
	{

		if (i == 1)
		{
			gotoXY(15, 6);
			printf("   您已经找到所有地雷，游戏胜利，恭喜您！");
			gotoXY(24, 9);
			printf("(ﾉ>ω<)ﾉ");
			gotoXY(24, 11);
			printf("累计步数:%d", sum);
			gotoXY(24, 14);
			printf("您可以选择：");
			if (userChoose == 0)setPrintColor(0x6f);
			gotoXY(24, 17);
			printf("1.返回游戏菜单\n");
			if (userChoose == 0) setPrintColor(0x0f);

			if (userChoose == 1) setPrintColor(0x6f);
			gotoXY(24, 20);
			printf("2.再玩一把\n");
			if (userChoose == 1)setPrintColor(0x0f);

			if (userChoose == 2)setPrintColor(0x6f);
			gotoXY(24, 23);
			printf("3.退出\n");
			if (userChoose == 2)setPrintColor(0x0f);
		}
		else
		{
			gotoXY(15, 6);
			printf("   很遗憾，您踩到了地雷，游戏失败");
			gotoXY(24, 9);
			printf("(´;ω;`)");
			gotoXY(24, 11);
			printf("累计步数:%d", sum);
			gotoXY(24, 14);
			printf("您可以选择：");
			if (userChoose == 0)setPrintColor(0x6f);
			gotoXY(24, 17);
			printf("1.返回游戏菜单\n");
			if (userChoose == 0) setPrintColor(0x0f);

			if (userChoose == 1) setPrintColor(0x6f);
			gotoXY(24, 20);
			printf("2.再玩一把\n");
			if (userChoose == 1)setPrintColor(0x0f);
			if (userChoose == 2)setPrintColor(0x6f);
			gotoXY(24, 23);
			printf("3.退出\n");
			if (userChoose == 2)setPrintColor(0x0f);
		}
		char input = _getch();
		switch (input)
		{
		case 'w':
		case 'W':
			userChoose -= 1;
			if (userChoose == -1) userChoose = 2;
			break;
		case 's':
		case 'S':
			userChoose += 1;
			if (userChoose == 3)userChoose = 0;
			break;
		case'\r':
			switch (userChoose)
			{
			case 0:
				view_menu();
				break;
			case 1:
				soybean();
				break;
			case 2:
				system("cls");
				printf("欢迎下次光临");
				exit(0);
			}
			break;
		}
	}

}



int explorer(int x, int y) {
	flag = 0;
	c = 0;
	x--;
	y--;
	if (board[y][x] == 666) {
		return 1;
	}
	xcheck[0][0] = x + 1;
	ycheck[0][0] = y + 1;
	xcheck[0][1] = 100;
	ycheck[0][1] = 100;
	if (board[y][x] == 0) {
		for (int i = 0; i < bian; i++) {
			for (int j = 0; j < bian; j++) {
				sarr[i][j] = board[i][j];
			}
		}
		while (1) {
			int m = ghost();
			if (m == 0) {
				break;
			}
			flag++;
		}
		return 0;
	}
	else {
		front_map[y][x] = board[y][x];
		return 0;
	}
}

int ghost() {
	//修改x,ycheck的棋盘值为9
	while (1) {
		if (xcheck[flag % 2][c] == 100) {
			break;
		}
		sarr[ycheck[flag % 2][c] - 1][xcheck[flag % 2][c] - 1] = 9;
		front_map[ycheck[flag % 2][c] - 1][xcheck[flag % 2][c] - 1] = 9;
		c++;
	}
	c--;
	//检索周围的空位置并记录
	//front_map[ycheck[flag % 2][c] + arrcheck[i][1] - 1][xcheck[flag % 2][c] + arrcheck[i][0] - 1] = sarr[ycheck[flag % 2][c] + arrcheck[i][1] - 1][xcheck[flag % 2][c] + arrcheck[i][0] - 1];
	while (c >= 0) {
		for (int j = 0; j < 8; j++) {
			if (xcheck[flag % 2][c] + arrcheck[j][0] > bian || xcheck[flag % 2][c] + arrcheck[j][0] < 1 || ycheck[flag % 2][c] + arrcheck[j][1]>bian || ycheck[flag % 2][c] + arrcheck[j][1] < 1) {
				continue;
			}
			if (sarr[ycheck[flag % 2][c] + arrcheck[j][1] - 1][xcheck[flag % 2][c] + arrcheck[j][0] - 1] != 0) {
				front_map[ycheck[flag % 2][c] + arrcheck[j][1] - 1][xcheck[flag % 2][c] + arrcheck[j][0] - 1] = sarr[ycheck[flag % 2][c] + arrcheck[j][1] - 1][xcheck[flag % 2][c] + arrcheck[j][0] - 1];
			}
		}
		for (int i = 0; i < 4; i++) {
			if (xcheck[flag % 2][c] + arrcheck[i][0] > bian || xcheck[flag % 2][c] + arrcheck[i][0] < 1 || ycheck[flag % 2][c] + arrcheck[i][1]>bian || ycheck[flag % 2][c] + arrcheck[i][1] < 1) {
				continue;
			}
			if (sarr[ycheck[flag % 2][c] + arrcheck[i][1] - 1][xcheck[flag % 2][c] + arrcheck[i][0] - 1] == 0) {
				if (flag % 2 == 0) {
					ycheck[flag % 2 + 1][q] = ycheck[flag % 2][c] + arrcheck[i][1];
					xcheck[flag % 2 + 1][q] = xcheck[flag % 2][c] + arrcheck[i][0];
				}
				else {
					ycheck[flag % 2 - 1][q] = ycheck[flag % 2][c] + arrcheck[i][1];
					xcheck[flag % 2 - 1][q] = xcheck[flag % 2][c] + arrcheck[i][0];
				}
				q++;
			}
		}
		c--;
	}
	c++;
	if (flag % 2 == 0) {
		xcheck[flag % 2 + 1][q] = 100;
	}
	else {
		xcheck[flag % 2 - 1][q] = 100;
	}
	if (q == 0) {
		q = 0;
		return 0;
	}
	else {
		q = 0;
		return 1;
	}
}

void view_timeout() {
	int h = 0;
	gotoXY(1, 0);
	for (int i = h; i < h + 30; i++) {
		printf("=");
	}
	for (int i = 1; i < 13; i++) {
		gotoXY(1, 1 + i);
		printf("||");
		gotoXY(29, 1 + i);
		printf("||");
	}
	gotoXY(1, 14);
	for (int i = h; i < h + 30; i++) {
		printf("=");
	}
	int userChoose = 0;
	while (1) {
		// ----------------- 打印界面 -----------------

		if (userChoose == 0) setPrintColor(0x6f);
		gotoXY(12, 3);
		printf("继续游戏");
		if (userChoose == 0) setPrintColor(0x0f);

		if (userChoose == 1) setPrintColor(0x6f);
		gotoXY(12, 6);
		printf("设置界面");
		if (userChoose == 1) setPrintColor(0x0f);

		if (userChoose == 2) setPrintColor(0x6f);
		gotoXY(12, 9);
		printf("游戏菜单");
		if (userChoose == 2) setPrintColor(0x0f);

		if (userChoose == 3) setPrintColor(0x6f);
		gotoXY(10, 12);
		printf("重新开始游戏");
		if (userChoose == 3) setPrintColor(0x0f);

		// ---------------- 接收用户输入 --------------
		char input = _getch();
		// -------------判断是方向上下还是回车------------
		switch (input) {
		case 'w':
		case 'W':
			userChoose -= 1;
			if (userChoose == -1) userChoose = 3;
			break;
		case 's':
		case 'S':
			userChoose = (userChoose + 1) % 4;
			break;
		case '\r':
			switch (userChoose) {
			case 0:
				if (art = 1)
				{
					art = 0;
					view_game();
				}
				else
				{
					goto p;
				}
				break;
			case 1:
				system("cls");
				view_Setting2(1);
				break;
			case 2:
				system("cls");
				view_menu();
				break;
			case 3:
				system("cls");
				soybean();
				break;
			}
			system("cls");
			break;
		}
	}
	p:Sleep(1);
}
void view_Setting2() {
	system("cls");
	js1 = 2;
	printf("=======================================\n");
	printf("||");
	printf(COLOR_CYAN"             设置界面:             "COLOR_RESET);
	printf("||\n");
	printf("||            1. 选择BGM             ||\n");
	printf("||            2. 关闭BGM             ||\n");
	printf("||            3. 开启音效            ||\n");
	printf("||            4. 关闭音效            ||\n");
	printf("||            5. 调节音量            ||\n");
	printf("||             6. 返回               ||\n");
	printf("||");
	printf(COLOR_PURPLE"	    W/S选择 回车确定         "COLOR_RESET);
	printf("||\n");
	printf("=======================================\n");
	setting_guang();
	gotoXY(15, js1 + 1);
	while (1) {
		char confirmsetting = 'm';
		confirmsetting = _getch();
		switch (confirmsetting) {
		case 'w':
		case 'W':
			if (js1 <= 2) {
				js1++;
			}
			js1--;
			setting_guang();
			break;
		case 's':
		case 'S':
			if (js1 >= 7) {
				js1--;
			}
			js1++;
			setting_guang();
			break;
		case '\r':
			switch (js1) {
			case 2:
				goto bgm; // 切换BGM
				break;
			case 3:
				Setting(-1); // 关闭BGM
				view_Setting2();
				break;
			case 4:
				Setting(1); // 开启音效
				view_Setting2();
				break;
			case 5:
				Setting(-2); // 关闭音效
				view_Setting2();
				break;
			case 6:
				Setting(3); // 调节音量
				view_Setting2();
				break;
			case 7:
				system("cls");
				art = 1;
				view_timeout(); // 返回暂停界面
				break;
			default:
				printf("输入错误，请重试。\n");
				Sleep(1000); // 暂停
				break;
			}
		}
	}
bgm:    system("cls");
	wchar_t cmd[128];
	int j, ret;
	printf("=====================================\n");
	printf("||");
	printf(COLOR_CYAN"            歌单如下             "COLOR_RESET);
	printf("||\n");
	printf("||           1. 又活了一天         ||\n");
	printf("||           2. 出山               ||\n");
	printf("||           3. 辞·九门回忆        ||\n");
	printf("||           4. こんにちは太陽     ||\n");
	printf("||           5. 光辉岁月           ||\n");
	printf("||           6. 跳伞               ||\n");
	printf("||           7. 神秘彩蛋           ||\n");
	printf("||           8. See you again      ||\n");
	printf("||           9. 坤坤进行曲         ||\n");
	printf("||           10. The des Alize     ||\n");
	printf("||           11. 返回              ||\n");
	printf("||           请选择BGM:            ||\n");
	printf("||");
	printf(COLOR_PURPLE"	   W/S选择 回车确定        "COLOR_RESET);
	printf("||\n");
	printf("=====================================\n");
	for (j = 1; j <= 10; j++) {
		swprintf(cmd, 128, L"close bgm%d", j);
		mciSendString(cmd, NULL, 0, NULL);
	}
	setting_bgmbiao();
	gotoXY(14, js1 + 1);
	while (1) {
		char confirmchuang = 'm';
		confirmchuang = _getch();
		switch (confirmchuang) {
		case 'w':
		case 'W':
			if (js1 <= 2) {
				js1++;
			}
			js1--;
			setting_bgmbiao();
			break;
		case 's':
		case 'S':
			if (js1 >= 12) {
				js1--;
			}
			js1++;
			setting_bgmbiao();
			break;
		case '\r':
			switch (js1) {
			case 2:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
					ret = mciSendString(L"open \"bgm1.mp3\" alias bgm1", NULL, 0, NULL);
					if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
					mciSendString(L"play bgm1 repeat", NULL, 0, NULL);
					
					break;
			case 3:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm2.mp3\" alias bgm2", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm2 repeat", NULL, 0, NULL);
				break;
			case 4:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm3.mp3\" alias bgm3", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm3 repeat", NULL, 0, NULL);
				break;
			case 5:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm4.mp3\" alias bgm4", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm4 repeat", NULL, 0, NULL);
				break;
			case 6:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm5.mp3\" alias bgm5", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm5 repeat", NULL, 0, NULL);
				break;
			case 7:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm6.mp3\" alias bgm6", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm6 repeat", NULL, 0, NULL);
				break;
			case 8:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm7.mp3\" alias bgm7", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm7 repeat", NULL, 0, NULL);
				break;
				//加的：
			case 9:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm8.mp3\" alias bgm8", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm8 repeat", NULL, 0, NULL);
				break;
			case 10:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm9.mp3\" alias bgm9", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm9 repeat", NULL, 0, NULL);
				break;
			case 11:
				for (j = 1; j <= 10; j++) {
					swprintf(cmd, 128, L"close bgm%d", j);
					mciSendString(cmd, NULL, 0, NULL);
				}
				ret = mciSendString(L"open \"bgm10.mp3\" alias bgm10", NULL, 0, NULL);
				if (ret != 0) printf("打开BGM失败，错误码：%d\n", ret);
				mciSendString(L"play bgm10 repeat", NULL, 0, NULL);
				break;
			case 12:
				view_Setting2();
				break;
			default:
				printf("输入错误，请重试。\n");
				Sleep(1000);
				}
				break;
			}
		}
	}
}
