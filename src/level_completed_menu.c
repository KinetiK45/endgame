#include "../inc/header.h"

bool level_completed_menu(SDL_Renderer* renderer) {
	SDL_Event event;
	bool to_next_level = false;
	bool running = true;
	int aimed_button;
	SDL_Texture* resume_button = IMG_LoadTexture(renderer, "./resource/buttons/Large Buttons/Continue Button.png");
	SDL_Texture* back_to_menu_button = IMG_LoadTexture(renderer, "./resource/buttons/Large Buttons/Menu Button.png");
	SDL_Texture* background = IMG_LoadTexture(renderer, "./resource/backgrounds/backgrpause.png");
	SDL_Rect resume_rect = { RESUME_X + 30, RESUME_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y };
	SDL_Rect back_to_menu_rect = { BACK_TO_MENU_X + 30, BACK_TO_MENU_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y };

	while (running) {
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, resume_button, NULL, &resume_rect);
		SDL_RenderCopy(renderer, back_to_menu_button, NULL, &back_to_menu_rect);
		while (SDL_PollEvent(&event)) {
			aimed_button = get_paused_aimed_button(event.button.x, event.button.y);
			switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT && aimed_button != -1)
				{
					switch (aimed_button)
					{
					case RESUME_BUTTON:
						Mix_PlayChannel(-1, CLICK, 0);
						SDL_SetTextureColorMod(resume_button, 300, 300, 300);
						SDL_RenderCopy(renderer, resume_button, NULL, &resume_rect);
						SDL_RenderPresent(renderer);
						SDL_Delay(250);
						running = false;
						to_next_level = true;
						break;

					case BACK_TO_MENU_BUTTON:
						Mix_PlayChannel(-1, CLICK, 0);
						SDL_SetTextureColorMod(back_to_menu_button, 300, 300, 300);
						SDL_RenderCopy(renderer, back_to_menu_button, NULL, &back_to_menu_rect);
						SDL_RenderPresent(renderer);
						SDL_Delay(250);
						running = false;
						break;
					}
					SDL_SetTextureColorMod(resume_button, 255, 255, 255);
					SDL_SetTextureColorMod(back_to_menu_button, 255, 255, 255);
				}
				break;
			}
		}
		SDL_RenderPresent(renderer);
	}
	return to_next_level;
}
