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



enum{SCR_WIDTH = 800};
enum{SCR_HEIGHT = 600};

typedef struct pawn pawn;
typedef struct region region;
typedef struct potion potion;
void init_game_map();
void kill_game_map();
int main_game_map(int map_number,int players_color,int number_of_players);
void add_border_game_map(int map[SCR_HEIGHT][SCR_WIDTH]);
int place_check_game_map(region *regions,int region_index,int x,int y);
void create_random_map_game_map(int map[SCR_HEIGHT][SCR_WIDTH],int cnt,int cnt_each,int cnt_neutral,int initial_pawn_cnt,region *regions);
void change_region_color_game_map(int map[SCR_HEIGHT][SCR_WIDTH],int color,int start_x,int start_y);
void draw_map_game_map(int map[SCR_HEIGHT][SCR_WIDTH],region *regions,int cnt_regions,TTF_Font* font);
int move_pawns_game_map(int map[SCR_HEIGHT][SCR_WIDTH],pawn *moving_pawns,region *regions,int cnt_moving_pawns,int color_potions[10][10]);
int get_region_id_game_map(region *regions,int cnt_regions,int x,int y);
int deploy_game_map(region *regions,pawn *moving_pawns,int cnt_moving_pawns,int selected_source_region,int selected_dest_region,int color_potions[10][10]);
int is_reachable_game_map(region *regions,int cnt_regions,int x,int y);
void random_potion_coordinate_game_map(region *regions,int cnt_regions,potion *potions,int cnt_potions,int *x,int *y);
int process_potions_game_map(region *regions,int cnt_regions,pawn *moving_pawns,int cnt_moving_pawns,potion *potions,int cnt_potions,int color_potions[10][10],SDL_Rect potion_texture_rect);
int is_in_rectangle_game_map(int x1,int y1,int x2,int y2,int x,int y);
void show_text_game_map(char *str_text,SDL_Color color,TTF_Font* font,int x,int y);
int opponents_game_map(region *regions,int cnt_regions,pawn *moving_pawns,int cnt_moving_pawns,int players_color,int color_potions[10][10]);
void draw_potion_bar_game_map(int color_potions[10][10],SDL_Rect potion_texture_rect,int current_color);
#endif //PROJECT_GAME_MAP_H
