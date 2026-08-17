#include "../slbhr.h"
#include <windows.h>
#include <easyx.h>

void EnterDoor() {
    // 人物进门动画：修正批绘制使用、整数帧计算、SRCCOPY、处理消息避免无响应
    static IMAGE enter_door0, enter_door1;
    static bool loaded = false;
    if (!loaded) {
        loadimage(&enter_door0, L"resource\\Image resource\\Door\\enterdoor0.jpg");
        loadimage(&enter_door1, L"resource\\Image resource\\Door\\enterdoor1.jpg");
        loaded = true;
    }

    const int totalFrames = 18;
    if (totalFrames <= 0) return;

    int srcW0 = enter_door0.getwidth();
    int srcH0 = enter_door0.getheight();
    int srcW1 = enter_door1.getwidth();
    int srcH1 = enter_door1.getheight();
    if (srcW0 <= 0 || srcW1 <= 0) return;

    int frameW0 = srcW0 / totalFrames;
    int frameW1 = srcW1 / totalFrames;
    if (frameW0 <= 0 || frameW1 <= 0) return;

    HDC hdcDest = GetImageHDC();
    HDC hdcSrc0 = GetImageHDC(&enter_door0);
    HDC hdcSrc1 = GetImageHDC(&enter_door1);

    // BeginBatchDraw 放在循环外，EndBatchDraw 放在循环外
    BeginBatchDraw();
    for (int i = 0; i < totalFrames; ++i) {
        int sx0 = i * frameW0;
        int sx1 = i * frameW1;


        StretchBlt(hdcDest, 880, 95, 74, 100, hdcSrc0, sx0, 0, frameW0, srcH0, SRCCOPY);
        StretchBlt(hdcDest, 811, 95, 74, 89, hdcSrc1, sx1, 0, frameW1, srcH1, SRCCOPY);


        FlushBatchDraw();

        // 处理系统消息，避免 Sleep 阻塞使窗口无响应
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Sleep(50); // 控制帧率；更好方案是把动画状态交给主循环逐帧推进
    }
    EndBatchDraw();
}