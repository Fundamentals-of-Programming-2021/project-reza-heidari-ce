cmake_minimum_required(VERSION 3.20)
project(project C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(project main.c username_menu.c username_menu.h game_map.c game_map.h main_menu.c main_menu.h leaderboard.c leaderboard.h maps_menu.c maps_menu.h picking_color.c picking_color.h win_loose_menu.c win_loose_menu.h picking_player_count.c picking_player_count.h)

target_link_libraries(project m SDL2 SDL2_gfx SDL2_image SDL2_ttf)
