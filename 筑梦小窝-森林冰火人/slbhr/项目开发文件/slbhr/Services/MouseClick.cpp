#include <graphics.h>
#include<stdio.h>
//提醒：在输入按钮坐标数据时，一定要保证按钮左上x坐标<按钮右下x坐标;按钮左上y坐标<按钮右下y坐标!!!!!!!
int	MouseClick(int Buttons[][4],int n)
//输入参数：int Buttons[按钮数量][4]，int n（按钮数量)
//Butttons的储存格式：{{按钮左上x坐标,按钮左上y坐标,按钮右下x坐标，按钮右下y坐标},{xxx},{},……}
{
	//优先级：核心
	//设计人：浮生若梦
	//负责人：玲
	//函数描述：此函数用于在鼠标点击时检测鼠标点击位置是否在按钮上，如果鼠标处于按钮上则返回按钮序号，如果没有就返回-1
	//方便各个界面按钮的点击检测，提高开发效率，避免代码重复，
	//使用者只需在检测到鼠标点击时执行此函数就能得到鼠标点击的按钮序号
	//按钮左上点和右下点即可构成矩形，判断鼠标是否在矩形内即可判断是否点击按钮
	//函数逻辑：
	//返回值：int类型，返回当前鼠标所点击的按钮序号，返回-1则说明当前鼠标未处于按钮上
	//如有疑问欢迎询问
// -----------------------------------------------------------------------------------------------
    // 输入校验：按钮数量为0或数组为空，直接返回-1
    if (n <= 0 || Buttons == NULL)
        return -1;
    static bool g_bBtnPressed = false;   // 是否在按钮上按下
    static int g_nPressedBtnIdx = -1;    // 记录按下时命中的按钮序号（-1为未命中）
    MOUSEMSG msg;
    while (MouseHit()){
        msg = GetMouseMsg(); // 读取鼠标消息（MouseHit()已确认有消息所以进入循环）
        switch (msg.uMsg){
            // 1. 鼠标左键按下，记录是否命中按钮
        case WM_LBUTTONDOWN:
			printf("%d %d\n", msg.x, msg.y); //调试用，输出鼠标坐标)
            g_bBtnPressed = false;
            g_nPressedBtnIdx = -1; // 重置之前的状态
            for (int i = 0; i < n; i++)
            {   // 复制按钮坐标
                int x1 = Buttons[i][0];
                int y1 = Buttons[i][1];
                int x2 = Buttons[i][2];
                int y2 = Buttons[i][3];
                // 判断鼠标是否在按钮矩形内
                if (msg.x >= x1 && msg.x <= x2 && msg.y >= y1 && msg.y <= y2)
                {
                    g_bBtnPressed = true;       // 标记在按钮上按下
                    g_nPressedBtnIdx = i;       // 记录命中的按钮序号
                    break; // 找到对应的按钮就退出
                }
            }
            break;      //跳出这次判断，去检测下一次鼠标操作
            // 2. 鼠标左键松开：判断是否为完整点击（按下+松开在同一按钮）
        case WM_LBUTTONUP:
            if (g_bBtnPressed && g_nPressedBtnIdx >= 0 && g_nPressedBtnIdx < n)//检查是否已经在有按钮的地方使用过鼠标左键以及按钮的序号是否正确
            {    // 再次获取该按钮的坐标
                int x1 = Buttons[g_nPressedBtnIdx][0];
                int y1 = Buttons[g_nPressedBtnIdx][1];
                int x2 = Buttons[g_nPressedBtnIdx][2];
                int y2 = Buttons[g_nPressedBtnIdx][3];
                // 校验松开位置是否仍在原按钮上（防止拖动后松开）
                if (msg.x >= x1 && msg.x <= x2 && msg.y >= y1 && msg.y <= y2)
                {   // 完成完整点击，重置状态并返回按钮序号
                    g_bBtnPressed = false;
                    int result = g_nPressedBtnIdx;
                    g_nPressedBtnIdx = -1;
                    return result;
                }
                // 松开位置不在原按钮上，重置状态
                g_bBtnPressed = false;
                g_nPressedBtnIdx = -1;
            }
            break;
            // 其他鼠标消息（移动、右键等），忽略
        default:
            break;
        }
    }
    return -1;
}