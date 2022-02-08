//
// Created by r4hei on 2/2/2022.
//

#include "leaderboard.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int FPS = 60;
static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture *background_texture;

struct player{
    int points;
    char name[100];
};

void init_leaderboard() {
    window = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}
void kill_leaderboard() {

    SDL_DestroyTexture( background_texture );
    background_texture = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
}
void show_text_leaderboard(char *str_text,SDL_Color color,TTF_Font* font,int x,int y){
    SDL_Surface* text = TTF_RenderText_Solid( font, str_text, color );
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface( renderer, text );
    SDL_Rect dest = { x,y, text->w, text->h };
    SDL_RenderCopy( renderer, text_texture,NULL, &dest );
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_texture);
}
int is_in_rectangle_leaderboard(int x1,int y1,int x2,int y2,int x,int y){
    if(x<x2 && x>x1 && y<y2 && y>y1)return 1;
    return 0;
}
int main_leaderboard() {

    init_leaderboard();
    background_texture = IMG_LoadTexture(renderer,"../main_menu_bg.png");
    TTF_Font* font1 = TTF_OpenFont("../Lato-Black.ttf", 24);
    TTF_Font* font2 = TTF_OpenFont("../metal-lord.ttf", 36);

    SDL_Rect background_texture_rect = {.x=0, .y=0, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT};

    SDL_Color credits_color = { 0x2E, 0xCA, 0x1D };
    SDL_Color user_name_color = { 0, 0, 0 };
    SDL_Color color_button = { 0xB2, 0x10, 0x10 };


    FILE *fptr= fopen("../player_scores.txt","r");
    int cnt_players;
    fscanf(fptr," %d",&cnt_players);
    player players[100];
    for(int i=0;i<cnt_players;i++){
        fscanf(fptr," %[^\n]s",players[i].name);
        fscanf(fptr," %d",&(players[i].points));
    }
    fclose(fptr);
    for(int i=0;i<cnt_players;i++){
        for(int j=0;j<i;j++){
            if(players[i].points>players[j].points){
                player temp_player;
                temp_player.points=players[i].points;
                strcpy(temp_player.name,players[i].name);
                players[i].points=players[j].points;
                strcpy(players[i].name,players[j].name);
                players[j].points=temp_player.points;
                strcpy(players[j].name,temp_player.name);
            }
        }
    }

    //printf("%d",cnt_players);
    int next_menu_id=-1;

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, &background_texture_rect);

        for(int i=0;i<9 && i<cnt_players;i++){
            show_text_leaderboard(players[i].name,user_name_color,font1,50,50+50*i);
            char temp_points[10];
            sprintf(temp_points,"%d",players[i].points);
            show_text_leaderboard(temp_points,user_name_color,font1,650,50+50*i);
        }



        roundedBoxRGBA(renderer,50,500,150,550,10,0x2b,0xde,0xc9,0xa9);
        show_text_leaderboard("back",color_button,font1,75,510);


        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(is_in_rectangle_leaderboard(50,500,150,550,sdlEvent.button.x,sdlEvent.button.y)){
                        next_menu_id=1;
                        shallExit = SDL_TRUE;
                    }
                    break;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    TTF_CloseFont( font1 );
    TTF_CloseFont( font2 );
    kill_leaderboard();
    return next_menu_id;
}


