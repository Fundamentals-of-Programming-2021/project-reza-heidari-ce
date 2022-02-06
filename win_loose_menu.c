//
// Created by r4hei on 2/6/2022.
//

#include "win_loose_menu.h"
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

void init_win_loose_menu() {
    window = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}
void kill_win_loose_menu() {

    SDL_DestroyTexture( background_texture );
    background_texture = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
}
void show_text_win_loose_menu(char *str_text,SDL_Color color,TTF_Font* font,int x,int y){
    SDL_Surface* text = TTF_RenderText_Solid( font, str_text, color );
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface( renderer, text );
    SDL_Rect dest = { x,y, text->w, text->h };
    SDL_RenderCopy( renderer, text_texture,NULL, &dest );
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_texture);
}
int is_in_rectangle_win_loose_menu(int x1,int y1,int x2,int y2,int x,int y){
    if(x<x2 && x>x1 && y<y2 && y>y1)return 1;
    return 0;
}
int main_win_loose_menu(char *user_name,int points) {
    if(points<15)points*=-1;

    init_win_loose_menu();
    background_texture = IMG_LoadTexture(renderer,"../main_menu_bg.png");
    TTF_Font* font1 = TTF_OpenFont("../Lato-Black.ttf", 24);
    TTF_Font* font2 = TTF_OpenFont("../metal-lord.ttf", 44);

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

    int index=-1;
    for(int i=0;i<cnt_players;i++){
        if(!strcmp(players[i].name,user_name)){
            index=i;
            break;
        }
    }
    if(index!=-1){
        players[index].points+=points;
    }
    else{
        strcpy(players[cnt_players].name,user_name);
        players[cnt_players].points+=points;
        index=cnt_players;
        cnt_players++;
    }
    FILE *temp_ptr= fopen("../player_scores_temp.txt","w");
    fprintf(temp_ptr,"%d\n",cnt_players);
    for(int i=0;i<cnt_players;i++){
        fprintf(temp_ptr,"%s\n%d\n",players[i].name,players[i].points);
    }
    remove("../player_scores.txt");
    rename("../player_scores_temp.txt","../player_scores.txt");
    fclose(temp_ptr);

    int next_menu_id=-1;

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, &background_texture_rect);


        if(points>0){
            show_text_win_loose_menu("You won",user_name_color,font2,300,100);
        }
        else{
            show_text_win_loose_menu("You lost",color_button,font2,300,100);
        }
        char temp_points[10];
        sprintf(temp_points,"%d",players[index].points);
        show_text_win_loose_menu("your total point is : ",user_name_color,font1,100,300);
        show_text_win_loose_menu(temp_points,user_name_color,font1,350,300);


        roundedBoxRGBA(renderer,50,500,300,550,10,0x2b,0xde,0xc9,0xa9);
        show_text_win_loose_menu("back to main menu",color_button,font1,75,510);


        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(is_in_rectangle_win_loose_menu(50,500,300,550,sdlEvent.button.x,sdlEvent.button.y)){
                        next_menu_id=-2;
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
    kill_win_loose_menu();
    return next_menu_id;
}


