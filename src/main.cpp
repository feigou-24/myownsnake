// ============================================================
// 贪吃蛇游戏 - 模块化工程版本
// 主入口点
// ============================================================

#include <iostream>
#include <windows.h>
#include "core/GameLoop.h"

using namespace std;

int main()
{
    // 设置控制台为UTF-8
    SetConsoleOutputCP(CP_UTF8);

    try
    {
        GameLoop gameEngine;
        gameEngine.run();
    }
    catch (exception& e)
    {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
