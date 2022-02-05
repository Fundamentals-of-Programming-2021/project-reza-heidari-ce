//
// Created by r4hei on 2/5/2022.
//

#ifndef PROJECT_MAPS_MENU_H
#define PROJECT_MAPS_MENU_H
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

void init_maps_menu();
void kill_maps_menu();
void show_text_maps_menu(char *str_text,SDL_Color color,TTF_Font* font,int x,int y);
int is_in_rectangle_maps_menu(int x1,int y1,int x2,int y2,int x,int y);
int main_maps_menu();

#endif //PROJECT_MAPS_MENU_H
