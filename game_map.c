//
// Created by r4hei on 1/30/2022.
//

#include "game_map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


static const int FPS = 60;

static SDL_Window* window;
static SDL_Renderer* renderer;

void init_game_map() {
    window = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}
void kill_game_map() {
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
}
void add_border_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH]){
    for(int i=1;i<SCREEN_HEIGHT-1;i++){
        for(int j=1;j<SCREEN_WIDTH-1;j++){
            if(map[i][j]!=0 && map[i][j]!=-1){
                if(map[i][j+1]==0 || map[i][j-1]==0 || map[i+1][j]==0 || map[i-1][j]==0)map[i][j]=-1;
            }
        }
    }
}
void create_random_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],int cnt,int cnt_each){
    for(int j=1;j<=cnt_each;j++) {
        for(int i=1;i<=cnt;i++){
            int start_x = rand() % SCREEN_WIDTH;
            int start_y = rand() % SCREEN_HEIGHT;
            while (map[start_y][start_x] != 0) {
                start_x = rand() % SCREEN_WIDTH;
                start_y = rand() % SCREEN_HEIGHT;
            }
            int q[SCREEN_HEIGHT * SCREEN_WIDTH][2] = {0};
            q[0][0] = start_x;
            q[0][1] = start_y;
            int index = 0, last = 0;
            double chance = 100.00;
            map[start_y][start_x] = i;
            while (index <= last) {
                int current_x = q[index][0];
                int current_y = q[index][1];
                index++;
                if (rand() % 100 < (int) chance) {
                    if (current_x + 1 < SCREEN_WIDTH && map[current_y][current_x + 1] == 0) {
                        last++;
                        q[last][0] = current_x + 1;
                        q[last][1] = current_y;
                        map[current_y][current_x + 1] = i;
                    }
                    if (current_x - 1 >= 0 && map[current_y][current_x - 1] == 0) {
                        last++;
                        q[last][0] = current_x - 1;
                        q[last][1] = current_y;
                        map[current_y][current_x - 1] = i;
                    }
                    if (current_y + 1 < SCREEN_HEIGHT && map[current_y + 1][current_x] == 0) {
                        last++;
                        q[last][0] = current_x;
                        q[last][1] = current_y + 1;
                        map[current_y + 1][current_x] = i;
                    }
                    if (current_y - 1 >= 0 && map[current_y - 1][current_x] == 0) {
                        last++;
                        q[last][0] = current_x;
                        q[last][1] = current_y - 1;
                        map[current_y - 1][current_x] = i;
                    }
                }
                chance = chance * 0.99995;
            }
            add_border_game_map(map);
        }
    }

}
void draw_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH]){
    for(int i=0;i<SCREEN_HEIGHT;i++){
        for(int j=0;j<SCREEN_WIDTH;j++){
            if(map[i][j]==1)pixelRGBA(renderer,j,i,0xff,0x00,0x00,0xff);
            if(map[i][j]==2)pixelRGBA(renderer,j,i,0x00,0xff,0x00,0xff);
            if(map[i][j]==3)pixelRGBA(renderer,j,i,0x00,0x00,0xff,0xff);
            if(map[i][j]==4)pixelRGBA(renderer,j,i,0xff,0xfd,0xd0,0xff);
            if(map[i][j]==-1)pixelRGBA(renderer,j,i,0x00,0x00,0x00,0xff);
        }
    }
}
void main_game_map(){
    init_game_map();
    srand(time(NULL));

    int map[SCREEN_HEIGHT][SCREEN_WIDTH]={0};
    create_random_map_game_map(map,4,6);


    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        draw_map_game_map(map);

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;

            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }


    kill_game_map();


}