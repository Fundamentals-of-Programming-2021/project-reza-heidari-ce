//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "username_menu.h"
#include "game_map.h"
#include "main_menu.h"
#include "leaderboard.h"
#include "maps_menu.h"
#include "picking_color.h"
#include "win_loose_menu.h"
#include "picking_player_count.h"
int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("SDL_image could not initialize! IMG_Error: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        return false;
    }
    return true;
}
void kill() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
void run_username_menu();
void run_main_menu(char *user_name);
void run_game_map(char *user_name,int map_number,int player_color,int cnt_players);
void run_leaderboard(char *user_name);
void run_maps_menu(char *user_name);
void run_picking_color(char *user_name,int map_number,int cnt_players);
void run_win_loose_menu(char *user_name,int points);
void run_picking_player_count(char *user_name,int map_number);
void run_username_menu(){
    char *user_name=main_username_menu();
    if(user_name==NULL)return;
    run_main_menu(user_name);
    free(user_name);
}
void run_main_menu(char *user_name){
    int next_menu_id=main_main_menu();
    if(next_menu_id==-1)return;
    if(next_menu_id==1)run_maps_menu(user_name);
    if(next_menu_id==2){
        int temp=1;
        //continue//
    }
    if(next_menu_id==3)run_leaderboard(user_name);
    if(next_menu_id==4)run_username_menu();
}
void run_maps_menu(char *user_name){
    int next_menu_id=main_maps_menu();
    if(next_menu_id>0){
        if(next_menu_id!=4){
            if(next_menu_id==5)run_picking_color(user_name,next_menu_id,2);
            else run_picking_color(user_name,next_menu_id,4);
        }
        else run_picking_player_count(user_name,next_menu_id);
    }
    if(next_menu_id==-1)return;
    if(next_menu_id==-2)run_main_menu(user_name);
}
void run_picking_player_count(char *user_name,int map_number){
    int next_menu_id=main_picking_player_count();
    if(next_menu_id==-1)return;
    else if(next_menu_id==-2)run_maps_menu(user_name);
    else{
        run_picking_color(user_name,map_number,next_menu_id);
    }
}
void run_picking_color(char *user_name,int map_number,int cnt_players){
    int next_menu_id=main_picking_color(cnt_players);
    if(next_menu_id==-1)return;
    else if(next_menu_id==-2){
        if(map_number!=4)run_maps_menu(user_name);
        else run_picking_player_count(user_name,map_number);
    }
    else{
        run_game_map(user_name,map_number,next_menu_id,cnt_players);
    }
}
void run_game_map(char *user_name,int map_number,int player_color,int cnt_players){
    int points=main_game_map(map_number,player_color,cnt_players);
    if(points==-1)return;
    else if(points==-2)run_main_menu(user_name);
    else{
        run_win_loose_menu(user_name,points);
    }
}
void run_win_loose_menu(char *user_name,int points){
    int next_menu_id= main_win_loose_menu(user_name,points);
    if(next_menu_id==-1)return;
    if(next_menu_id==-2)run_main_menu(user_name);
}
void run_leaderboard(char *user_name){
    int next_menu_id=main_leaderboard();
    if(next_menu_id==-1)return;
    if(next_menu_id==1)run_main_menu(user_name);
}
int main() {
    init();
    run_username_menu();
    kill();

    return 0;
}

