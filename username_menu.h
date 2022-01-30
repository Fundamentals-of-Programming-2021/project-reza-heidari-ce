//
// Created by r4hei on 1/29/2022.
//

#ifndef PROJECT_USERNAME_MENU_H
#define PROJECT_USERNAME_MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>



void init_username_menu();
void kill_username_menu();
void show_text_username_menu(char *str_text,SDL_Color color,TTF_Font* font,int x,int y);
char *main_username_menu();


#endif //PROJECT_USERNAME_MENU_H
