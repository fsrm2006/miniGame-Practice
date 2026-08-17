#include <stdio.h>
#include <easyx.h>
#include "../slbhr.h"
void ViewMenu() {
	/*核心
	* 编写人：望年
	* 负责人：清绪
		输入值：无
		返回值：无
		函数内变量：int VMButtons[5][5];		//用于存储按钮位置坐标
		功能：
		1.展示游戏开始菜单界面(展示内容见原型图);
		2.初始化VMButtons[5][4]数组(已知按钮数量为5)
		Butttons的储存格式：{{按钮左上x坐标,按钮左上y坐标,按钮右下x坐标，按钮右下y坐标,},{xxx},{},……}
		3.调用int MouseClick(VMButtons[5][4],5)函数检测鼠标点击，根据其返回值跳转对应界面
	*/
	IMAGE img1;
	loadimage(&img1, L"resource/Image resource/Menu/menu.jpg", 1024, 768);
	putimage(0, 0, &img1);
	int VMButtons[4][4] = {
	{360, 370, 690, 460},  // 游戏按钮坐标
	{400, 490, 640, 556},  // 设置按钮坐标  
	{400, 580, 640, 650},  // 介绍按钮坐标
	{400, 676, 640, 750}   // 退出按钮坐标
	};
	while (1) {
		switch (MouseClick(VMButtons, 4)) {
		case 0:
			PlaySoundEffect(12);//播放点击音效
			ViewChoiceLevel();
			break;
		case 1:
			PlaySoundEffect(12);//播放点击音效
			ViewSettings(0);
			break;
		case 2:
			PlaySoundEffect(12);//播放点击音效
			ViewIntroduce();
			break;
		case 3:
			PlaySoundEffect(12);//播放点击音效
			exit(0);
			break;

		}
	}
}