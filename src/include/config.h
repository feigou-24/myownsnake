#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>
#include <chrono>
#include <algorithm>

// ============================================================
// 游戏配置常量
// ============================================================
#define STAGE_WIDTH 20
#define STAGE_HEIGHT 20
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 25
#define CORNER_X 1
#define CORNER_Y 1
#define THICKNESS 1
#define MAX_SNAKE_LENGTH 100
#define DIFFICULTY_FACTOR 50
#define MAX_DIFFICULTY_LEVEL 5

// ============================================================
// 控制台颜色代码
// ============================================================
#define COLOR_WALL 0x01
#define COLOR_TEXT 0x0B
#define COLOR_TEXT_HIGHLIGHT 0x1F
#define COLOR_SCORE 0x0A
#define COLOR_FRUIT 0x0E
#define COLOR_SNAKE_HEAD 0x0B
#define COLOR_SNAKE_BODY 0x09

// ============================================================
// 游戏枚举定义
// ============================================================
enum Direction { DIR_STOP = 0, DIR_LEFT = 1, DIR_RIGHT = 2, DIR_UP = 3, DIR_DOWN = 4 };

enum GameState
{
    STATE_MENU = 0,       // 菜单状态
    STATE_RUNNING = 1,    // 运行中
    STATE_PAUSED = 2,     // 暂停
    STATE_GAME_OVER = 3,  // 游戏结束
    STATE_EXIT = 4        // 退出
};

#endif // CONFIG_H
