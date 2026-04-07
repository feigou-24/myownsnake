#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <string>

/**
 * 存档系统 - 游戏数据持久化
 * 
 * 未来功能（当前为骨架）：
 * - 保存最高分
 * - 保存游戏进度
 * - 保存玩家设置
 */
class SaveSystem
{
private:
    const std::string saveFilePath = "savegame.dat";

public:
    SaveSystem() {}

    /**
     * 保存游戏分数到文件
     */
    bool saveScore(int score);

    /**
     * 加载最高分
     */
    int loadHighScore();

    /**
     * 清除存档
     */
    void clearSaveData();
};

#endif // SAVESYSTEM_H
