#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <ctime>
#include "../include/config.h"
#include "../core/StateMachine.h"
#include "../systems/TimeSystem.h"
#include "../systems/InputSystem.h"
#include "../systems/RenderSystem.h"
#include "../gameplay/Snake.h"
#include "../gameplay/Food.h"

/**
 * 游戏循环 - 主游戏引擎
 * 
 * 核心职责：
 * - 实现标准三阶段 Game Loop
 * - 管理所有子系统的协调
 * - 驱动游戏逻辑
 * 
 * Loop 结构：
 * 1. processInput()   - 采集用户输入
 * 2. gameUpdate()     - 按固定时间步长更新游戏状态
 * 3. render()         - 渲染画面
 */
class GameLoop
{
private:
    StateMachine stateMachine;
    Snake snake;
    Food food;
    int score;
    bool isFullWidth;
    
    TimeSystem timeSystem;
    InputSystem inputSystem;
    RenderSystem renderSystem;
    bool running;

    void processInput();
    void gameUpdate();
    void render();

public:
    GameLoop();

    /**
     * 启动主游戏循环
     */
    void run();
};

#endif // GAMELOOP_H
