//
// Created by r4hei on 1/30/2022.
//

#ifndef PROJECT_GAME_MAP_H
#define PROJECT_GAME_MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

enum{SCREEN_WIDTH = 800};
enum{SCREEN_HEIGHT = 600};
void init_game_map();
void kill_game_map();
void main_game_map();
void add_border_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH]);
void create_random_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],int cnt,int cnt_each);
void draw_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH]);

#endif //PROJECT_GAME_MAP_H
