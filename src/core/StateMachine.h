#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "../include/config.h"

/**
 * 状态机 - 管理游戏的五态转移
 * 
 * 状态流：MENU → RUNNING ⟷ PAUSED → GAME_OVER → EXIT
 * 
 * 职责：
 * - 维护当前游戏状态
 * - 处理状态转移规则
 * - 提供状态查询接口
 */
class StateMachine
{
private:
    GameState currentState;

public:
    StateMachine() : currentState(STATE_MENU) {}

    GameState getCurrentState() const { return currentState; }
    void setState(GameState newState) { currentState = newState; }

    // 状态判断辅助函数
    bool isRunning() const { return currentState == STATE_RUNNING; }
    bool isPaused() const { return currentState == STATE_PAUSED; }
    bool isGameOver() const { return currentState == STATE_GAME_OVER; }
    bool isExiting() const { return currentState == STATE_EXIT; }
};

#endif // STATEMACHINE_H
