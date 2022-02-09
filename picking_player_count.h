//
// Created by r4hei on 2/9/2022.
//

#ifndef PROJECT_PICKING_PLAYER_COUNT_H
#define PROJECT_PICKING_PLAYER_COUNT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

void init_picking_player_count();
void kill_picking_player_count();
void show_text_picking_player_count(char *str_text,SDL_Color color,TTF_Font* font,int x,int y);
int is_in_rectangle_picking_player_count(int x1,int y1,int x2,int y2,int x,int y);
int main_picking_player_count();
#endif //PROJECT_PICKING_PLAYER_COUNT_H
