#include "../inc/header.h"

int main() {

    bool running = true;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_Cursor* cursor;
    SDL_Surface* cursor_image;
    cursor_image = SDL_LoadBMP("./resource/Cursors/cursor_blue_mini.bmp");
    cursor = SDL_CreateColorCursor(cursor_image, 0, 0);
    SDL_SetCursor(cursor);
    srand(time(NULL));
    
    Mix_Music* music = NULL;
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    if (SDL_GetAudioStatus() != SDL_AUDIO_PLAYING) {
        music = Mix_LoadMUS("./resource/music/ost.mp3");
        Mix_VolumeMusic(4);
        Mix_PlayMusic(music, -1);
    }
    SDL_Window* window = SDL_CreateWindow("Bombers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    menu(renderer,running);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    Mix_FreeMusic(music);
    
    SDL_Quit();
    return 0;
}
