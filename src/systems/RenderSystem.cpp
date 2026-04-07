#include "RenderSystem.h"
#include "../gameplay/Snake.h"
#include "../gameplay/Food.h"
#include "../systems/TimeSystem.h"

using namespace std;

RenderSystem::RenderSystem(int w, int h)
    : windowWidth(w), windowHeight(h), isFullWidth(true)
{
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    frameBuffer.resize(windowWidth * windowHeight);
    
    // 初始化控制台
    SetConsoleTitleW(L"贪吃蛇 - 工程级版本");
    COORD bufSize = {static_cast<SHORT>(windowWidth), static_cast<SHORT>(windowHeight)};
    SetConsoleScreenBufferSize(consoleHandle, bufSize);
    CONSOLE_CURSOR_INFO cursorInfo = {1, false};
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    SetConsoleOutputCP(CP_UTF8);
}

int RenderSystem::mapToScreenX(int mapX) const
{
    int base = CORNER_X + THICKNESS;
    return isFullWidth ? base + 2 * mapX : base + mapX;
}

int RenderSystem::mapToScreenY(int mapY) const
{
    return CORNER_Y + THICKNESS + mapY;
}

void RenderSystem::putCharToBuffer(int x, int y, wchar_t ch, WORD attr)
{
    if (x < 0 || x >= windowWidth || y < 0 || y >= windowHeight)
        return;
    CHAR_INFO& cell = frameBuffer[y * windowWidth + x];
    cell.Char.UnicodeChar = ch;
    cell.Attributes = attr;
}

void RenderSystem::putCellToBuffer(int mapX, int mapY, wchar_t ch, WORD attr)
{
    int sx = mapToScreenX(mapX);
    int sy = mapToScreenY(mapY);
    putCharToBuffer(sx, sy, ch, attr);
    if (isFullWidth)
        putCharToBuffer(sx + 1, sy, ch, attr);
}

void RenderSystem::render(Snake& snake, Food& food, int score, GameState state, TimeSystem& timeSystem)
{
    // 清空缓冲区
    WORD bgColor = COLOR_TEXT;
    for (int y = 0; y < windowHeight; ++y)
    {
        for (int x = 0; x < windowWidth; ++x)
        {
            CHAR_INFO& cell = frameBuffer[y * windowWidth + x];
            cell.Char.UnicodeChar = L' ';
            cell.Attributes = bgColor;
        }
    }

    // 绘制墙
    for (int x = -THICKNESS; x < STAGE_WIDTH + THICKNESS; ++x)
    {
        putCellToBuffer(x, -THICKNESS, L'#', COLOR_WALL);
        putCellToBuffer(x, STAGE_HEIGHT, L'#', COLOR_WALL);
    }
    for (int y = 0; y < STAGE_HEIGHT; ++y)
    {
        putCellToBuffer(-THICKNESS, y, L'#', COLOR_WALL);
        putCellToBuffer(STAGE_WIDTH, y, L'#', COLOR_WALL);
    }

    // 绘制食物（闪烁效果：每500ms闪烁一次）
    long long currentMs = timeSystem.getCurrentTimeMs();
    bool foodVisible = (currentMs / 500) % 2 == 0;
    if (foodVisible)
        putCellToBuffer(food.getPosX(), food.getPosY(), L'*', COLOR_FRUIT);

    // 绘制蛇
    for (int i = 0; i < snake.getSnakeLength(); ++i)
    {
        int x = snake.getTailX(i);
        int y = snake.getTailY(i);
        if (i == 0)
            putCellToBuffer(x, y, L'@', COLOR_SNAKE_HEAD);
        else
            putCellToBuffer(x, y, L'o', COLOR_SNAKE_BODY);
    }

    // 绘制信息面板
    int scoreLineY = STAGE_HEIGHT + THICKNESS * 2 + CORNER_Y;
    
    wstring scoreTxt = L"Score: " + to_wstring(score);
    for (size_t i = 0; i < scoreTxt.size(); ++i)
        putCharToBuffer(2 + i, scoreLineY, scoreTxt[i], COLOR_SCORE);

    int diffLevel = (score / DIFFICULTY_FACTOR) + 1;
    diffLevel = max(1, min(MAX_DIFFICULTY_LEVEL, diffLevel));
    wstring diffTxt = L"Difficulty: " + to_wstring(diffLevel) + L"/5";
    for (size_t i = 0; i < diffTxt.size(); ++i)
        putCharToBuffer(2 + i, scoreLineY + 1, diffTxt[i], COLOR_SCORE);

    // 状态特定信息
    if (state == STATE_PAUSED)
    {
        for (size_t i = 0; i < 6; ++i)
            putCharToBuffer(46 + i, 6, L"PAUSED"[i], COLOR_TEXT_HIGHLIGHT);
    }
    else if (state == STATE_GAME_OVER)
    {
        wstring gameOverStr = L"GAME OVER";
        for (size_t i = 0; i < gameOverStr.size(); ++i)
            putCharToBuffer(6 + i, 10, gameOverStr[i], COLOR_TEXT_HIGHLIGHT);
        
        wstring restartStr = L"Y: Restart  N: Quit";
        for (size_t i = 0; i < restartStr.size(); ++i)
            putCharToBuffer(4 + i, 11, restartStr[i], COLOR_TEXT_HIGHLIGHT);
    }

    // 绘制右侧说明面板
    drawInstructionPanel();

    // 提交帧缓冲到控制台
    COORD bufferSize = {static_cast<SHORT>(windowWidth), static_cast<SHORT>(windowHeight)};
    COORD bufferPos = {0, 0};
    SMALL_RECT writeRegion = {0, 0, static_cast<SHORT>(windowWidth - 1), static_cast<SHORT>(windowHeight - 1)};
    WriteConsoleOutputW(consoleHandle, frameBuffer.data(), bufferSize, bufferPos, &writeRegion);
}

void RenderSystem::drawInstructionPanel()
{
    // 右侧说明面板 (从第 49 列开始，向右平移 4 格)
    const int panelX = 50;
    const int panelY = 2;
    
    // 面板标题
    wstring title = L"═ 控制说明 ═";
    for (size_t i = 0; i < title.size(); ++i)
        putCharToBuffer(panelX - 2 + i, panelY, title[i], COLOR_TEXT_HIGHLIGHT);
    
    // 控制说明
    wstring instructions[] = {
        L"↑↓←→ : 移动",
        L"Space : 暂停",
        L"R     : 重新开始",
        L"F     : 切换宽度",
        L"Esc   : 退出",
        L"",
        L"难度等级：",
        L"1-超慢 2-慢",
        L"3-中 4-快",
        L"5-地狱"
    };
    
    for (int i = 0; i < 10; ++i)
    {
        for (size_t j = 0; j < instructions[i].size(); ++j)
            putCharToBuffer(panelX - 4 + j, panelY + 2 + i, instructions[i][j], COLOR_TEXT);
    }
}
