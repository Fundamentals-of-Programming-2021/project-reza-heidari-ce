//
// Created by r4hei on 2/2/2022.
//

#ifndef PROJECT_LEADERBOARD_H
#define PROJECT_LEADERBOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

void init_leaderboard();
void kill_leaderboard();
void show_text_leaderboard(char *str_text,SDL_Color color,TTF_Font* font,int x,int y);
int is_in_rectangle_leaderboard(int x1,int y1,int x2,int y2,int x,int y);
void main_leaderboard(char *user_name);

#endif //PROJECT_LEADERBOARD_H
