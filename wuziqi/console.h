// console.h
#ifndef CONSOLE_H
#define CONSOLE_H

#include "game.h" 

void draw_board(const Game* game);
void get_mouse_left_click(int* out_x, int* out_y);
MoveResult game_place(Game* game, int mouse_x, int mouse_y) ;
void clear_screen(void);
#endif