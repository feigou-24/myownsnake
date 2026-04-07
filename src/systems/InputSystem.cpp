#include "InputSystem.h"

// ============================================================
// 方向约束函数实现
// ============================================================
bool isOppositeDirection(Direction current, Direction input)
{
    if (current == DIR_STOP) return false;
    return (current == DIR_LEFT && input == DIR_RIGHT) ||
           (current == DIR_RIGHT && input == DIR_LEFT) ||
           (current == DIR_UP && input == DIR_DOWN) ||
           (current == DIR_DOWN && input == DIR_UP);
}

// ============================================================
// InputSystem 实现
// ============================================================
InputSystem::InputSystem() 
    : nextDirection(DIR_STOP), currentDirection(DIR_STOP),
      toggleFullWidth(false), requestPause(false),
      requestExit(false), requestRestart(false) {}

void InputSystem::processInput(Direction currentDir, bool isPaused)
{
    // 重置每帧标志位
    toggleFullWidth = false;
    requestPause = false;
    requestExit = false;
    requestRestart = false;

    // 读取所有可用的键盘输入（可能有多个）
    while (_kbhit())
    {
        int keyCode = _getch();
        
        // 处理方向键（需要特殊处理）
        if (keyCode == 224)  // 方向键前缀
        {
            keyCode = _getch();
            switch (keyCode)
            {
            case 72:  // 上
                if (!isOppositeDirection(currentDir, DIR_UP))
                    nextDirection = DIR_UP;
                break;
            case 80:  // 下
                if (!isOppositeDirection(currentDir, DIR_DOWN))
                    nextDirection = DIR_DOWN;
                break;
            case 75:  // 左
                if (!isOppositeDirection(currentDir, DIR_LEFT))
                    nextDirection = DIR_LEFT;
                break;
            case 77:  // 右
                if (!isOppositeDirection(currentDir, DIR_RIGHT))
                    nextDirection = DIR_RIGHT;
                break;
            }
        }
        else
        {
            // 处理普通键
            switch (keyCode)
            {
            case 'w':
            case 'W':
                if (!isOppositeDirection(currentDir, DIR_UP))
                    nextDirection = DIR_UP;
                break;
            case 's':
            case 'S':
                if (!isOppositeDirection(currentDir, DIR_DOWN))
                    nextDirection = DIR_DOWN;
                break;
            case 'a':
            case 'A':
                if (!isOppositeDirection(currentDir, DIR_LEFT))
                    nextDirection = DIR_LEFT;
                break;
            case 'd':
            case 'D':
                if (!isOppositeDirection(currentDir, DIR_RIGHT))
                    nextDirection = DIR_RIGHT;
                break;
            case ' ':
                requestPause = true;
                break;
            case 'x':
            case 'X':
                requestExit = true;
                break;
            case 13:  // Enter - 宽度切换
                toggleFullWidth = true;
                break;
            case 'y':
            case 'Y':
                requestRestart = true;
                break;
            case 'n':
            case 'N':
                requestExit = true;
                break;
            }
        }
    }

    // 确定最终的方向（如果没有新输入，保持当前方向）
    if (nextDirection != DIR_STOP)
        currentDirection = nextDirection;
}
