#include "Snake.h"

Snake::Snake() : snakeLength(1), currentDirection(DIR_STOP)
{
    init();
}

void Snake::init()
{
    headX = mapWidth / 2;
    headY = mapHeight / 2;
    snakeLength = 1;
    currentDirection = DIR_STOP;

    tailX[0] = headX;
    tailY[0] = headY;
    for (int i = 1; i < MAX_SNAKE_LENGTH; i++)
    {
        tailX[i] = 0;
        tailY[i] = 0;
    }
}

bool Snake::moveSnake(Direction newDir)
{
    // 更新方向
    if (newDir != DIR_STOP && newDir != currentDirection)
        currentDirection = newDir;

    // 移动蛇头
    switch (currentDirection)
    {
    case DIR_LEFT:
        headX--;
        break;
    case DIR_RIGHT:
        headX++;
        break;
    case DIR_UP:
        headY--;
        break;
    case DIR_DOWN:
        headY++;
        break;
    default:
        break;
    }

    // 穿墙处理（边界环绕）
    if (headX >= mapWidth) headX = 0;
    else if (headX < 0) headX = mapWidth - 1;
    if (headY >= mapHeight) headY = 0;
    else if (headY < 0) headY = mapHeight - 1;

    // 检查蛇头是否与身体碰撞
    for (int i = 1; i < snakeLength; i++)
    {
        if (tailX[i] == headX && tailY[i] == headY)
            return false;  // 游戏结束
    }

    // 更新蛇身
    int prevX = headX;
    int prevY = headY;
    int tmpX, tmpY;

    for (int i = 0; i < snakeLength; i++)
    {
        tmpX = tailX[i];
        tmpY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = tmpX;
        prevY = tmpY;
    }

    return true;  // 游戏继续
}

void Snake::grow()
{
    if (snakeLength < MAX_SNAKE_LENGTH)
        snakeLength++;
}
