#pragma comment(lib, "winmm.lib")
#include"../slbhr.h"
#include<stdio.h>
#include <windows.h>
#include <mmsystem.h>
//初始化音乐路径数组
const char* music[] = {
    "old.mp3",//0 原版音乐
    "mok.mp3",//1 Memories of Kindness
    "See You Again.mp3",//2 See You Again
    "The des Alizes.mp3",//3 The des Alizes
    "ffxdz.mp3",//4 反方向的钟
    "gyfb.mp3",//5 光阴副本
    "Masquerade.mp3",//6 Masquerade
    "jbs.mp3",//7 诀别书
    "sp.mp3",//8 水泡
    "ts.mp3",//9 跳伞
	"nhty.mp3",//10 こんにちは太陽
	"aqxx.mp3",//11 爱情讯息
    
};
void PlayBGM(int i) {
    //检测(关闭)当前播放的音乐
    char cmd[256] = "";
    sprintf(cmd, "close all");
    wchar_t wcmd[256];
    mbstowcs(wcmd, cmd, sizeof(wcmd) / sizeof(wchar_t));
    mciSendString(wcmd, NULL, 0, NULL);
    //初始化音效路径数组
    memset(cmd, 0, sizeof(cmd));   //全部置零
    wmemset(wcmd, 0, 256); //全部置零
    if (i == -1) {
        mciSendString(L"close all", NULL, 0, NULL);

    }
    //拼接命令字符串
    sprintf(cmd, "open \"resource\\audio resource\\Background music\\%s\" alias SFX", music[i]);
    //转换为宽字符
    mbstowcs(wcmd, cmd, sizeof(wcmd) / sizeof(wchar_t));
    //发送mci命令
    MCIERROR error = mciSendString(wcmd, NULL, 0, NULL);
    //错误处理
    if (error != 0) {
        char errorMsg[256];
        mciGetErrorStringA(error, errorMsg, sizeof(errorMsg));
        printf("打开错误%d:%s\n", error, errorMsg);
    }
    //播放音乐
    error = mciSendString(L"play SFX repeat", NULL, 0, NULL);
    //播放错误处理
    if (error != 0) {
        char errorMsg2[256];
        mciGetErrorStringA(error, errorMsg2, sizeof(errorMsg2));
        printf("播放错误%d:%s\n", error, errorMsg2);
    }

}
