// [IMPORTANT] Link winmm.lib in order to compile the code!
#include <windows.h>
#include <iostream>
#include <mmsystem.h>
#include <fstream>
#include <direct.h>
#include<limits.h>
#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

wstring getCurrentDir() {
    wchar_t buff[MAX_PATH];
    GetModuleFileNameW(NULL, buff, MAX_PATH);
    wstring::size_type position = wstring(buff).find_last_of(L"\\/");
    return wstring(buff).substr(0, position);
}
void volumeIncrease() {
    DWORD volume = 0;
    DWORD step = 0xFFFF / 100; // step to increase volume by 1%
    DWORD time_interval_ms = 50; // time interval between volume increases in milliseconds
    for (int i = 0; i <= 100; i++) {
        volume += step;
        waveOutSetVolume(NULL, volume);
        std::cout << "Volume: " << (i + 1) << "%" << std::endl;
        Sleep(time_interval_ms);
    }
    DWORD volume1 = 0xFFFF; // 100% volume
    waveOutSetVolume(NULL, volume1);
}



void songBg(){
    wstring file = getCurrentDir() + L"\\bg.jpg";
    const wchar_t* path = file.data();
    int result;
    result = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)path, SPIF_UPDATEINIFILE);
    int i = 0;
    HWND window;
    AllocConsole();

    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, 0);
    while (i < 1) {

        PlaySound(TEXT("sound.wav"), NULL, SND_SYNC);

    }
}

void cursorPanick() {
    int x, y,stepy,stepx;
    x = 0;
    y = 0;
    stepy = 1;
    stepx = 1;
    srand(time(0));
    while (true) {
        int randomX = rand() % 1400;
        int randomY = rand() % 1400;
        while (true) { //randomX >= x && randomY >= y//
            if (x > randomX) {
                stepx = -stepx;
            }
            if (y > randomY) {
                stepy = -stepy;
            }
            if (y == randomY && x == randomX) {
                break;
            }
            if (y == 0 && x == 0) {
                int randomX = rand() % 1400;
                int randomY = rand() % 1400;
            }
            x = x + stepx;
            y = y + stepy;
            SetCursorPos(x, y);
            std::this_thread::sleep_for(std::chrono::microseconds(5));
        }
    }
}

int main(){

    std::thread t1(volumeIncrease);
    std::thread t2(songBg);
    std::thread t3(cursorPanick);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
