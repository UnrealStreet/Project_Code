#include <cstdio>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <vector>
#include <string>
void set_cursor(bool hide) { // 隐藏/显示 光标
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo); // 获取控制台光标信息
    CursorInfo.bVisible = hide;				   // 隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo); // 设置控制台光标状态
}
void gotoxy(int x, int y) { // 设置光标
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setmode() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE; // 移除快速编辑模式
    // mode &= ~ENABLE_INSERT_MODE;	 // 移除插入模式
    // mode &= ~ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, mode);
}
struct Click {
    int x, y;
    int delay;
    int button_down, button_up;
    std::string msg;
};
int main() {
    setmode();
    std::printf("欢迎使用鼠标连点器！\n\n");
    _ReStart_: // 重新开始的地方
    std::system("mode con cols=40 lines=15");
    set_cursor(true);
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口置顶
    std::puts("请选择模式：");
    std::puts("  1. 点击位置为鼠标指针，鼠标左/右键点击");
    std::puts("  2. 点击位置固定循环，鼠标左/右键点击");
    std::puts("  0. 退出");
    int ch = _getch();
    while(ch < '0' || ch > '2') ch = _getch();
    std::system("cls");
    set_cursor(false);
    if(ch == '1') {
        set_cursor(true);
        std::puts("配置：");
        std::printf("请输入每秒钟的点击次数(1—1000)：");
        int spd;
        std::scanf("%d", &spd);
        std::printf("\n请选择点击的键(0左键，1右键)：");
        ch = _getch();
        while(ch < '0' || ch > '1') ch = _getch();
        int CLICK_BUTTON_DOWN = (ch == '0' ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN);
        int CLICK_BUTTON_UP = (ch == '0' ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP);
        std::system("cls");
        int cont = true, lst_tim = clock();
        set_cursor(false);
        while(true) {
            gotoxy(0, 0);
            std::printf("连点器%s. . . \n\n", cont ? "运行中" : "已暂停");
            std::printf("速度：%d次/秒\n", spd);
            std::printf("  空格键\t%s\n", cont ? "暂停" : "继续");
            std::printf("  Esc键 \t退出\n");
            SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口置顶
            if(_kbhit()) {
                int ch = _getch();
                if(ch == 27) { // Esc
                    break;
                } else if(ch == ' ') { // 空格
                    cont = !cont;
                }
            } else {
                if(cont) {
                    if(clock() - lst_tim >= 1.0 / spd * CLOCKS_PER_SEC) {
                        lst_tim = clock();
                        POINT pt;
                        GetCursorPos(&pt);
                        mouse_event(CLICK_BUTTON_DOWN, 0, 0, 0, 0);
                        mouse_event(CLICK_BUTTON_UP, 0, 0, 0, 0);
                    }
                }
            }
        }
    } else if(ch == '2') {
        std::printf("请输入您要点击的位置个数：");
        int times;
        std::scanf("%d", &times);
        std::vector<Click> ps;
        set_cursor(true);
        for(int i = 1; i <= times; i++) {
            std::system("cls");
            std::printf("将鼠标移动到第%d个位置上后按下空格：", i);
            while(_getch() != ' ') {}
            POINT p;
            GetCursorPos(&p);
            ps.push_back({p.x, p.y, 0, 0, 0, ""});
            std::printf("\n需要按下的键(0左键，1右键)：");
            char ch = _getch();
            while(ch < '0' || ch > '1') ch = _getch();
            ps.back().button_down = (ch == '0' ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN);
            ps.back().button_up = (ch == '0' ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP);
            std::printf("\n在上一次点击后需要等待多少毫秒：");
            int delay;
            std::scanf("%d", &delay);
            ps.back().delay = delay;
            std::printf("\n附加描述（可不填）：");
            char msg[10000];
            gets(msg);
            gets(msg);
            ps.back().msg = msg;
        }
        int cont = true;
        int now = 0;
        int lst_tim = clock();
        std::system("cls");
        set_cursor(false);
        while(true) {
            gotoxy(0, 0);
            std::printf("连点器%s. . . \n\n", cont ? "运行中" : "已暂停");
            std::printf("当前位置描述：%s\n", ps[now].msg.c_str());
            std::printf("需要等待：%d秒\n", ps[now].delay);
            std::printf("点击按键：%s键\n", (ps[now].button_down == MOUSEEVENTF_LEFTDOWN ? "左" : "右"));
            std::printf("  空格键\t%s\n", cont ? "暂停" : "继续");
            std::printf("  Esc键 \t退出\n");
            SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 窗口置顶
            if(_kbhit()) {
                int ch = _getch();
                if(ch == 27) { // Esc
                    break;
                } else if(ch == ' ') { // 空格
                    cont = !cont;
                }
            } else {
                if(cont) {
                    if(clock() - lst_tim > ps[now].delay) {
                        lst_tim = clock();
                        POINT pt;
                        GetCursorPos(&pt);
                        SetCursorPos(ps[now].x, ps[now].y);
                        mouse_event(ps[now].button_down, 0, 0, 0, 0);
                        mouse_event(ps[now].button_up, 0, 0, 0, 0);
                        SetCursorPos(pt.x, pt.y);
                        if(now + 1 == (int)ps.size()) now = 0;
                        else
                            now = now + 1;
                    }
                }
            }
        }
    } else
        return 0;
    std::system("cls");
    std::printf("欢迎回来！\n\n");
    goto _ReStart_;
    return 0;
}