//
// Created by r4hei on 2/5/2022.
//

#ifndef PROJECT_PICKING_COLOR_H
#define PROJECT_PICKING_COLOR_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

void init_picking_color();
void kill_picking_color();
void show_text_picking_color(char *str_text,SDL_Color color,TTF_Font* font,int x,int y);
int is_in_rectangle_picking_color(int x1,int y1,int x2,int y2,int x,int y);
int main_picking_color(int cnt_players);

#endif //PROJECT_PICKING_COLOR_H
