#pragma comment(lib, "winmm.lib")
#include"../slbhr.h"
#include<stdio.h>
#include <windows.h>
#include <mmsystem.h>

int VolumeChange(int n) {
    //获取当前音量
    int volumepercent;
    DWORD volume = 0;
    MMRESULT result1 = waveOutGetVolume(0, &volume);
    if (result1 == MMSYSERR_NOERROR) {
        WORD leftVolume = LOWORD(volume);
        volumepercent = (leftVolume * 100) / 65535;
    }
    //根据按钮序号调整音量
    switch (n) {
    case 1://最大音量
        volumepercent = 100;
        break;
    case 2://中等音量
        volumepercent = 50;
        break;
    case 3://低音
        volumepercent = 20;
        break;
    case 4://静音
        volumepercent = 0;
        break;
    }

    //确保音量在0-100范围内
    if (volumepercent < 0) volumepercent = 0;
    if (volumepercent > 100) volumepercent = 100;
    //转换为0-65535范围
    volume = (volumepercent * 65535) / 100;
    //设置相同的左右声道音量
    DWORD leftRightVolume = (volume << 16) | volume;
    //设置音量
    MMRESULT result2 = waveOutSetVolume(0, leftRightVolume);
    //检查结果
    if (result2 == MMSYSERR_NOERROR) {
        printf(" 音量设置为: %d%%\n", volumepercent);
        return TRUE;
    }
    else {
        printf(" 设置音量失败: %d\n", result2);
        return FALSE;
    }

    return volumepercent;

}
//优先级：非核心
//设计人：白的黑
//开发者：
/*  功能描述:改变音量
    逻辑描述：
    音量初始值默认为200
    n：按钮序号（通过鼠标点击函数获取）
    1:调大音量 2:调小音量 3:最大音量 4:静音 5.自定义音量
    swtich(n)
    调用mcisendstring（）进行相应调节//音量为0—1000
    返回值：调节后音量
*/