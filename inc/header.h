#ifndef HEADER_H
#define HEADER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_audio.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "SDL2/SDL_mixer.h"
#include "button_coords.h"

Mix_Chunk* CLICK;

char* get_random_image(void);

char* get_random_map(void);

char* get_random_enemy(void);

char* get_box(char* current_map);

bool menu(SDL_Renderer* renderer, bool running);

int get_aimed_button(Sint32 mouse_x, Sint32 mouse_y);

int get_paused_aimed_button(Sint32 mouse_x, Sint32 mouse_y);

void settings_menu(SDL_Renderer* renderer);

bool end_game_menu(SDL_Renderer* renderer);

bool level_completed_menu(SDL_Renderer *renderer);

int start_level(SDL_Renderer* renderer, int level_of_difficulty);

void die_walk(SDL_Renderer* renderer, SDL_Rect hero_rect);

void win_walk(SDL_Renderer* renderer, SDL_Rect hero_rect,SDL_Texture* current, SDL_Texture* arr[]);

bool pause_menu(SDL_Renderer* renderer);

int getXcoord(int x_index);

int getYcoord(int y_index);

int getXindex(int x_coord);

int getYindex(int y_coord);

typedef struct s_bomb {
    int timer;
    int x;
    int y;
}   t_bomb;

typedef struct s_list {
    t_bomb bomb;
    struct s_list* next;
}   t_list;

typedef struct s_enemy {
    SDL_Rect enemy_rect;
    int way;
    int speed;
}   t_enemy;

typedef struct s_player {
    SDL_Rect player_rect;
    int speed;
    int count_of_bombs;
    int bomb_r;
}   t_player;

typedef struct s_list_enemies {
    t_enemy enemy;
    struct s_list_enemies* next;
}   t_list_enemies;


void calculate_enemy_step(t_enemy* enemy, int data[17][13]);

t_list* mx_create_node(t_bomb bomb);
int mx_list_size(t_list* list);
void mx_pop_front(t_list** list);
void mx_clear_list(t_list** list);
void mx_push_back(t_list** list, t_bomb bomb);

t_list_enemies* mx_create_node_enemy(t_enemy enemy);
int mx_list_size_enemy(t_list_enemies* list);
void mx_pop_front_enemy(t_list_enemies** list);
void mx_clear_list_enemy(t_list_enemies** list);
void mx_push_back_enemy(t_list_enemies** list, t_enemy enemy);

#endif
