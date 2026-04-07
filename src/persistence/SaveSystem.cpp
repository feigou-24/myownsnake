#include "SaveSystem.h"
#include <fstream>

bool SaveSystem::saveScore(int score)
{
    std::ofstream file(saveFilePath, std::ios::binary);
    if (!file.is_open())
        return false;
    
    file.write((const char*)&score, sizeof(int));
    file.close();
    return true;
}

int SaveSystem::loadHighScore()
{
    std::ifstream file(saveFilePath, std::ios::binary);
    if (!file.is_open())
        return 0;  // 文件不存在，返回0
    
    int score = 0;
    file.read((char*)&score, sizeof(int));
    file.close();
    return score;
}

void SaveSystem::clearSaveData()
{
    std::remove(saveFilePath.c_str());
}
