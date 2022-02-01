//
// Created by r4hei on 2/1/2022.
//

#ifndef PROJECT_MAIN_MENU_H
#define PROJECT_MAIN_MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

void init_main_menu();
void kill_main_menu();
void show_text_main_menu(char *str_text,SDL_Color color,TTF_Font* font,int x,int y);
int is_in_rectangle_main_menu(int x1,int y1,int x2,int y2,int x,int y);
int main_main_menu();

#endif //PROJECT_MAIN_MENU_H
