#include<time.h>
#include"../slbhr.h"
void CountTime(int flag)
{

    //优先级：非核心
    //设计人：浮生若梦
    //开发人：阏逢
    //介绍用于游戏内的计时
    //参考逻辑：使用time.h中的time()函数获取当前时间，并与游戏开始时间进行比较，计算出经过的时间更新到全局变量time中
    //注意和游戏暂停状态的配合使用，暂停时不计时
    //返回值:void


    // 如果尚未设置游戏开始时间，使用第一次调用时的时间作为开始时间
    time_t currentTime = time(NULL);
    if (gameStartTime == 0) {
        gameStartTime = currentTime;
        pauseAccumulate = 0;
        isPaused = 0;
        pauseStartTime = 0;
    }

    // flag == 1 表示请求暂停，flag == 0 表示请求继续（与头文件注释一致）
    if (flag == 1) {
        if (!isPaused) {
            isPaused = 1;
            // 记录暂停开始时刻（不要改动 gameStartTime）
            pauseStartTime = currentTime;
        }
    }
    else if (flag == 0) {
        if (isPaused) {
            isPaused = 0;
            // 累加这段暂停的时长
            pauseAccumulate += (currentTime - pauseStartTime);
            pauseStartTime = 0;
        }
    }

    if (!isPaused) {
        // 总时间 = 当前时间 - 游戏开始时间 - 已累计暂停时间
        gametime = (int)(currentTime - gameStartTime - pauseAccumulate);
        if (gametime < 0) gametime = 0; // 防御性处理
    }
}