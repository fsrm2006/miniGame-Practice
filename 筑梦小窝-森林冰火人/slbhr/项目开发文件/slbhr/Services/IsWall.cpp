#include "../slbhr.h"
#include<stdio.h>
// AABB碰撞检测函数
bool IsAABBCollide(int l1, int t1, int r1, int b1, int l2, int t2, int r2, int b2) {
    return !(r1 <= l2 || l1 >= r2 || b1 <= t2 || t1 >= b2);
}

void IsWall(int player)
//player 表示哪个玩家1表示玩家1,2表示玩家2
{
    //优先级：核心；
    //设计人：浮生若梦
    //负责人：浮生若梦
    //函数描述：此函数用于检测人物是否碰壁或者触地，若体积碰撞则限制人物坐标，并且在触地时改变ItemType;
    //逻辑说明：分别遍历对应关卡的SolidWall[3][100][5]和NowSlatePos[10][4], 矩形数量在WallNum[3]和PanelNum[3]；
    //人物体积框的上下左右边框都需要判断是否触地
    //如果人物体积判定框（左上右下的两个点）在任何一个矩形内部则将人物的坐标固定在矩形边缘，
    //并且如果人物下边缘触地（y轴==，x轴在长度范围内），就将人物的ItemType改为对应方块的类型（如果是石砖的话也当成地面值为0）
    //如果人物下方没有任何的体积碰撞或者接触，就把ItemType改为-1表示空中；
    //如有疑问欢迎询问
    //返回值：无
    struct player* p;
    if (player == 1)
        p = &player1;
    else
        p = &player2;
    p->xm = (p->xl + p->xr) / 2;

    // 地图边界
    const int mapLeft = 0, mapTop = 0, mapRight = 1024, mapBottom = 768;

    // 边界越界处理
    if (p->xl < mapLeft) {
        p->xr += (mapLeft - p->xl);
        p->xl = mapLeft;
    }
    if (p->xr > mapRight) {
        p->xl -= (p->xr - mapRight);
        p->xr = mapRight;
    }
    if (p->yl < mapTop) {
        p->yr += (mapTop - p->yl);
        p->yl = mapTop;
    }
    if (p->yr > mapBottom) {
        p->yl -= (p->yr - mapBottom);
        p->yr = mapBottom;
    }

    // 1. 先做碰撞修正（不负责ItemType赋值）
    for (int i = 0; i < WallNum[NowLevel]; i++) {
        int* wall = SolidWall[NowLevel][i];
        if (wall[4] == 0 || wall[4] == 4 || wall[4] == 5) {
            if (IsAABBCollide(p->xl, p->yl, p->xr, p->yr, wall[0], wall[1], wall[2], wall[3])) {
                // 人物下方碰撞
                if (p->yr > wall[1] && p->yl < wall[1] && p->xm >= wall[0] && p->xm <= wall[2]) {
                    int h = p->yr - p->yl;
                    p->yl = wall[1] - h;
                    p->yr = wall[1];
                }
                // 人物上方碰撞
                if (p->yl < wall[3] && p->yr > wall[3] && p->xm >= wall[0] && p->xm <= wall[2]) {
                    int h = p->yr - p->yl;
                    p->yl = wall[3];
                    p->yr = wall[3] + h;
                    p->jumptimes = 0;
                }
                // 人物左侧碰撞
                if (p->xl < wall[2] && p->xr > wall[2]) {
                    int w = p->xr - p->xl;
                    p->xl = wall[2];
                    p->xr = wall[2] + w;
                }
                // 人物右侧碰撞
                if (p->xr > wall[0] && p->xl < wall[0]) {
                    int w = p->xr - p->xl;
                    p->xl = wall[0] - w;
                    p->xr = wall[0];
                }
            }
        }
    }
    for (int i = 0; i < SlateNum[NowLevel]; i++) {
        int* slate = NowSlatePos[i];
        if (IsAABBCollide(p->xl, p->yl, p->xr, p->yr, slate[0], slate[1], slate[2], slate[3])) {
            // 下方碰撞
            if (p->yr > slate[1] && p->yl < slate[1] && p->xm >= slate[0] && p->xm <= slate[2]) {
                int h = p->yr - p->yl;
                p->yl = slate[1] - h;
                p->yr = slate[1];
            }
            // 上方碰撞
            if (p->yl < slate[3] && p->yr > slate[3] && p->xm >= slate[0] && p->xm <= slate[2]) {
                int h = p->yr - p->yl;
                p->yl = slate[3];
                p->yr = slate[3] + h;
                p->jumptimes = 0;
            }
            // 左侧碰撞
            if (p->xl < slate[2] && p->xr > slate[2]) {
                int w = p->xr - p->xl;
                p->xl = slate[2];
                p->xr = slate[2] + w;
            }
            // 右侧碰撞
            if (p->xr > slate[0] && p->xl < slate[0]) {
                int w = p->xr - p->xl;
                p->xl = slate[0] - w;
                p->xr = slate[0];
            }
        }
    }

    p->ItemType = -1; // 默认空中

    // 优先判特殊地形
    for (int i = 0; i < WallNum[NowLevel]; i++) {
        int* wall = SolidWall[NowLevel][i];
        if (wall[4] == 1 || wall[4] == 2 || wall[4] == 3) { // 特殊地形
            if (p->yr > wall[1] && p->yr < wall[3] && p->xm > wall[0] && p->xm < wall[2]) {
                p->ItemType = wall[4];
                return;
            }
        }
    }

    // 没踩到特殊地形再判地面
    if (p->ItemType == -1) {
        for (int i = 0; i < WallNum[NowLevel]; i++) {
            int* wall = SolidWall[NowLevel][i];
            if (wall[4] == 0 || wall[4] == 4 || wall[4] == 5) {
                if (p->yr == wall[1] && p->xm >= wall[0] && p->xm <= wall[2]) {
                    p->ItemType = wall[4];
                    break;
                }
            }
        }
    }
    // 没踩到地面再判石板
    if (p->ItemType == -1) {
        for (int i = 0; i < SlateNum[NowLevel]; i++) {
            int* slate = NowSlatePos[i];
            if (p->yr == slate[1] && p->xm > slate[0] && p->xm < slate[2]) {
                p->ItemType = 0; // 石板视为地面
                break;
            }
        }
    }
    for (int i = 0; i < SpikeNum[NowLevel]; i++)
    {
        int* Spike = SpikeVolume[NowLevel][i];
        if (RectTriangleCollide(Spike[0] + 4, Spike[1] - 6, Spike[2], Spike[3], Spike[4], Spike[5], p->xl + 10, p->yl, p->xr - 4, p->yr - 10))
        {
            p->ItemType = 3; //尖刺视为毒液
            break;
        }
    }
    // 边界底部视为地面
    if (p->yr == mapBottom) {
        p->ItemType = 0;
    }
}
