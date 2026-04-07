#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <conio.h>
#include "../include/config.h"

/**
 * 检查两个方向是否相反（180度）
 * 用于防止用户快速按下相反方向导致蛇头撞上蛇身的bug
 */
bool isOppositeDirection(Direction current, Direction input);

/**
 * 输入系统 - 实现最新合法输入覆盖策略
 * 
 * 核心设计：
 * - 一帧内读取所有可用键盘输入
 * - 仅保留最后一个"合法"（非反向）的方向输入
 * - 自动过滤180°反向输入
 * 
 * 职责：
 * - 采集用户输入
 * - 验证输入合法性
 * - 提供输入查询接口
 */
class InputSystem
{
private:
    Direction nextDirection;      // "下一个方向"缓冲
    Direction currentDirection;   // 当前正在执行的方向
    bool toggleFullWidth;         // 宽度切换标志
    bool requestPause;            // 暂停请求
    bool requestExit;             // 退出请求
    bool requestRestart;          // 重新开始请求

public:
    InputSystem();

    /**
     * 核心输入处理函数 - 实现"最新合法输入覆盖策略"
     */
    void processInput(Direction currentDir, bool isPaused);

    Direction getDirection() const { return currentDirection; }
    Direction getNextDirection() const { return nextDirection; }
    bool getToggleFullWidth() const { return toggleFullWidth; }
    bool getPauseRequest() const { return requestPause; }
    bool getExitRequest() const { return requestExit; }
    bool getRestartRequest() const { return requestRestart; }

    void resetNextDirection() { nextDirection = DIR_STOP; }
};

#endif // INPUTSYSTEM_H
