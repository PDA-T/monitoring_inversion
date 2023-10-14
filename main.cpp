#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

bool isSwapped = false;
std::string filePath = R"(E:\Procet\C++\monitoring_inversion\mouse_config.txt)";

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if (p->vkCode == VK_F9) {
            if (isSwapped) {
                SwapMouseButton(FALSE);  // 已经反转，还原
                std::cout << "Mouse buttons restored." << std::endl;
            } else {
                SwapMouseButton(TRUE);  // 未反转，进行反转
                std::cout << "Mouse buttons swapped." << std::endl;
            }
            isSwapped = !isSwapped;

            // 更新状态并保存到文件
            std::ofstream configFileOut(filePath);
            if (configFileOut.is_open()) {
                configFileOut << isSwapped;
                configFileOut.close();
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 读取上次的状态
    std::ifstream configFile(filePath);
    if (configFile.is_open()) {
        configFile >> isSwapped;
        configFile.close();
    }

    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        // Handle error
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);
    return 0;
}