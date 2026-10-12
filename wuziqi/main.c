#include <stdio.h>
#include "game.h"
#include <stdlib.h> 
#include "console.h"
#include <windows.h>

static DWORD g_old_in_mode = 0;          // 存放控制台的原始模式，退出时要还

void enable_mouse_input(void) {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(hIn, &g_old_in_mode);          // 备份原始模式
    DWORD mode = g_old_in_mode;                   // 从备份改（不写这个，mode 是垃圾值）

    mode &= ~ENABLE_QUICK_EDIT_MODE;              // 关快速编辑
    mode |= ENABLE_EXTENDED_FLAGS;                // 开总闸（不开的话会被系统忽略）
    mode |= ENABLE_MOUSE_INPUT;                   // 开鼠标输入

    SetConsoleMode(hIn, mode);                    // 提交
}

void restore_console(void) {                      // 还原
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), g_old_in_mode);
}

int main() {
    enable_mouse_input();
    Game game;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            game.cells[r][c] = EMPTY_CELL;
        }
    }
    draw_board(&game);

    game.current_player = 'X'; 
    game.move_count     = 0;
    game.status = GAME_RUNNING;

    int mouse_x, mouse_y;
    while(game.status==GAME_RUNNING){    
        get_mouse_left_click(&mouse_x, &mouse_y); 
        int row = (mouse_y - 1) / 2;           
        int col = (mouse_x - 1) / 4;            
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
            continue;                              
        game_place(&game, mouse_x,mouse_y);
        clear_screen();
        draw_board(&game) ;
        game_status_text(&game);
        game.status=check_game_status(&game, row,col );
        printf(">>> mouse=(%d,%d) row=%d col=%d moves=%d now=%c\n",
            mouse_x, mouse_y,
            (mouse_y-1)/2, (mouse_x-1)/4,
            game.move_count, game.current_player);
    
    }                     
    printf("%s\n",game_status_text(&game));
    system("pause");
    restore_console();  

    return 0;
}

