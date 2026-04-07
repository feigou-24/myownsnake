#ifndef FOOD_H
#define FOOD_H

#include "../include/config.h"

/**
 * 食物类 - 管理食物的位置和生成
 * 
 * 职责：
 * - 食物位置的初始化和重置
 * - 食物的随机生成
 */
class Food
{
private:
    int posX, posY;
    const int mapWidth = STAGE_WIDTH;
    const int mapHeight = STAGE_HEIGHT;

public:
    Food();

    /**
     * 随机生成食物位置
     */
    void generate();

    int getPosX() const { return posX; }
    int getPosY() const { return posY; }

    void setPos(int x, int y) { posX = x; posY = y; }
};

#endif // FOOD_H
