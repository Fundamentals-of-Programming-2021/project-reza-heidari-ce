//
// Created by r4hei on 1/29/2022.
//

#include "username_menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FPS = 60;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture *background_texture;
TTF_Font* font;


void init_username_menu() {
    window = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_StartTextInput();
}
void kill_username_menu() {
    SDL_StopTextInput();

    TTF_CloseFont( font );
    SDL_DestroyTexture( background_texture );
    background_texture = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
}
char* main_username_menu() {

    init_username_menu();
    background_texture = IMG_LoadTexture(renderer,"../sample.bmp");
    font = TTF_OpenFont("../Lato-Black.ttf", 24);

    SDL_Rect texture_rect = {.x=0, .y=0, .w=SCREEN_WIDTH, .h=SCREEN_HEIGHT};

    SDL_Surface* text;
    SDL_Texture* text_texture;
    SDL_Color color = { 0, 0, 0 };


    char user_name[100]="Enter you user name : ";

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        text = TTF_RenderText_Solid( font, user_name, color );
        text_texture = SDL_CreateTextureFromSurface( renderer, text );
        SDL_Rect dest = { SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2, text->w, text->h };

        SDL_RenderCopy(renderer, background_texture, NULL, &texture_rect);
        SDL_RenderCopy( renderer, text_texture,NULL, &dest );

        SDL_FreeSurface(text);
        SDL_DestroyTexture(text_texture);

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_TEXTINPUT:
                    strcat(user_name,sdlEvent.text.text);
                    break;
                case SDL_KEYDOWN:
                    if(sdlEvent.key.keysym.sym == SDLK_BACKSPACE && strlen(user_name)>22){
                        user_name[strlen(user_name)-1]='\0';
                    }
                    break;
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    kill_username_menu();
    return NULL;
}

