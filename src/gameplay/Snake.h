#ifndef SNAKE_H
#define SNAKE_H

#include "../include/config.h"
#include <cstdlib>
#include <ctime>

/**
 * 蛇类 - 管理蛇的状态和行为
 * 
 * 职责：
 * - 蛇的位置和方向
 * - 蛇身体的移动和碰撞检测
 * - 分数和得分逻辑
 */
class Snake
{
private:
    // 蛇的状态
    int headX, headY;
    int tailX[MAX_SNAKE_LENGTH], tailY[MAX_SNAKE_LENGTH];
    int snakeLength;
    Direction currentDirection;

    // 游戏参数
    const int mapWidth = STAGE_WIDTH;
    const int mapHeight = STAGE_HEIGHT;

public:
    Snake();

    void init();
    
    /**
     * 移动蛇，检测碰撞
     * @return false 表示与自己碰撞（游戏结束）
     */
    bool moveSnake(Direction newDir);

    /**
     * 增长蛇身
     */
    void grow();

    // 获取器
    int getHeadX() const { return headX; }
    int getHeadY() const { return headY; }
    int getSnakeLength() const { return snakeLength; }
    Direction getDirection() const { return currentDirection; }
    int getTailX(int i) const { return (i < snakeLength) ? tailX[i] : -1; }
    int getTailY(int i) const { return (i < snakeLength) ? tailY[i] : -1; }

    // 设置器
    void setDirection(Direction d) { currentDirection = d; }
};

#endif // SNAKE_H
