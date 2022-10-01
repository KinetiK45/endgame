#include "../inc/header.h"
char* get_box(char* current_map) {
    if (current_map == "./resource/level_textures/map1.png")
    {
        return  "./resource/level_textures/box.png";
    }
    else if (current_map == "./resource/level_textures/map2.png")
    {
        return  "./resource/level_textures/box2.png";
    }
    else
        return  "./resource/level_textures/box3.png";
}
