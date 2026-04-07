#ifndef TIMESYSTEM_H
#define TIMESYSTEM_H

#include "../include/config.h"

/**
 * 时间系统 - 基于毫秒时间戳的固定逻辑帧控制
 * 
 * 职责：
 * - 维护精确的游戏逻辑更新间隔
 * - 根据难度等级调整游戏速度
 * - 提供时间查询接口
 */
class TimeSystem
{
private:
    std::chrono::high_resolution_clock::time_point lastUpdateTime;
    int gameTickInterval;  // 毫秒为单位的固定时间步长
    int difficultyLevel;
    
public:
    TimeSystem(int initialLevel = 1);

    /**
     * 检查是否应该执行一次游戏逻辑更新
     * @return true 表示应该调用 update()
     */
    bool shouldUpdate();

    /**
     * 根据难度等级更新游戏速度
     * 难度等级越高，更新间隔越短（游戏越快）
     */
    void setDifficultyLevel(int level);

    int getDifficultyLevel() const { return difficultyLevel; }
    int getTickInterval() const { return gameTickInterval; }
    
    /**
     * 获取当前时间戳（毫秒），用于闪烁等动画效果
     */
    long long getCurrentTimeMs() const;
};

#endif // TIMESYSTEM_H
