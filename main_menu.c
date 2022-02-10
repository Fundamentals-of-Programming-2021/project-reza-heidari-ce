//
// Created by r4hei on 2/1/2022.
//

#include "main_menu.h"
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


void init_main_menu() {
    window = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}
void kill_main_menu() {

    SDL_DestroyTexture( background_texture );
    background_texture = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
}
void show_text_main_menu(char *str_text,SDL_Color color,TTF_Font* font,int x,int y){
    SDL_Surface* text = TTF_RenderText_Solid( font, str_text, color );
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface( renderer, text );
    SDL_Rect dest = { x,y, text->w, text->h };
    SDL_RenderCopy( renderer, text_texture,NULL, &dest );
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_texture);
}
int is_in_rectangle_main_menu(int x1,int y1,int x2,int y2,int x,int y){
    if(x<x2 && x>x1 && y<y2 && y>y1)return 1;
    return 0;
}
int main_main_menu() {

    init_main_menu();
    background_texture = IMG_LoadTexture(renderer,"../main_menu_bg.png");
    TTF_Font* font1 = TTF_OpenFont("../Lato-Black.ttf", 24);
    TTF_Font* font2 = TTF_OpenFont("../metal-lord.ttf", 36);

    SDL_Rect background_texture_rect = {.x=0, .y=0, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT};

    SDL_Color color_title = { 0xB2, 0x10, 0x10 };

    int next_menu_id=-1;

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, &background_texture_rect);

        roundedBoxRGBA(renderer,245,177,555,227,30,0x2b,0xde,0xc9,0xa9);
       // roundedBoxRGBA(renderer,245,242,555,292,30,0x2b,0xde,0xc9,0xa9);
        roundedBoxRGBA(renderer,245,242,555,292,30,0x30,0xde,0xc9,0xa9);
        roundedBoxRGBA(renderer,245,307,555,357,30,0x30,0xde,0xc9,0xa9);
        show_text_main_menu("new game",color_title,font2,320,180);
        //show_text_main_menu("continue",color_title,font2,320,245);
        show_text_main_menu("leaderboard",color_title,font2,290,245);
        show_text_main_menu("Change user name",color_title,font2,245,310);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(is_in_rectangle_main_menu(245,177,555,227,sdlEvent.button.x,sdlEvent.button.y)){
                        next_menu_id=1;
                        shallExit = SDL_TRUE;
                    }
                  /*  else if(is_in_rectangle_main_menu(245,242,555,292,sdlEvent.button.x,sdlEvent.button.y)){
                        next_menu_id=2;
                        shallExit = SDL_TRUE;
                    }*/
                    else if(is_in_rectangle_main_menu(245,242,555,292,sdlEvent.button.x,sdlEvent.button.y)){
                        next_menu_id=3;
                        shallExit = SDL_TRUE;
                    }
                    else if(is_in_rectangle_main_menu(245,307,555,357,sdlEvent.button.x,sdlEvent.button.y)){
                        next_menu_id=4;
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
    kill_main_menu();

    return next_menu_id;
}


