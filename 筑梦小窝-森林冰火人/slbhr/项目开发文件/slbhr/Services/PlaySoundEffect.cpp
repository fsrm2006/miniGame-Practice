#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <wchar.h>
#pragma comment(lib, "winmm.lib")
#include "../slbhr.h"

// 注意：请在 slbhr.h 声明 `extern int SoundEffectFlag;`
// 并在 globals.cpp 定义 `int SoundEffectFlag = 1;`

void PlaySoundEffect(int n) {
    static const wchar_t* SoundEffect[] = {
        L"冰人进岩浆池.wav",//0 冰人火人进入水池或者池子死亡时调用
        L"火人跳跃.wav",//1
        L"水人跳跃.wav",//2
        L"开关操作.wav",//3
		L"开门音效.wav",//4
        L"胜利音效1.wav",//5
        L"胜利音效2.wav",//6
        L"失败音效.wav",//7
        L"石板移动.wav",//8
        L"进水池的音效.wav",//9
        L"死亡音效.wav",//10
        L"钻石拾取.wav",//11
        L"点击音效.wav"//12
    };
    const int soundCount = sizeof(SoundEffect) / sizeof(SoundEffect[0]);

    // 特殊命令即时处理
    if (n == -1) { SoundEffectFlag = 0; return; }
    if (n == -2) { SoundEffectFlag = 1; return; }
    if (n == -3) { PlaySoundW(NULL, NULL, 0); return; }

    if (!SoundEffectFlag) return;
    if (n < 0 || n >= soundCount) return;

    // 获取 exe 目录
    wchar_t exePath[MAX_PATH] = {0};
    if (GetModuleFileNameW(NULL, exePath, MAX_PATH) == 0) {
        // 无法获取则使用相对路径
        exePath[0] = L'\0';
    } else {
        wchar_t* p = wcsrchr(exePath, L'\\');
        if (p) *p = L'\0';
    }

    // 构造绝对路径（安全拼接）
    wchar_t fullPath[MAX_PATH] = {0};
    if (exePath[0]) {
        _snwprintf_s(fullPath, _countof(fullPath), _TRUNCATE,
                     L"%s\\resource\\audio resource\\Background sound effects\\%s",
                     exePath, SoundEffect[n]);
    } else {
        _snwprintf_s(fullPath, _countof(fullPath), _TRUNCATE,
                     L"resource\\audio resource\\Background sound effects\\%s",
                     SoundEffect[n]);
    }

    // 调试输出：打印要播放的路径
    fwprintf(stderr, L"[PlaySoundEffect] 播放请求: %s\n", fullPath);
    OutputDebugStringW(fullPath);
    OutputDebugStringW(L"\n");

    // 检查文件是否存在，避免无效路径导致问题
    DWORD attr = GetFileAttributesW(fullPath);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        fwprintf(stderr, L"[PlaySoundEffect] 文件不存在: %s\n", fullPath);
        // 退回尝试相对路径（文件名）
        wchar_t rel[MAX_PATH] = {0};
        _snwprintf_s(rel, _countof(rel), _TRUNCATE,
                     L"resource\\audio resource\\Background sound effects\\%s",
                     SoundEffect[n]);
        attr = GetFileAttributesW(rel);
        if (attr == INVALID_FILE_ATTRIBUTES) {
            fwprintf(stderr, L"[PlaySoundEffect] 相对路径也不存在: %s\n", rel);
            return;
        } else {
            // 使用相对路径
            if (!PlaySoundW(rel, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT)) {
                fwprintf(stderr, L"[PlaySoundEffect] PlaySoundW 失败 (rel)\n");
            }
            return;
        }
    }

    // 非阻塞播放（禁止系统默认蜂鸣）
    if (!PlaySoundW(fullPath, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT)) {
        fwprintf(stderr, L"[PlaySoundEffect] PlaySoundW 失败 (abs)\n");
    }
}

/*  设计人：白的黑
       开发人：
       优先级：非核心
       功能描述：打开音效
       逻辑描述：
       n：按钮序号（通过鼠标点击函数获取）
        关闭 -1
       n默认是1（开始为打开状态）；
       char wav：音乐相对路径地址
       swtich（n）
       case 1：
       打开音效
       case 2：
       关闭音效
       返回值：int （2 表示关闭 1表示打开）
   */