#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <windows.h>
#include <vector>
#include <string>
#include "../include/config.h"

class Snake;
class Food;
class TimeSystem;

/**
 * 渲染系统 - 完全解耦的显示模块
 * 
 * 职责：
 * - 管理控制台缓冲区
 * - 绘制游戏画面
 * - 显示UI信息
 */
class RenderSystem
{
private:
    HANDLE consoleHandle;
    std::vector<CHAR_INFO> frameBuffer;
    int windowWidth, windowHeight;
    bool isFullWidth;

    int mapToScreenX(int mapX) const;
    int mapToScreenY(int mapY) const;
    void putCharToBuffer(int x, int y, wchar_t ch, WORD attr);
    void putCellToBuffer(int mapX, int mapY, wchar_t ch, WORD attr);

public:
    RenderSystem(int w = WINDOW_WIDTH, int h = WINDOW_HEIGHT);

    void setFullWidth(bool fw) { isFullWidth = fw; }

    void render(Snake& snake, Food& food, int score, GameState state, TimeSystem& timeSystem);
    
private:
    void drawInstructionPanel();
};

#endif // RENDERSYSTEM_H
