// game.h
#ifndef GAME_H
#define GAME_H

// 1. 基础常量定义
#define BOARD_SIZE 9
#define WIN_LENGTH 5
#define EMPTY_CELL '.'

// 2. 游戏状态枚举
typedef enum {
    GAME_RUNNING, // 游戏进行中
    GAME_X_WINS,  // X胜出
    GAME_O_WINS,  // O胜出
    GAME_DRAW     // 平局
} GameStatus;

// 3. 下棋结果枚举
typedef enum {
    MOVE_ACCEPTED,      // 可以下棋
    MOVE_OUT_OF_BOUNDS, // 当前位置在棋盘外
    MOVE_OCCUPIED       // 当前位置已占用
} MoveResult;

// 4. 游戏核心结构体
typedef struct {
    char cells[BOARD_SIZE][BOARD_SIZE]; // 棋盘信息
    char current_player;                // 当前玩家
    int move_count;                     // 步数统计
    GameStatus status;                  // 游戏状态
} Game;

// 5. 游戏逻辑函数声明（实现在 game.c）
GameStatus  check_game_status(Game* game, int row, int col);
const char* game_status_text(const Game* game);

#endif // GAME_H 结束