//
// Created by r4hei on 1/29/2022.
//

#include "username_menu.h"
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

void init_username_menu() {
    window = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_StartTextInput();
}
void kill_username_menu() {


    SDL_StopTextInput();


    SDL_DestroyTexture( background_texture );
    background_texture = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
}
void show_text_username_menu(char *str_text,SDL_Color color,TTF_Font* font,int x,int y){
    SDL_Surface* text = TTF_RenderText_Solid( font, str_text, color );
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface( renderer, text );
    SDL_Rect dest = { x,y, text->w, text->h };
    SDL_RenderCopy( renderer, text_texture,NULL, &dest );
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_texture);
}
char *main_username_menu() {

    init_username_menu();
    background_texture = IMG_LoadTexture(renderer,"../username_menu_bg.png");
    TTF_Font* font1 = TTF_OpenFont("../Lato-Black.ttf", 24);
    TTF_Font* font2 = TTF_OpenFont("../metal-lord.ttf", 36);

    SDL_Rect background_texture_rect = {.x=0, .y=0, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT};

    SDL_Color credits_color = { 0x2E, 0xCA, 0x1D };
    SDL_Color user_name_color = { 0, 0, 0 };
    SDL_Color color_title = { 0xB2, 0x10, 0x10 };

    char *user_name=(char *) malloc(sizeof(char) * 100);
    user_name[0]='\0';
    strcat(user_name,"Enter you user name : ");

    int closed=0;
    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, &background_texture_rect);
        show_text_username_menu(user_name,user_name_color,font1,SCREEN_WIDTH/2-280,SCREEN_HEIGHT/2-30);
        show_text_username_menu("Welcome to State.io",color_title,font2,SCREEN_WIDTH/2-180,60);
        show_text_username_menu("Press Enter to continue",credits_color,font1,SCREEN_WIDTH/2-130,SCREEN_HEIGHT/2+50);
        show_text_username_menu("Created by Reza Heidari",credits_color,font1,SCREEN_WIDTH/2-130,SCREEN_HEIGHT-60);

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    closed=1;
                    shallExit = SDL_TRUE;
                    break;
                case SDL_TEXTINPUT:
                    strcat(user_name,sdlEvent.text.text);
                    break;
                case SDL_KEYUP:
                    if(sdlEvent.key.keysym.sym == SDLK_RETURN){
                        shallExit = SDL_TRUE;
                    }
                    else if(sdlEvent.key.keysym.sym == SDLK_BACKSPACE && strlen(user_name)>22){
                        user_name[strlen(user_name)-1]='\0';
                    }
                    break;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    TTF_CloseFont( font1 );
    TTF_CloseFont( font2 );
    kill_username_menu();
    char temp_str[100];
    for(int i=22;i<strlen(user_name);i++)temp_str[i-22]=user_name[i];
    temp_str[strlen(user_name)-22]='\0';
    strcpy(user_name,temp_str);
    if(closed){
        free(user_name);
        return NULL;
    }



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
    if(index==-1){
        strcpy(players[cnt_players].name,user_name);
        players[cnt_players].points=0;
        index=cnt_players;
        cnt_players++;
        FILE *temp_ptr= fopen("../player_scores_temp.txt","w");
        fprintf(temp_ptr,"%d\n",cnt_players);
        for(int i=0;i<cnt_players;i++){
            fprintf(temp_ptr,"%s\n%d\n",players[i].name,players[i].points);
        }
        remove("../player_scores.txt");
        rename("../player_scores_temp.txt","../player_scores.txt");
        fclose(temp_ptr);
    }

    return user_name;
}

