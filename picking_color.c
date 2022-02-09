//
// Created by r4hei on 2/5/2022.
//

#include "picking_color.h"
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


void init_picking_color() {
    window = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}
void kill_picking_color() {

    SDL_DestroyTexture( background_texture );
    background_texture = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
}
void show_text_picking_color(char *str_text,SDL_Color color,TTF_Font* font,int x,int y){
    SDL_Surface* text = TTF_RenderText_Solid( font, str_text, color );
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface( renderer, text );
    SDL_Rect dest = { x,y, text->w, text->h };
    SDL_RenderCopy( renderer, text_texture,NULL, &dest );
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_texture);
}
int is_in_rectangle_picking_color(int x1,int y1,int x2,int y2,int x,int y){
    if(x<x2 && x>x1 && y<y2 && y>y1)return 1;
    return 0;
}
int main_picking_color(int cnt_players) {

    init_picking_color();
    background_texture = IMG_LoadTexture(renderer,"../main_menu_bg.png");
    TTF_Font* font1 = TTF_OpenFont("../Lato-Black.ttf", 24);
    TTF_Font* font3 = TTF_OpenFont("../Lato-Black.ttf", 30);
    TTF_Font* font2 = TTF_OpenFont("../metal-lord.ttf", 36);

    SDL_Rect background_texture_rect = {.x=0, .y=0, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT};

    SDL_Color color_blue = { 0x00, 0x00, 0xff };
    SDL_Color color_red = { 0xff, 0x00, 0x00 };
    SDL_Color color_green = { 0x00, 0xa0, 0x00 };
    SDL_Color color_yellow = { 0xff, 0xff, 0x00 };
    SDL_Color color_button = { 0xB2, 0x10, 0x10 };
    SDL_Color color_title = { 0x00, 0x00, 0x00 };

    int next_menu_id=-1;

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, NULL, &background_texture_rect);

        show_text_picking_color("pick a color",color_title,font3,320,100);

        roundedBoxRGBA(renderer,245,177,555,227,30,0x2b,0xde,0xc9,0xa9);
        roundedBoxRGBA(renderer,245,242,555,292,30,0x2b,0xde,0xc9,0xa9);
        show_text_picking_color("red",color_red,font2,370,180);
        show_text_picking_color("green",color_green,font2,350,245);
        if(cnt_players>2){
            roundedBoxRGBA(renderer, 245, 307, 555, 357, 30, 0x30, 0xde, 0xc9, 0xa9);
            show_text_picking_color("blue",color_blue,font2,365,310);
        }
        if(cnt_players>3){
            roundedBoxRGBA(renderer, 245, 372, 555, 422, 30, 0x30, 0xde, 0xc9, 0xa9);
            show_text_picking_color("yellow",color_yellow,font2,350,375);
        }

        roundedBoxRGBA(renderer,50,500,150,550,10,0x2b,0xde,0xc9,0xa9);
        show_text_picking_color("back",color_button,font1,75,510);

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(is_in_rectangle_picking_color(245,177,555,227,sdlEvent.button.x,sdlEvent.button.y)){
                        next_menu_id=1;
                        shallExit = SDL_TRUE;
                    }
                    if(is_in_rectangle_picking_color(245,242,555,292,sdlEvent.button.x,sdlEvent.button.y)){
                        next_menu_id=2;
                        shallExit = SDL_TRUE;
                    }
                    if(cnt_players>2) {
                        if (is_in_rectangle_picking_color(245, 307, 555, 357, sdlEvent.button.x, sdlEvent.button.y)) {
                            next_menu_id = 3;
                            shallExit = SDL_TRUE;
                        }
                    }
                    if(cnt_players>3) {
                        if (is_in_rectangle_picking_color(245, 372, 555, 422, sdlEvent.button.x, sdlEvent.button.y)) {
                            next_menu_id = 5;
                            shallExit = SDL_TRUE;
                        }
                    }
                    if(is_in_rectangle_picking_color(50,500,150,550,sdlEvent.button.x,sdlEvent.button.y)){
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
    TTF_CloseFont(font3);
    kill_picking_color();

    return next_menu_id;
}


