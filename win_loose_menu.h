//
// Created by r4hei on 2/6/2022.
//

#ifndef PROJECT_WIN_LOOSE_MENU_H
#define PROJECT_WIN_LOOSE_MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

typedef struct player player;

void init_win_loose_menu();
void kill_win_loose_menu();
void show_text_win_loose_menu(char *str_text,SDL_Color color,TTF_Font* font,int x,int y);
int is_in_rectangle_win_loose_menu(int x1,int y1,int x2,int y2,int x,int y);
int main_win_loose_menu(char *user_name,int points);

#endif //PROJECT_WIN_LOOSE_MENU_H
