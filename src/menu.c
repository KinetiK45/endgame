#include "../inc/header.h"

bool menu(SDL_Renderer* renderer, bool running) {
    SDL_Event event;
    //setting up sound of click;
    CLICK = Mix_LoadWAV("./resource/music/sigh_sound.wav");
    CLICK->volume = 24;
    int result_of_level;
    static int level_of_difficulty;
    //initialisation of textures
    SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/backgrounds/backgr.png");
    SDL_Texture* start_button = IMG_LoadTexture(renderer,"./resource/buttons/Large Buttons/Play Button.png");
    SDL_Texture* settings_button = IMG_LoadTexture(renderer,"./resource/buttons/Large Buttons/Settings Button.png");
    SDL_Texture* exit_button = IMG_LoadTexture(renderer,"./resource/buttons/Large Buttons/Exit Button.png");

   
    SDL_Rect start_rect = { START_X, START_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y };
    SDL_Rect settings_rect = { SETTINGS_X, SETTINGS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y };
    SDL_Rect exit_rect = { EXIT_X, EXIT_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y };

    int aimed_button;
    while (running)
    {
        SDL_RenderCopy(renderer, background, NULL, NULL);
  
        SDL_RenderCopy(renderer, start_button, NULL, &start_rect);
        SDL_RenderCopy(renderer, settings_button, NULL, &settings_rect);
        SDL_RenderCopy(renderer, exit_button, NULL, &exit_rect);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            aimed_button = get_aimed_button(event.button.x, event.button.y);
          
            switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && aimed_button != -1) {
                   // Mix_PlayChannel(-1, CLICK, 0); звук клика
                    switch (aimed_button)
                    {
                    case START_BUTTON:
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_SetTextureColorMod(start_button, 300, 300, 300);
                        SDL_RenderCopy(renderer, start_button, NULL, &start_rect);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(250);
                        level_of_difficulty = 1;
                        result_of_level = start_level(renderer, level_of_difficulty);

                        while (result_of_level != -1) {
                            if (result_of_level == 1) {
                                if (!level_completed_menu(renderer)) {
                                    result_of_level = -1;                      
                                }
                                else {                 
                                    level_of_difficulty += 1;
                                    result_of_level = start_level(renderer, level_of_difficulty);
                                }
                            }
                            else if (result_of_level == 0) {
                                if (!end_game_menu(renderer)) {
                                    level_of_difficulty = 1;
                                    result_of_level = start_level(renderer, level_of_difficulty);
                                }
                                else 
                                    result_of_level = -1;
                            }
                        }
                        break;

                    case EXIT_BUTTON:
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_SetTextureColorMod(exit_button, 300, 300, 300);
                        SDL_RenderCopy(renderer, exit_button, NULL, &exit_rect);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                        running = false;
                        //ливаем
                        break;

                    case SETTINGS_BUTTON:
                        Mix_PlayChannel(-1, CLICK, 0);
                        SDL_SetTextureColorMod(settings_button, 300, 300, 300);
                        SDL_RenderCopy(renderer, settings_button, NULL, &settings_rect);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(250);
                        //меню настроек
                        settings_menu(renderer);
                        break;
                    }
                    SDL_SetTextureColorMod(start_button, 255, 255, 255);
                    SDL_SetTextureColorMod(settings_button, 255, 255, 255);
                    SDL_SetTextureColorMod(exit_button, 255, 255, 255);
                    break;
                }

            }
        }
        SDL_RenderPresent(renderer);
    }
    return running;
} 

