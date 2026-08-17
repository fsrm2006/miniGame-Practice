extern int DoorFlag[2];
int IsWin()
{
	/*	优先级：核心
		设计人：无相欠
		负责人：阏逢
		功能:判断游戏是否胜利
		参考逻辑：两扇门的状态是否为开启状态DoorFlag[0]==1&&DoorFlag[1]==1
		返回值:int 1代表胜利 0代表未胜利
	*/
    if (DoorFlag[0] == 1 && DoorFlag[1] == 1){
        return 1; // 两扇门都开启，返回胜利
    }
    else{
        return 0; // 未胜利
    }
}
