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


enum{SCREEN_WIDTH = 800};
enum{SCREEN_HEIGHT = 600};
static const int FPS = 60;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture *potion1_texture;
static SDL_Texture *potion2_texture;
static SDL_Texture *potion3_texture;
static SDL_Texture *potion4_texture;
static SDL_Texture *barracks_red_texture,*barracks_green_texture,*barracks_blue_texture,*barracks_neutral_texture,*barracks_yellow_texture;

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
    int show_pawn_cnt;
    int growth_rate;
    int color;
};
struct potion{
    int potion_type;
    int x,y;
    int time_remaining;
};
void init_game_map() {
    window = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT+150, SDL_WINDOW_OPENGL);

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
        if(dist<10000)return 0;
    }
    return 1;
}
void create_random_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],int cnt,int cnt_each,int cnt_neutral,int initial_pawn_cnt,region *regions){
    int region_index=0;
    for(int j=1;j<=cnt_each || j<=cnt_neutral;j++) {
        for(int i=1;i<=cnt;i++){
            if(i==cnt && cnt==3)i++;
            if(i==4 && j>cnt_neutral)continue;
            if(i!=4 && j>cnt_each)continue;
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
            regions[region_index].show_pawn_cnt=initial_pawn_cnt;
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

void draw_map_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],region *regions,int cnt_regions,TTF_Font* font){
    for(int i=0;i<SCREEN_HEIGHT;i++){
        for(int j=0;j<SCREEN_WIDTH;j++){
            //red
            if(map[i][j]==1)pixelRGBA(renderer,j,i,0xff,0x55,0x55,0xff);
            //green
            if(map[i][j]==2)pixelRGBA(renderer,j,i,0x00,0xa0,0x00,0xff);
            //blue
            if(map[i][j]==3)pixelRGBA(renderer,j,i,0xad,0x77,0xff,0xff);
            //yellow
            if(map[i][j]==5)pixelRGBA(renderer,j,i,0xf0,0xff,0x55,0xff);


            //neutral
            if(map[i][j]==4)pixelRGBA(renderer,j,i,0xff,0xfd,0xd0,0xff);
            //black border
            if(map[i][j]==-1)pixelRGBA(renderer,j,i,0x00,0x00,0x00,0xff);
        }
    }
    SDL_Color color_button = { 0x00, 0x00, 0x00 };
    SDL_Rect barracks_texture_rect = {.x=200, .y=200, .w=40, .h=50};
    for(int i=0;i<cnt_regions;i++){
        // reminder: add code for artillery color and image

        barracks_texture_rect.x=regions[i].center_x-barracks_texture_rect.w/2+8;
        barracks_texture_rect.y=regions[i].center_y-barracks_texture_rect.h/2;
        if(regions[i].color==1)SDL_RenderCopy(renderer,barracks_red_texture,NULL,&barracks_texture_rect);
        if(regions[i].color==2)SDL_RenderCopy(renderer,barracks_green_texture,NULL,&barracks_texture_rect);
        if(regions[i].color==3)SDL_RenderCopy(renderer,barracks_blue_texture,NULL,&barracks_texture_rect);
        if(regions[i].color==4)SDL_RenderCopy(renderer,barracks_neutral_texture,NULL,&barracks_texture_rect);
        if(regions[i].color==5)SDL_RenderCopy(renderer,barracks_yellow_texture,NULL,&barracks_texture_rect);

         //
        char temp_str[5];
        sprintf(temp_str,"%d",regions[i].show_pawn_cnt);
       // printf("%d %s\n",regions[i].pawn_cnt,temp_str);
        //stringRGBA(renderer,regions[i].center_x,regions[i].center_y,temp_str,0x00,0x00,0x00,0xff);
        show_text_game_map( temp_str,color_button,font,regions[i].center_x,regions[i].center_y);
    }
}
int move_pawns_game_map(int map[SCREEN_HEIGHT][SCREEN_WIDTH],pawn *moving_pawns,region *regions,int cnt_moving_pawns,int color_potions[10][10]){
    pawn temp[3000];
    int index=0;

    for(int i=0;i<cnt_moving_pawns;i++){
        int flag=0;
        for(int j=0;j<10;j++){
            if(color_potions[j][2]!=0 && moving_pawns[i].color!=j){
                flag=1;
                break;
            }
        }
        if(flag){
            temp[index]=moving_pawns[i];
            index++;
            continue;
        }

        if(moving_pawns[i].visible_after>0){
            (moving_pawns[i].visible_after)--;
            temp[index]=moving_pawns[i];
            index++;
        }
        else {
            if(moving_pawns[i].visible_after==0){
                if(regions[moving_pawns[i].region_source].show_pawn_cnt>0)(regions[moving_pawns[i].region_source].show_pawn_cnt)--;
                moving_pawns[i].visible_after=-1;
            }
            int speed_x,speed_y;
            double slope;
            if(abs(moving_pawns[i].dest_x-moving_pawns[i].source_x)>abs(moving_pawns[i].dest_y-moving_pawns[i].source_y)) {
                speed_x = 2;
                if(color_potions[moving_pawns[i].color][1]!=0)speed_x*=2;
                if (moving_pawns[i].dest_x < moving_pawns[i].source_x)speed_x *= -1;
                slope = ((double) (moving_pawns[i].dest_y - moving_pawns[i].source_y)) /
                        ((double) (moving_pawns[i].dest_x - moving_pawns[i].source_x));
                moving_pawns[i].current_x = moving_pawns[i].current_x + speed_x;
                moving_pawns[i].current_y = ((int)(slope * ((double)(moving_pawns[i].current_x-moving_pawns[i].source_x)))) + (moving_pawns[i].source_y);
            }
            else{
                speed_y = 2;
                if(color_potions[moving_pawns[i].color][1]!=0)speed_y*=2;
                if (moving_pawns[i].dest_y < moving_pawns[i].source_y)speed_y *= -1;
                slope = ((double) (moving_pawns[i].dest_x - moving_pawns[i].source_x)) /
                        ((double) (moving_pawns[i].dest_y - moving_pawns[i].source_y));
                moving_pawns[i].current_y = moving_pawns[i].current_y + speed_y;
                moving_pawns[i].current_x = ((int)(slope * ((double)(moving_pawns[i].current_y-moving_pawns[i].source_y)))) + (moving_pawns[i].source_x);
            }
            if(abs(moving_pawns[i].current_x-moving_pawns[i].dest_x)<5 && abs(moving_pawns[i].current_y-moving_pawns[i].dest_y)<5){
                if(regions[moving_pawns[i].region_dest].color==moving_pawns[i].color){
                    (regions[moving_pawns[i].region_dest].pawn_cnt)++;
                    (regions[moving_pawns[i].region_dest].show_pawn_cnt)++;
                }
                else{
                    if(regions[moving_pawns[i].region_dest].pawn_cnt != 0){
                        (regions[moving_pawns[i].region_dest].pawn_cnt)--;
                        (regions[moving_pawns[i].region_dest].show_pawn_cnt)--;
                    }
                    else{
                        regions[moving_pawns[i].region_dest].pawn_cnt = 1;
                        regions[moving_pawns[i].region_dest].show_pawn_cnt = 1;
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
                if(temp[i].visible_after>=0){
                    if(regions[temp[i].region_source].show_pawn_cnt>0)(regions[temp[i].region_source].show_pawn_cnt)--;
                    temp[i].visible_after=-1;
                }
                if(temp[j].visible_after>=0){
                    if(regions[temp[j].region_source].show_pawn_cnt>0)(regions[temp[j].region_source].show_pawn_cnt)--;
                    temp[j].visible_after=-1;
                }
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
        if(moving_pawns[i].color==2)filledCircleRGBA(renderer,moving_pawns[i].current_x,moving_pawns[i].current_y,circle_radius,0x00,0x6b,0x00,0xff);
        if(moving_pawns[i].color==3)filledCircleRGBA(renderer,moving_pawns[i].current_x,moving_pawns[i].current_y,circle_radius,0x00,0x00,0xff,0xff);
        if(moving_pawns[i].color==5)filledCircleRGBA(renderer,moving_pawns[i].current_x,moving_pawns[i].current_y,circle_radius,0x88,0xff,0x00,0xff);

    }
    return cnt_moving_pawns;
}
int get_region_id_game_map(region *regions,int cnt_regions,int x,int y){
    for(int i=0;i<cnt_regions;i++){
        int dist=(regions[i].center_x-x)*(regions[i].center_x-x)+(regions[i].center_y-y)*(regions[i].center_y-y);
        if(dist<1000){
            return i;
        }
    }
    return -1;
}
int deploy_game_map(region *regions,pawn *moving_pawns,int cnt_moving_pawns,int selected_source_region,int selected_dest_region,int color_potions[10][10]){
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
        moving_pawns[cnt_moving_pawns].visible_after=i*5;
        cnt_moving_pawns++;
    }
    regions[selected_source_region].pawn_cnt=0;
    return cnt_moving_pawns;
}
int is_reachable_game_map(region *regions,int cnt_regions,int x,int y){
    if(x<50 || x>SCREEN_WIDTH-50)return 0;
    if(y<50 || y>SCREEN_HEIGHT-50)return 0;
    for(int i=0;i<cnt_regions;i++){
        for(int j=0;j<i;j++){
            int dist_region_source=(regions[i].center_x-x)*(regions[i].center_x-x)+(regions[i].center_y-y)*(regions[i].center_y-y);
            int dist_region_dest=(regions[j].center_x-x)*(regions[j].center_x-x)+(regions[j].center_y-y)*(regions[j].center_y-y);
            if(dist_region_source<1500 || dist_region_dest<1500)continue;

            if(regions[i].color==4 && regions[j].color==4)continue;
            if((x>regions[i].center_x && x>regions[j].center_x) || (x<regions[i].center_x && x<regions[j].center_x))continue;
            if((y>regions[i].center_y && y>regions[j].center_y) || (y<regions[i].center_y && y<regions[j].center_y))continue;

            int dist1=(regions[i].center_x-x)*(regions[i].center_x-x)+(regions[i].center_y-y)*(regions[i].center_y-y);
            int dist2=(regions[j].center_x-x)*(regions[j].center_x-x)+(regions[j].center_y-y)*(regions[j].center_y-y);
            int dist=(regions[i].center_x-regions[j].center_x)*(regions[i].center_x-regions[j].center_x)+(regions[i].center_y-regions[j].center_y)*(regions[i].center_y-regions[j].center_y);

            double actual_dist1=sqrt((double)dist1);
            double actual_dist2=sqrt((double)dist2);
            double actual_dist=sqrt((double)dist);
            double dist_difference=actual_dist-(actual_dist1+actual_dist2);

            if(dist_difference<0)dist_difference = dist_difference * (-1.0);
            if(dist_difference<1.0)return 1;
        }
    }
    return 0;

}
void random_potion_coordinate_game_map(region *regions,int cnt_regions,potion *potions,int cnt_potions,int *x,int *y){
    *x=0;
    *y=0;
    int flag=1;
    while(flag || !is_reachable_game_map(regions,cnt_regions,*x,*y)){
        *x=rand()%SCREEN_WIDTH;
        *y=rand()%SCREEN_HEIGHT;
        flag=0;
        for(int i=0;i<cnt_potions;i++){
            int dist=(potions[i].x-*x)*(potions[i].x-*x)+(potions[i].y-*y)*(potions[i].y-*y);
            if(dist<50000){
                flag=1;
                break;
            }
        }
    }
}
int process_potions_game_map(region *regions,int cnt_regions,pawn *moving_pawns,int cnt_moving_pawns,potion *potions,int cnt_potions,int color_potions[10][10],SDL_Rect potion_texture_rect){
    potion temp[20];
    int index=0;
    for(int i=0;i<cnt_potions;i++){

        int flag=0;
        for(int j=0;j<cnt_moving_pawns;j++){
            int dist=(moving_pawns[j].current_x-potions[i].x)*(moving_pawns[j].current_x-potions[i].x);
            dist+=(moving_pawns[j].current_y-potions[i].y)*(moving_pawns[j].current_y-potions[i].y);
            if(dist<1000){
                int already_has_potion=0;
                for(int u=0;u<10;u++){
                    if(color_potions[moving_pawns[j].color][u]!=0) {
                        already_has_potion=1;
                        break;
                    }
                }
                if(already_has_potion)continue;
                flag=1;
                color_potions[moving_pawns[j].color][potions[i].potion_type]=300;
                break;
            }
        }
        if(flag)continue;

        (potions[i].time_remaining)--;
        if(potions[i].time_remaining!=0){
            temp[index]=potions[i];
            index++;
        }
    }
    for(int i=0;i<index;i++)potions[i]=temp[i];
    cnt_potions=index;
    int time_potion_shown=300;
    int max_potions_shown=2;
    if(cnt_potions<max_potions_shown && rand()%100==0){
        int x,y;
        random_potion_coordinate_game_map(regions,cnt_regions,potions,cnt_potions,&x,&y);
        potions[cnt_potions].x=x;
        potions[cnt_potions].y=y;
        potions[cnt_potions].time_remaining=time_potion_shown;
        potions[cnt_potions].potion_type=rand()%4+1;
        cnt_potions++;
    }
    for(int i=0;i<cnt_potions;i++){
        potion_texture_rect.x=potions[i].x-(potion_texture_rect.w / 2);
        potion_texture_rect.y=potions[i].y-(potion_texture_rect.h / 2);
        if(potions[i].potion_type==1)SDL_RenderCopy(renderer,potion1_texture,NULL,&potion_texture_rect);
        else if(potions[i].potion_type==2)SDL_RenderCopy(renderer,potion2_texture,NULL,&potion_texture_rect);
        else if(potions[i].potion_type==3)SDL_RenderCopy(renderer,potion3_texture,NULL,&potion_texture_rect);
        else if(potions[i].potion_type==4)SDL_RenderCopy(renderer,potion4_texture,NULL,&potion_texture_rect);
    }
    return cnt_potions;
}
int is_in_rectangle_game_map(int x1,int y1,int x2,int y2,int x,int y){
    if(x<x2 && x>x1 && y<y2 && y>y1)return 1;
    return 0;
}
void show_text_game_map(char *str_text,SDL_Color color,TTF_Font* font,int x,int y){
    SDL_Surface* text = TTF_RenderText_Solid( font, str_text, color );
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface( renderer, text );
    SDL_Rect dest = { x,y, text->w, text->h };
    SDL_RenderCopy( renderer, text_texture,NULL, &dest );
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_texture);
}
int opponents_game_map(region *regions,int cnt_regions,pawn *moving_pawns,int cnt_moving_pawns,int players_color,int color_potions[10][10]){
    for(int i=0;i<cnt_regions;i++){
        if(regions[i].color==4 || regions[i].color==players_color)continue;
        int id=-1;
        int max_pawn=-100;
        for(int j=0;j<cnt_regions;j++){
            if(j==i || regions[i].color==regions[j].color)continue;
            if(regions[i].pawn_cnt-regions[j].pawn_cnt-5>max_pawn){
                id=j;
                max_pawn=regions[i].pawn_cnt-regions[j].pawn_cnt;
            }
        }
        if(max_pawn>5){
            cnt_moving_pawns=deploy_game_map(regions,moving_pawns,cnt_moving_pawns,i,id,color_potions);
            break;
        }
    }
    return cnt_moving_pawns;
}
void draw_potion_bar_game_map(int color_potions[10][10],SDL_Rect potion_texture_rect,int current_color){
    for(int i=1;i<=4;i++){
        if(color_potions[current_color][i]!=0){
            if(current_color==1) {
                potion_texture_rect.x = 200;
                potion_texture_rect.y = 610;
            }
            if(current_color==2) {
                potion_texture_rect.x = 400;
                potion_texture_rect.y = 610;
            }
            if(current_color==3) {
                potion_texture_rect.x = 200;
                potion_texture_rect.y = 680;
            }
            if(current_color==5) {
                potion_texture_rect.x = 400;
                potion_texture_rect.y = 680;
            }
            if(i==1)SDL_RenderCopy(renderer,potion1_texture,NULL,&potion_texture_rect);
            if(i==2)SDL_RenderCopy(renderer,potion2_texture,NULL,&potion_texture_rect);
            if(i==3)SDL_RenderCopy(renderer,potion3_texture,NULL,&potion_texture_rect);
            if(i==4)SDL_RenderCopy(renderer,potion4_texture,NULL,&potion_texture_rect);

            if(current_color==1)boxRGBA(renderer,10+potion_texture_rect.x+potion_texture_rect.w,potion_texture_rect.y+10,10+potion_texture_rect.x+potion_texture_rect.w+color_potions[current_color][i]/3,potion_texture_rect.y-10+potion_texture_rect.h,0xff,0x55,0x55,0xff);
            if(current_color==2)boxRGBA(renderer,10+potion_texture_rect.x+potion_texture_rect.w,potion_texture_rect.y+10,10+potion_texture_rect.x+potion_texture_rect.w+color_potions[current_color][i]/3,potion_texture_rect.y-10+potion_texture_rect.h,0x00,0xa0,0x00,0xff);
            if(current_color==3)boxRGBA(renderer,10+potion_texture_rect.x+potion_texture_rect.w,potion_texture_rect.y+10,10+potion_texture_rect.x+potion_texture_rect.w+color_potions[current_color][i]/3,potion_texture_rect.y-10+potion_texture_rect.h,0xad,0x77,0xff,0xff);
            if(current_color==5)boxRGBA(renderer,10+potion_texture_rect.x+potion_texture_rect.w,potion_texture_rect.y+10,10+potion_texture_rect.x+potion_texture_rect.w+color_potions[current_color][i]/3,potion_texture_rect.y-10+potion_texture_rect.h,0xf0,0xff,0x55,0xff);

        }
    }
}
int main_game_map(int map_number,int players_color,int number_of_players){
    init_game_map();
    if(map_number==4)srand(time(NULL));
    else srand(1000*map_number);
    int map[SCREEN_HEIGHT][SCREEN_WIDTH]={0};
    region regions[20];
    TTF_Font* font1 = TTF_OpenFont("../Lato-Black.ttf", 24);
    TTF_Font* font2 = TTF_OpenFont("../Lato-Black.ttf", 14);
    //
    int cnt_colors=number_of_players;
    if(map_number==5)cnt_colors=4;
    int cnt_each=2;
    int cnt_neutral=10;
    int cnt_regions=cnt_colors*cnt_each+cnt_neutral;
    int initial_pawn_cnt=10;
    int max_pawns=50;
    //
    if(map_number==5){
        create_random_map_game_map(map,cnt_colors+1,cnt_each,cnt_neutral,initial_pawn_cnt,regions);
        for(int i=0;i<cnt_regions-1;i++){
            change_region_color_game_map(map,players_color,regions[i].center_x,regions[i].center_y);
            regions[i].color=players_color;
        }
        if(players_color==1){
            regions[cnt_regions-1].color=2;
            change_region_color_game_map(map,2,regions[cnt_regions-1].center_x,regions[cnt_regions-1].center_y);
        }
        if(players_color==2){
            regions[cnt_regions-1].color=1;
            change_region_color_game_map(map,1,regions[cnt_regions-1].center_x,regions[cnt_regions-1].center_y);
        }
    }
    else create_random_map_game_map(map,cnt_colors+1,cnt_each,cnt_neutral,initial_pawn_cnt,regions);

    srand(time(NULL));
    SDL_Color color_button = { 0xB2, 0x10, 0x10 };
    pawn moving_pawns[10000];
    int cnt_moving_pawns=0;
    int frame=0;
    int selected_source_region=-1,selected_dest_region=-1;
    potion potions[20];
    int cnt_potions=0;
    int color_potions[10][10]={0};

    potion1_texture= IMG_LoadTexture(renderer,"../potion_1.png");
    potion2_texture= IMG_LoadTexture(renderer,"../potion_2.png");
    potion3_texture= IMG_LoadTexture(renderer,"../potion_3.png");
    potion4_texture= IMG_LoadTexture(renderer,"../potion_4.png");
    barracks_red_texture= IMG_LoadTexture(renderer,"../red_barracks.png");
    barracks_green_texture= IMG_LoadTexture(renderer,"../green_barracks.png");
    barracks_blue_texture= IMG_LoadTexture(renderer,"../blue_barracks.png");
    barracks_neutral_texture= IMG_LoadTexture(renderer,"../neutral_barracks.png");
    barracks_yellow_texture= IMG_LoadTexture(renderer,"../yellow_barracks.png");


    SDL_Rect potion_texture_rect = {.x=200, .y=200, .w=40, .h=50};


    int points=-1;

    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        frame=(frame+1)%30;
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                if(color_potions[i][j]>0)color_potions[i][j]--;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        draw_map_game_map(map,regions,cnt_regions,font2);

        if(frame==0){
            for(int i=0;i<cnt_regions;i++){
                if(regions[i].color!=4 ){
                    if(color_potions[regions[i].color][3]!=0 || regions[i].pawn_cnt<max_pawns){
                        (regions[i].pawn_cnt) += regions[i].growth_rate;
                        (regions[i].show_pawn_cnt) += regions[i].growth_rate;
                    }
                    if(color_potions[regions[i].color][4]!=0 && regions[i].pawn_cnt<max_pawns){
                        (regions[i].pawn_cnt) += regions[i].growth_rate;
                        (regions[i].show_pawn_cnt) += regions[i].growth_rate;
                    }
                }
             /*   if(regions[i].color==4 && regions[i].pawn_cnt<initial_pawn_cnt){
                    (regions[i].pawn_cnt) += regions[i].growth_rate;
                    (regions[i].show_pawn_cnt) += regions[i].growth_rate;
                }*/
            }
        }

        cnt_moving_pawns=move_pawns_game_map(map,moving_pawns,regions,cnt_moving_pawns,color_potions);

        cnt_potions=process_potions_game_map(regions,cnt_regions,moving_pawns,cnt_moving_pawns,potions,cnt_potions,color_potions,potion_texture_rect);

        int finished=1;
        for(int i=0;i<cnt_regions;i++){
            if(regions[i].color==players_color)finished=0;
        }
        int finished2=1;
        for(int i=0;i<cnt_regions;i++){
            if(regions[i].color!=players_color && regions[i].color!=4)finished2=0;
        }
        if(finished || finished2){
            int index=0;
            while(regions[index].color==4)index++;
            if(regions[index].color==players_color)points=15;
            else{
                int cnt_different_colors=0;
                int flag1=0,flag2=0,flag3=0,flag5=0;
                for(int i=0;i<cnt_regions;i++){
                    if(regions[i].color==1 && flag1==0){
                        flag1=1;
                        cnt_different_colors++;
                    }
                    if(regions[i].color==2 && flag2==0){
                        flag2=1;
                        cnt_different_colors++;
                    }
                    if(regions[i].color==3 && flag3==0){
                        flag3=1;
                        cnt_different_colors++;
                    }
                    if(regions[i].color==5 && flag5==0){
                        flag5=1;
                        cnt_different_colors++;
                    }
                }
                points=(10*cnt_different_colors)/cnt_colors;
            }
            shallExit=true;
        }


        for(int i=1;i<=5;i++){
            if(i!=4)draw_potion_bar_game_map(color_potions,potion_texture_rect,i);
        }




        roundedBoxRGBA(renderer,10,650,150,700,10,0x2b,0xde,0xc9,0xa9);
        show_text_game_map("main menu",color_button,font1,20,660);

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
                    if(is_in_rectangle_game_map(10,650,150,700,sdlEvent.button.x,sdlEvent.button.y)){
                        points=-2;
                        shallExit = SDL_TRUE;
                    }
                    selected_dest_region = get_region_id_game_map(regions,cnt_regions,sdlEvent.button.x,sdlEvent.button.y);
                    if(selected_source_region==-1 || selected_dest_region==-1 || selected_source_region==selected_dest_region || regions[selected_source_region].color!=players_color){
                        selected_source_region=-1;
                        selected_dest_region=-1;
                    }
                    else{
                        cnt_moving_pawns=deploy_game_map(regions,moving_pawns,cnt_moving_pawns,selected_source_region,selected_dest_region,color_potions);
                    }
                    break;
            }
        }
        if(frame==0 && rand()%2==0)cnt_moving_pawns= opponents_game_map(regions,cnt_regions,moving_pawns,cnt_moving_pawns,players_color,color_potions);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    TTF_CloseFont( font1 );
    TTF_CloseFont(font2);
    SDL_DestroyTexture(potion1_texture);
    SDL_DestroyTexture(potion2_texture);
    SDL_DestroyTexture(potion3_texture);
    SDL_DestroyTexture(potion4_texture);
    SDL_DestroyTexture(barracks_red_texture);
    SDL_DestroyTexture(barracks_blue_texture);
    SDL_DestroyTexture(barracks_green_texture);
    SDL_DestroyTexture(barracks_neutral_texture);
    SDL_DestroyTexture(barracks_yellow_texture);
    kill_game_map();
    return points;

    //return winner;
}