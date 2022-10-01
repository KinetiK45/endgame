#include "../inc/header.h"

void win_walk(SDL_Renderer* renderer, SDL_Rect hero_rect, SDL_Texture* current, SDL_Texture* arr[]) {
    SDL_Surface* image;
    int image_width, image_height;

    if (current == arr[0] || current == arr[1]) {
        image = IMG_Load("./resource/level_textures/spritesheet_back.png");
        image_width = 540;
        image_height = 596;
    }
    else if (current == arr[2] || current == arr[3]) {
        image = IMG_Load("./resource/level_textures/spritesheet_front.png");
        image_width = 540;
        image_height = 580;
    }
    else if (current == arr[4] || current == arr[5]) {
        image = IMG_Load("./resource/level_textures/spritesheet_left.png"); 
        image_width = 572;
        image_height = 595;
    }
    else {
        image = IMG_Load("./resource/level_textures/spritesheet_right.png");
        image_width = 572;
        image_height = 595;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Event event;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    int current_time = SDL_GetTicks() / 1000;
    while (SDL_GetTicks() / 1000 < current_time + 2)
    {
        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / 150) % 4;
        SDL_Rect srcrect = { sprite * image_width/2, 0, image_width /2,image_height}; 
        SDL_Rect dstrect = { 825, 250, image_width/2, image_height};

        SDL_PollEvent(&event);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}
