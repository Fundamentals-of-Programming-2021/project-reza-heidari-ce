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

struct pawn{
    int current_x,current_y;
    int dest_x,dest_y;
    int source_x,source_y;
    int region_dest,region_source;
    int color;
    int visible_after;
};
struct region{
    int center_x,center_y;
    int pawn_cnt;
    int growth_rate;
    int color;
};
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
    for(int i=0;i<SCREEN_WIDTH;i++){
        map[0][i]=-1;
        map[SCREEN_HEIGHT-1][i]=-1;
    }
    for(int i=0;i<SCREEN_HEIGHT;i++){
        map[i][0]=-1;
        map[i][SCREEN_WIDTH-1]=-1;
    }
}
int place_check_game_map(region *regions,int region_index,int x,int y){
    if(x<50 || x>SCREEN_WIDTH-50)return 0;
    if(y<50 || y>SCREEN_HEIGHT-50)return 0;
    for(int i=0;i<region_index;i++){
        int dist=(regions[i].center_x-x)*(regions[i].center_x-x)+(regions[i].center_y-y)*(regions[i].center_y-y);
        if(dist<5000)return 0;
    }
    return 1;
}
void create_random_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],int cnt,int cnt_each,int initial_pawn_cnt,region *regions){
    int region_index=0;
    for(int j=1;j<=cnt_each;j++) {
        for(int i=1;i<=cnt;i++){
            int start_x = rand() % SCREEN_WIDTH;
            int start_y = rand() % SCREEN_HEIGHT;
            while (map[start_y][start_x] != 0 || place_check_game_map(regions,region_index,start_x,start_y)==0) {
                start_x = rand() % SCREEN_WIDTH;
                start_y = rand() % SCREEN_HEIGHT;
            }
            regions[region_index].center_x=start_x;
            regions[region_index].center_y=start_y;
            regions[region_index].color=i;
            regions[region_index].pawn_cnt=initial_pawn_cnt;
            regions[region_index].growth_rate=1;
            region_index++;

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
void change_region_color_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],int color,int start_x,int start_y){
    int q[SCREEN_HEIGHT * SCREEN_WIDTH][2] = {0};
    q[0][0] = start_x;
    q[0][1] = start_y;
    int index = 0, last = 0;
    map[start_y][start_x] = color;
    while (index <= last) {
        int current_x = q[index][0];
        int current_y = q[index][1];
        index++;
        if (current_x + 1 < SCREEN_WIDTH && map[current_y][current_x + 1] != -1 && map[current_y][current_x + 1] !=color) {
            last++;
            q[last][0] = current_x + 1;
            q[last][1] = current_y;
            map[current_y][current_x + 1] = color;
        }
        if (current_x - 1 >= 0 && map[current_y][current_x - 1] != -1 && map[current_y][current_x - 1] != color) {
            last++;
            q[last][0] = current_x - 1;
            q[last][1] = current_y;
            map[current_y][current_x - 1] = color;
        }
        if (current_y + 1 < SCREEN_HEIGHT && map[current_y + 1][current_x] != -1 && map[current_y + 1][current_x] != color) {
            last++;
            q[last][0] = current_x;
            q[last][1] = current_y + 1;
            map[current_y + 1][current_x] = color;
        }
        if (current_y - 1 >= 0 && map[current_y - 1][current_x] != -1 && map[current_y - 1][current_x] != color) {
            last++;
            q[last][0] = current_x;
            q[last][1] = current_y - 1;
            map[current_y - 1][current_x] = color;
        }
    }
}

void draw_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],region *regions,int cnt_regions){
    for(int i=0;i<SCREEN_HEIGHT;i++){
        for(int j=0;j<SCREEN_WIDTH;j++){
            if(map[i][j]==1)pixelRGBA(renderer,j,i,0xee,0x4b,0x2b,0xff);
            if(map[i][j]==2)pixelRGBA(renderer,j,i,0x22,0xd6,0xc0,0xff);
            if(map[i][j]==3)pixelRGBA(renderer,j,i,0x9b,0xa0,0xdb,0xff);
            if(map[i][j]==4)pixelRGBA(renderer,j,i,0xff,0xfd,0xd0,0xff);
            if(map[i][j]==-1)pixelRGBA(renderer,j,i,0x00,0x00,0x00,0xff);
        }
    }
    for(int i=0;i<cnt_regions;i++){
        /* reminder: add code for artillery color and image */
        char temp_str[5];
        sprintf(temp_str,"%d",regions[i].pawn_cnt);
        stringRGBA(renderer,regions[i].center_x,regions[i].center_y,temp_str,0x00,0x00,0x00,0xff);
    }
}
int move_pawns_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],pawn *moving_pawns,region *regions,int cnt_moving_pawns){
    pawn temp[3000];
    int index=0;

    for(int i=0;i<cnt_moving_pawns;i++){
        if(moving_pawns[i].visible_after>0){
            (moving_pawns[i].visible_after)--;
            temp[index]=moving_pawns[i];
            index++;
        }
        else {
            if(moving_pawns[i].visible_after==0){
                (regions[moving_pawns[i].region_source].pawn_cnt)--;
                moving_pawns[i].visible_after=-1;
            }
            int speed_x,speed_y;
            double slope;
            if(abs(moving_pawns[i].dest_x-moving_pawns[i].source_x)>abs(moving_pawns[i].dest_y-moving_pawns[i].source_y)) {
                speed_x = 3;
                if (moving_pawns[i].dest_x < moving_pawns[i].source_x)speed_x *= -1;
                slope = ((double) (moving_pawns[i].dest_y - moving_pawns[i].source_y)) /
                        ((double) (moving_pawns[i].dest_x - moving_pawns[i].source_x));
                moving_pawns[i].current_x = moving_pawns[i].current_x + speed_x;
                moving_pawns[i].current_y = ((int)(slope * ((double)(moving_pawns[i].current_x-moving_pawns[i].source_x)))) + (moving_pawns[i].source_y);
            }
            else{
                speed_y = 3;
                if (moving_pawns[i].dest_y < moving_pawns[i].source_y)speed_y *= -1;
                slope = ((double) (moving_pawns[i].dest_x - moving_pawns[i].source_x)) /
                        ((double) (moving_pawns[i].dest_y - moving_pawns[i].source_y));
                moving_pawns[i].current_y = moving_pawns[i].current_y + speed_y;
                moving_pawns[i].current_x = ((int)(slope * ((double)(moving_pawns[i].current_y-moving_pawns[i].source_y)))) + (moving_pawns[i].source_x);
            }
            if(abs(moving_pawns[i].current_x-moving_pawns[i].dest_x)<5 && abs(moving_pawns[i].current_y-moving_pawns[i].dest_y)<5){
                if(regions[moving_pawns[i].region_dest].color==moving_pawns[i].color){
                    (regions[moving_pawns[i].region_dest].pawn_cnt)++;
                }
                else{
                    if(regions[moving_pawns[i].region_dest].pawn_cnt != 0){
                        (regions[moving_pawns[i].region_dest].pawn_cnt)--;
                    }
                    else{
                        regions[moving_pawns[i].region_dest].pawn_cnt = 1;
                        regions[moving_pawns[i].region_dest].color=moving_pawns[i].color;
                        change_region_color_game_map(map,moving_pawns[i].color,moving_pawns[i].dest_x,moving_pawns[i].dest_y);
                    }
                }
            }
            else{
                temp[index]=moving_pawns[i];
                index++;
            }
        }
    }
    int circle_radius=5;
    cnt_moving_pawns=0;
    for(int i=0;i<index;i++){
        if(temp[i].current_x==-1)continue;
        for(int j=0;j<index;j++){
            if(j==i || temp[i].color==temp[j].color)continue;
            if(temp[j].current_x==-1)continue;
            int dest=(temp[i].current_x-temp[j].current_x)*(temp[i].current_x-temp[j].current_x);
            dest+=(temp[i].current_y-temp[j].current_y)*(temp[i].current_y-temp[j].current_y);
            if(dest<=2*(circle_radius*circle_radius)){
                temp[i].current_x=-1;
                temp[j].current_x=-1;
                break;
            }
        }
        if(temp[i].current_x!=-1){
            moving_pawns[cnt_moving_pawns]=temp[i];
            cnt_moving_pawns++;
        }
    }

    for(int i=0;i<cnt_moving_pawns;i++){
        if(moving_pawns[i].visible_after>0)continue;
        if(moving_pawns[i].color==1)filledCircleRGBA(renderer,moving_pawns[i].current_x,moving_pawns[i].current_y,circle_radius,0xff,0x00,0x00,0xff);
        if(moving_pawns[i].color==2)filledCircleRGBA(renderer,moving_pawns[i].current_x,moving_pawns[i].current_y,circle_radius,0x00,0xff,0x00,0xff);
        if(moving_pawns[i].color==3)filledCircleRGBA(renderer,moving_pawns[i].current_x,moving_pawns[i].current_y,circle_radius,0x00,0x00,0xff,0xff);
    }
    return cnt_moving_pawns;
}
int get_region_id_game_map(region *regions,int cnt_regions,int x,int y){
    for(int i=0;i<cnt_regions;i++){
        int dist=(regions[i].center_x-x)*(regions[i].center_x-x)+(regions[i].center_y-y)*(regions[i].center_y-y);
        if(dist<400){
            return i;
        }
    }
    return -1;
}
int deploy_game_map(region *regions,pawn *moving_pawns,int cnt_moving_pawns,int selected_source_region,int selected_dest_region){
    for(int i=0;i<regions[selected_source_region].pawn_cnt;i++){
        moving_pawns[cnt_moving_pawns].current_x=regions[selected_source_region].center_x;
        moving_pawns[cnt_moving_pawns].current_y=regions[selected_source_region].center_y;
        moving_pawns[cnt_moving_pawns].dest_x=regions[selected_dest_region].center_x;
        moving_pawns[cnt_moving_pawns].dest_y=regions[selected_dest_region].center_y;
        moving_pawns[cnt_moving_pawns].source_x=regions[selected_source_region].center_x;
        moving_pawns[cnt_moving_pawns].source_y=regions[selected_source_region].center_y;
        moving_pawns[cnt_moving_pawns].region_dest=selected_dest_region;
        moving_pawns[cnt_moving_pawns].region_source=selected_source_region;
        moving_pawns[cnt_moving_pawns].color=regions[selected_source_region].color;
        moving_pawns[cnt_moving_pawns].visible_after=i*4;
        cnt_moving_pawns++;
    }
    return cnt_moving_pawns;
}
void main_game_map(){
    init_game_map();
    srand(time(NULL));

    int map[SCREEN_HEIGHT][SCREEN_WIDTH]={0};
    region regions[20];
    int cnt_regions=4;
    create_random_map_game_map(map,4,1,10,regions);
    pawn moving_pawns[3000];
    int cnt_moving_pawns=0;
    int max_soldiers=50;
    int frame=0;

    int selected_source_region=-1,selected_dest_region=-1;

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        frame=(frame+1)%30;
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        draw_map_game_map(map,regions,cnt_regions);

        if(frame==0){
            for(int i=0;i<cnt_regions;i++){
                if(regions[i].color!=4 && regions[i].pawn_cnt<max_soldiers)(regions[i].pawn_cnt) += regions[i].growth_rate;
            }
        }


        cnt_moving_pawns=move_pawns_game_map(map,moving_pawns,regions,cnt_moving_pawns);

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    selected_source_region=get_region_id_game_map(regions,cnt_regions,sdlEvent.button.x,sdlEvent.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    selected_dest_region = get_region_id_game_map(regions,cnt_regions,sdlEvent.button.x,sdlEvent.button.y);
                    if(selected_source_region==-1 || selected_dest_region==-1 || selected_source_region==selected_dest_region || regions[selected_source_region].color==4){
                        selected_source_region=-1;
                        selected_dest_region=-1;
                    }
                    else{
                        cnt_moving_pawns=deploy_game_map(regions,moving_pawns,cnt_moving_pawns,selected_source_region,selected_dest_region);
                    }
                    break;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }


    kill_game_map();
}