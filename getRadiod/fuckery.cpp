#include <windows.h>
#include <iostream>
#include "tchar.h"
#include <chrono>
#include <thread>
#include "wtypes.h"
#include <random>
using namespace std;

void GetDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
}


int _tmain(int argc, _TCHAR* argv[])
{
    int x = 50;
    int y = 50;
    int l = 1;
    int stepX = 3;
    int stepY = 3;

    int horizontal = 0;
    int vertical = 0;
    GetDesktopResolution(horizontal, vertical);
    HWND hWnd = GetConsoleWindow();
    cout << "L\n";

    while (l== 1) {
        MoveWindow(hWnd, x, y, 960, 540, TRUE);
        x = x + stepX;
        y= y + stepY;
        this_thread::sleep_for(chrono::milliseconds(10));        
        if (x > 1920 || x < 0) {
            stepX = -stepX;
        }
        if (y > 1080 || y < 0) {
            stepY = -stepY;
        }
    }
    cin.ignore();

    return 0;
}


