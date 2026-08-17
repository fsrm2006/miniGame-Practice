#include"..\slbhr.h"
#include <tchar.h>
#include <conio.h>
#include <stdio.h>
#include <wingdi.h> 

const wchar_t* SETTINGS_BG_PATH = _T("resource\\Image resource\\Setting\\ling.jpg");
const wchar_t* MUSIC_SELECT_BG_PATH = _T("resource\\Image resource\\Setting\\qiansui.jpg");
#define MUSIC_TOTAL 12          // 音乐数量10个
#define MAIN_BUTTON_COUNT 4
int SettingsButtons[MAIN_BUTTON_COUNT][4] = {
    {312, 180, 712, 240},  // 索引0：音效开关
    {312, 280, 712, 340},  // 索引1：音量大小
    {312, 380, 712, 440},  // 索引2：音乐选择
    {312, 480, 712, 540}   // 索引3：返回主菜单
};

// 音乐选择子界面的按钮配置（10个按钮，索引0-9）
int MusicButtons[MUSIC_TOTAL][4];

const wchar_t* SongNames[MUSIC_TOTAL] = {
    _T("原版音乐"),       // 索引0 → 歌曲1
    _T("Memories of Kindness"),         // 索引1 → 歌曲2
    _T("See You Again"),         // 索引2 → 歌曲3
    _T("The des Alizes"),       // 索引3 → 歌曲4
    _T("反方向的钟"),         // 索引4 → 歌曲5
    _T("光阴副本"),     // 索引5 → 歌曲6
    _T("Masquerade"),       // 索引6 → 歌曲7
    _T("诀别书"),       // 索引7 → 歌曲8
    _T("水泡"),     // 索引8 → 歌曲9
    _T("跳伞"),        // 索引9 → 歌曲10
	_T("こんにちは太陽"),             // 索引10 → 空
	_T("爱情讯息")               // 索引11 → 空
};

void InitMusicButtons() {
    int startX = 262, startY = 180;
    int btnWidth = 200, btnHeight = 70;
    int gapX = 300, gapY = 100;
    for (int i = 0; i < MUSIC_TOTAL; i++) {
        int col = i % 2;
        int row = i / 2;
        MusicButtons[i][0] = startX + col * gapX;
        MusicButtons[i][1] = startY + row * gapY;
        MusicButtons[i][2] = startX + col * gapX + btnWidth;
        MusicButtons[i][3] = startY + row * gapY + btnHeight;
    }
}

void DrawBackground(const wchar_t* imgPath) {
    IMAGE bgImg;

    // 加载图片
    loadimage(&bgImg, imgPath);

    // 获取窗口尺寸和图片尺寸
    int winWidth = getwidth();
    int winHeight = getheight();
    int imgWidth = bgImg.getwidth();
    int imgHeight = bgImg.getheight();

    // 构造 BITMAPINFO 结构体
    BITMAPINFO bmpInfo = { 0 };
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = imgWidth;
    bmpInfo.bmiHeader.biHeight = -imgHeight; // 负值表示自上而下
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 32;
    bmpInfo.bmiHeader.biCompression = BI_RGB;

    // 缩放图片至窗口大小（双缓冲兼容，绘制到底层缓冲区）
    StretchDIBits(
        GetImageHDC(),
        0, 0, winWidth, winHeight,
        0, 0, imgWidth, imgHeight,
        GetImageBuffer(&bgImg),
        &bmpInfo,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}

void DrawButton(int x1, int y1, int x2, int y2, const wchar_t* text, int isSelected) {
    setfillcolor(isSelected ? BLUE : WHITE);
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 2);
    fillrectangle(x1, y1, x2, y2);

    // 文字精确居中（优化字号）
    settextcolor(isSelected ? WHITE : BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(24, 0, _T("微软雅黑"));
    int textWidth = textwidth(text);
    int textHeight = textheight(text);
    int x = x1 + (x2 - x1 - textWidth) / 2;
    int y = y1 + (y2 - y1 - textHeight) / 2;
    outtextxy(x, y, text);
}

void MusicSelectWindow() {
    InitMusicButtons();
    setbkcolor(LIGHTGRAY);
    BeginBatchDraw();

    while (1) {
        cleardevice();

        DrawBackground(MUSIC_SELECT_BG_PATH);

        settextstyle(36, 0, _T("微软雅黑"));
        outtextxy(400, 80, _T("选择音乐"));

        // 绘制10个音乐按钮（索引0-9对应音乐1-10，选中项高亮）
        settextstyle(24, 0, _T("微软雅黑"));
        for (int i = 0; i < MUSIC_TOTAL; i++) {
            DrawButton(MusicButtons[i][0], MusicButtons[i][1],
                MusicButtons[i][2], MusicButtons[i][3],
                SongNames[i], (selectedMusic == i + 1));
        }

        FlushBatchDraw();
        int clickBtn = MouseClick(MusicButtons, MUSIC_TOTAL);
        if (clickBtn != -1) {
            selectedMusic=clickBtn + 1; // 更新选中音乐索引
            PlayBGM(clickBtn);
            EndBatchDraw();
            return;
        }
        Sleep(30);
    }
}
// 展示设置界面
void ViewSettings(int flag)
{
    /*
     优先级：非核心
     设计人：白的黑
     功能：展示设置界面：
     1.音效开关{1 打开 2关闭}
     2.音量大小{1.调大音量 2.降低音量 3.最大音量 4.静音}
     3.音乐选择{音乐1 音乐2 音乐3.......}
     4.返回主菜单
     5.皮肤切换
     然后检测鼠标点击，点击后调用MouseClick()函数获取点击按钮序号
     int Buttons[按钮数量][4]
     Butttons的储存格式：{{按钮左上x坐标,按钮左上y坐标,按钮右下x坐标，按钮右下y坐标},{xxx},{},……}
 */
    setbkcolor(LIGHTGRAY);
    BeginBatchDraw();

    while (1) {
        cleardevice();

        DrawBackground(SETTINGS_BG_PATH);

        // 绘制标题
        settextcolor(BLACK);
        settextstyle(40, 0, _T("微软雅黑"));
        outtextxy(420, 80, _T("设置界面"));

        // 绘制主按钮
        settextstyle(24, 0, _T("微软雅黑"));

        // 1. 音效开关
        wchar_t soundText[32];
        swprintf(soundText, 32, _T("音效开关：%s"), soundEnabled == 1 ? _T("打开(1)") : _T("关闭(2)"));
        DrawButton(SettingsButtons[0][0], SettingsButtons[0][1],
            SettingsButtons[0][2], SettingsButtons[0][3], soundText, 0);

        // 2. 音量大小
        wchar_t volumeText[32];
        const wchar_t* volumeStr[] = { _T("最大音量(1)"), _T("中等音量(2)"), _T("最小音量(3)"), _T("静音(4)") };
        swprintf(volumeText, 32, _T("总音量大小：%s"), volumeStr[volumeLevel - 1]);
        DrawButton(SettingsButtons[1][0], SettingsButtons[1][1],
            SettingsButtons[1][2], SettingsButtons[1][3], volumeText, 0);
		wchar_t SongButtonText[32];
        swprintf(SongButtonText, 32, _T("当前音乐：%s"), SongNames[selectedMusic - 1]);
        // 3. 音乐选择
        DrawButton(SettingsButtons[2][0], SettingsButtons[2][1],
            SettingsButtons[2][2], SettingsButtons[2][3], SongButtonText, 0);

        // 4. 返回主菜单
        DrawButton(SettingsButtons[3][0], SettingsButtons[3][1],
            SettingsButtons[3][2], SettingsButtons[3][3], _T("返回"), 0);

        FlushBatchDraw();
        // 检测按钮点击（返回索引0-3，-1=未点击）
        int clickBtn = MouseClick(SettingsButtons, MAIN_BUTTON_COUNT);
        switch (clickBtn) {
        case 0: // 音效开关（索引0）
            PlaySoundEffect(12);//播放点击音效
            soundEnabled = (soundEnabled == 1) ? 2 : 1;
            if (soundEnabled == 2) {
                PlaySoundEffect(-1); // 关闭音效
            }
            else {
                PlaySoundEffect(-2); // 打开音效
			}
            break;
        case 1:// 音量大小（索引1）
            PlaySoundEffect(12);//播放点击音效
            volumeLevel = (volumeLevel % 4) + 1;
			VolumeChange(volumeLevel);
            break;
        case 2: // 音乐选择（索引2）
            PlaySoundEffect(12);//播放点击音效
            EndBatchDraw();
            MusicSelectWindow();
            setbkcolor(LIGHTGRAY);
            BeginBatchDraw();
            break;
        case 3:// 返回主菜单（索引3）
            PlaySoundEffect(12);//播放点击音效
            EndBatchDraw();
            EndBatchDraw();
            if (flag)
            {
                ViewStop();
            }
            else
            {
                ViewMenu();
            }
        default:
            break;
        }
        Sleep(30);
    }
}