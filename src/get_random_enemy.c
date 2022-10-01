#include "../inc/header.h"
char* get_random_enemy(void) {
    char* enemies[] = { "./resource/level_textures/enemy1.png",
                        "./resource/level_textures/enemy2.png" };

    return enemies[rand() % 2];
}
