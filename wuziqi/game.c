
#include "game.h"

// 4 个方向的行/列增量
static const int DIR_R[4] = { 0, 1, 1,  1 };
static const int DIR_C[4] = { 1, 0, 1, -1 };

// 判断刚落下的这一颗 (row,col) 有没有形成五连
static int is_winning_move(const Game* game, int row, int col) {
    char who = game->cells[row][col];   // 刚下的是谁

    for (int d = 0; d < 4; d++) {       // 4 个方向各查一次
        int count = 1;                  // ★ 算上刚下的自己

        // ---------- 往正方向数 ----------
        for (int step = 1; step < WIN_LENGTH; step++) {
            int r = row + DIR_R[d] * step;
            int c = col + DIR_C[d] * step;

            // 出界就停（必须写在访问 cells 之前！）
            if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE) break;
            // 不是同一方的子就停
            if (game->cells[r][c] != who) break;

            count++;
        }

        // ---------- 往反方向数 ----------
        for (int step = 1; step < WIN_LENGTH; step++) {
            int r = row - DIR_R[d] * step;
            int c = col - DIR_C[d] * step;

            if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE) break;
            if (game->cells[r][c] != who) break;

            count++;
        }

        if (count >= WIN_LENGTH) return 1;   
    }
    return 0;   
}

GameStatus check_game_status(Game* game, int row, int col) {
    if (game->cells[row][col] != EMPTY_CELL && is_winning_move(game, row, col)) {
        // 赢了：看刚下的是谁
        game->status = (game->cells[row][col] == 'X') ? GAME_X_WINS : GAME_O_WINS;
    } 
    else if (game->move_count >= BOARD_SIZE * BOARD_SIZE) 
        game->status = GAME_DRAW;
    else {
        game->status = GAME_RUNNING;   
    }
    return game->status;
}

const char* game_status_text(const Game* game) {
    switch (game->status) {
        case GAME_X_WINS: return "Game over: X wins!";
        case GAME_O_WINS: return "Game over: O wins!";
        case GAME_DRAW:   return "Game over: Draw!";
        default:          return "Game running...";
    }
}

