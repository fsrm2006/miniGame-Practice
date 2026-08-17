#include"../slbhr.h"
void HorizontalMov() {
	double speed = 3;
    if (keyLeft_player1) { // A键按住：左移
        if (player1.ItemType == 4)
            speed = 5;
        else if (player1.ItemType == 5)
            speed = 2;
        player1.xl -= speed;
        player1.xr -= speed;
        player1.movflag = 1;
        player1.movdire = 1;

    }
    else if (keyRight_player1) { // D键按住：右移
        if (player1.ItemType == 4)
            speed = 5;
        else if (player1.ItemType == 5)
            speed = 2;
        player1.xl += speed;
        player1.xr += speed;
        player1.movflag = 1;
        player1.movdire = 2;
    }
    // 玩家2：根据箭头键状态移动
    if (keyLeft_player2) { // ←键按住：左移
        if (player2.ItemType == 4)
            speed = 2;
        else if (player2.ItemType == 5)
            speed = 5;
        player2.xl -= speed;
        player2.xr -= speed;
        player2.movflag = 1;
        player2.movdire = 1;
    }
    else if (keyRight_player2) { // →键按住：右移
        if (player2.ItemType == 4)
            speed = 2;
        else if (player2.ItemType == 5)
            speed = 5;
        player2.xl += speed;
        player2.xr += speed;
        player2.movflag = 1;
        player2.movdire = 2;
    }
	
	
}
/*	优先级：核心
		设计人：无相欠
		负责人：
		功能：根据键盘传入的消息，’A‘则对应人物1横坐标减小	‘D'则人物1横坐标增加
			  根据键盘传入的消息’←‘则对应人物2横坐标减小	‘→'则人物2横坐标增加
		参考逻辑：
		返回值:void
	*/