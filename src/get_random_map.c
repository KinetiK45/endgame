#include "../inc/header.h"
char* get_random_map(void) {
	char* maps[] = { "./resource/level_textures/map1.png", "./resource/level_textures/map2.png", "./resource/level_textures/map3.png" };
	return maps[rand() % 3];
}
