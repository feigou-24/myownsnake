#include "GameLoop.h"
#include <windows.h>
#include <iostream>

GameLoop::GameLoop()
    : score(0), isFullWidth(true), timeSystem(1), running(true)
{
    srand((unsigned)time(NULL));
}

void GameLoop::run()
{
    while (running)
    {
        // ============ 阶段1：输入采集 (高频) ============
        processInput();

        // ============ 阶段2：游戏逻辑更新 (固定时间步长) ============
        if (stateMachine.isRunning() && timeSystem.shouldUpdate())
        {
            gameUpdate();
        }

        // ============ 阶段3：渲染输出 ============
        render();

        // 小延迟，避免CPU占用过高
        Sleep(10);
    }
}

void GameLoop::processInput()
{
    GameState state = stateMachine.getCurrentState();

    switch (state)
    {
    case STATE_RUNNING:
        inputSystem.processInput(snake.getDirection(), false);
        
        if (inputSystem.getPauseRequest())
            stateMachine.setState(STATE_PAUSED);
        else if (inputSystem.getExitRequest())
            stateMachine.setState(STATE_EXIT);
        
        // 更新全宽度切换
        if (inputSystem.getToggleFullWidth())
            isFullWidth = !isFullWidth;
        break;

    case STATE_PAUSED:
        inputSystem.processInput(snake.getDirection(), true);
        
        if (inputSystem.getPauseRequest())
            stateMachine.setState(STATE_RUNNING);
        else if (inputSystem.getExitRequest())
            stateMachine.setState(STATE_EXIT);
        break;

    case STATE_GAME_OVER:
        inputSystem.processInput(snake.getDirection(), true);
        
        if (inputSystem.getRestartRequest())
        {
            snake.init();
            food.generate();
            score = 0;
            stateMachine.setState(STATE_RUNNING);
            timeSystem.setDifficultyLevel(1);
        }
        else if (inputSystem.getExitRequest())
            stateMachine.setState(STATE_EXIT);
        break;

    case STATE_MENU:
        inputSystem.processInput(DIR_STOP, false);
        stateMachine.setState(STATE_RUNNING);
        break;

    case STATE_EXIT:
        running = false;
        break;
    }
}

void GameLoop::gameUpdate()
{
    // 移动蛇
    bool isAlive = snake.moveSnake(inputSystem.getDirection());
    
    if (!isAlive)
    {
        stateMachine.setState(STATE_GAME_OVER);
        return;
    }

    // 检查是否吃到食物
    if (snake.getHeadX() == food.getPosX() && snake.getHeadY() == food.getPosY())
    {
        score += 10;
        snake.grow();
        food.generate();

        // 更新难度
        int diffLevel = (score / DIFFICULTY_FACTOR) + 1;
        timeSystem.setDifficultyLevel(diffLevel);
    }
}

void GameLoop::render()
{
    renderSystem.setFullWidth(isFullWidth);
    renderSystem.render(snake, food, score, stateMachine.getCurrentState(), timeSystem);
}
