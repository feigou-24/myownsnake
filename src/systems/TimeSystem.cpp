#include "TimeSystem.h"

using namespace std;

TimeSystem::TimeSystem(int initialLevel)
    : gameTickInterval(220), difficultyLevel(initialLevel)
{
    lastUpdateTime = chrono::high_resolution_clock::now();
}

bool TimeSystem::shouldUpdate()
{
    auto now = chrono::high_resolution_clock::now();
    int elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastUpdateTime).count();
    
    if (elapsed >= gameTickInterval)
    {
        lastUpdateTime = now;
        return true;
    }
    return false;
}

void TimeSystem::setDifficultyLevel(int level)
{
    difficultyLevel = max(1, min(MAX_DIFFICULTY_LEVEL, level));
    // 公式：220毫秒 - (难度-1)*35毫秒
    // 难度1（220ms）-> 难度5（80ms）
    gameTickInterval = 220 - (difficultyLevel - 1) * 35;
}

long long TimeSystem::getCurrentTimeMs() const
{
    auto now = chrono::high_resolution_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(
        now.time_since_epoch()).count();
    return ms;
}
