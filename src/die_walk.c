#include "../inc/header.h"

void die_walk(SDL_Renderer*renderer, SDL_Rect hero_rect) {
    SDL_Surface* image = IMG_Load("./resource/level_textures/skeleton.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
    SDL_Event event;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    int current_time = SDL_GetTicks() / 1000;
    while (SDL_GetTicks()/1000 < current_time + 2)
    {
        Uint32 ticks = SDL_GetTicks();
        Uint32 sprite = (ticks / 100) % 4;
        SDL_Rect srcrect = { sprite * 32, 0, 32, 64};
        SDL_Rect dstrect = { hero_rect.x, hero_rect.y, 60, 75};

        SDL_PollEvent(&event);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);

}


