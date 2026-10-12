// console.c
#include <stdio.h>
#include "console.h"
#include <windows.h>

void draw_board(const Game* game) {
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("+---");
    }
    printf("+\n");

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf("| %c ", game->cells[row][col]); 
        }
        printf("|\n");

        for (int col = 0; col < BOARD_SIZE; col++) {
            printf("+---");
        }
        printf("+\n");
    }
}
void get_mouse_left_click(int* out_x, int* out_y) {
    
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);//拿钥匙
    
    INPUT_RECORD input;//
    DWORD events;

    while (1) {
        // 死等，直到有人操作
        ReadConsoleInput(hInput, &input, 1, &events);
        
        // 判断是不是鼠标事件
        if (input.EventType == MOUSE_EVENT) {
            // 把事件里的鼠标信息拆出来
            MOUSE_EVENT_RECORD mer = input.Event.MouseEvent;
            
            // 判断是不是“左键按下”并且“没有拖动”
            // FROM_LEFT_1ST_BUTTON_PRESSED 就是左键
            if ((mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) && mer.dwEventFlags == 0) {
                // 将鼠标位置通过指针赋给外面的变量
                *out_x = mer.dwMousePosition.X;
                *out_y = mer.dwMousePosition.Y;
                
                return; // 找到了，结束等待
            }
        }
    }
}

MoveResult game_place(Game* game, int mouse_x, int mouse_y) {

    if (mouse_x < 0 || mouse_x > 36) 
        return MOVE_OUT_OF_BOUNDS;
    if (mouse_y < 0 || mouse_y > 18) 
        return MOVE_OUT_OF_BOUNDS;
        
    int col = (mouse_x - 1) / 4;                  
    int row = (mouse_y - 1) / 2;    

    if (game->cells[row][col] != EMPTY_CELL) {
        return MOVE_OCCUPIED;
    }

    game->cells[row][col] = game->current_player;
    game->move_count++;                   

    if (game->current_player == 'X') {
        game->current_player = 'O';
    } else {
        game->current_player = 'X';
    }

    return MOVE_ACCEPTED;
}

 void clear_screen(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;
    COORD home = { 0, 0 };

    GetConsoleScreenBufferInfo(hOut, &csbi);
    DWORD cells = (DWORD)csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacterA(hOut, ' ', cells, home, &written);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, cells, home, &written);
    SetConsoleCursorPosition(hOut, home);
}