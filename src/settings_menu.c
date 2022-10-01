#include "../inc/header.h"

void settings_menu(SDL_Renderer* renderer) {
	SDL_Event event;
	bool running = true;
	static bool sound_turned_on = true;
	static int sound_level = 16;
	int aimed_button;
	SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/backgrounds/backgr.png");
	SDL_Texture* back_button = IMG_LoadTexture(renderer, "./resource/buttons/Large Buttons/Back Button.png");
	SDL_Texture* sound_off = IMG_LoadTexture(renderer, "./resource/buttons/Large Buttons/MusicOFF Square Button.png");
	SDL_Texture* sound_on = IMG_LoadTexture(renderer, "./resource/buttons/Large Buttons/Music Square Button.png");
	SDL_Texture* decrease_sound_button = IMG_LoadTexture(renderer, "./resource/buttons/decrease_volume_button.png");
	SDL_Texture* increase_sound_button = IMG_LoadTexture(renderer, "./resource/buttons/increase_volume_button.png");
	SDL_Texture* current_sound_button;

	SDL_Rect back_rect = { BACK_X + 30, BACK_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y };
	SDL_Rect sound_rect = { SOUND_SHIFT_X + 88, SOUND_SHIFT_Y, BUTTON_SIZE_X - 120, BUTTON_SIZE_Y};
	SDL_Rect decrease_rect = { DECREASE_VOLUME_X + 30, DECREASE_VOLUME_Y, DECREASE_VOLUME_SIZE_X, BUTTON_SIZE_Y };
	SDL_Rect increase_rect = { INCREASE_VOLUME_X - 30, INCREASE_VOLUME_Y, INCREASE_VOLUME_SIZE_X, BUTTON_SIZE_Y };

	if (sound_turned_on)
        current_sound_button = sound_on;
	else 
		current_sound_button = sound_off;


	while (running) {
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, back_button, NULL, &back_rect);
		SDL_RenderCopy(renderer, current_sound_button, NULL, &sound_rect);
		SDL_RenderCopy(renderer, decrease_sound_button, NULL, &decrease_rect);
		SDL_RenderCopy(renderer, increase_sound_button, NULL, &increase_rect);
		while (SDL_PollEvent(&event)) {
			aimed_button = get_aimed_button(event.button.x, event.button.y);
			switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT && aimed_button != -1)
				{
					switch (aimed_button)
					{
					case BACK_BUTTON:
						Mix_PlayChannel(-1, CLICK, 0);
						SDL_SetTextureColorMod(back_button, 300, 300, 300);
						SDL_RenderCopy(renderer, back_button, NULL, &back_rect);
						SDL_RenderPresent(renderer);
						SDL_Delay(250);
						running = false;
						break;

					case SOUND_SHIFT_BUTTON:
						Mix_PlayChannel(-1, CLICK, 0);
						if (sound_turned_on) {
							sound_turned_on = false;
							current_sound_button = sound_off;
							Mix_PauseMusic();
						}
						else {
							sound_turned_on = true;
							current_sound_button = sound_on;
							Mix_ResumeMusic();
						}
						SDL_SetTextureColorMod(current_sound_button, 300, 300, 300);
						SDL_RenderCopy(renderer, current_sound_button, NULL, &sound_rect);
						SDL_RenderPresent(renderer);
						SDL_Delay(250);
						break;

					case DECREASE_VOLUME_BUTTON:
						Mix_PlayChannel(-1, CLICK, 0);
						if (sound_level - 8 >= 0)
						    sound_level -= 8;
						Mix_VolumeMusic(sound_level);
						break;

					case INCREASE_VOLUME_BUTTON:
						Mix_PlayChannel(-1, CLICK, 0);
						if (sound_level + 8 <= 128)
							sound_level += 8;
						Mix_VolumeMusic(sound_level);
						break;
					}	
					SDL_SetTextureColorMod(back_button, 255, 255, 255);
					SDL_SetTextureColorMod(current_sound_button, 255, 255, 255);
				}
					break;
			}
		}
		SDL_RenderPresent(renderer);
	}
}
