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

enum{SCREEN_WIDTH = 600};
enum{SCREEN_HEIGHT = 400};
typedef struct pawn pawn;
typedef struct region region;
typedef struct potion potion;
void init_game_map();
void kill_game_map();
void main_game_map();
void add_border_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH]);
int place_check_game_map(region *regions,int region_index,int x,int y);
void create_random_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],int cnt,int cnt_each,int cnt_neutral,int initial_pawn_cnt,region *regions);
void change_region_color_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],int color,int start_x,int start_y);
void draw_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],region *regions,int cnt_regions);
int move_pawns_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],pawn *moving_pawns,region *regions,int cnt_moving_pawns);
int get_region_id_game_map(region *regions,int cnt_regions,int x,int y);
int deploy_game_map(region *regions,pawn *moving_pawns,int cnt_moving_pawns,int selected_source_region,int selected_dest_region);
int is_reachable(region *regions,int cnt_regions,int x,int y);
void random_potion_coordinate(region *regions,int cnt_regions,int *x,int *y);
#endif //PROJECT_GAME_MAP_H
