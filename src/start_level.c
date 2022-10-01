#include "../inc/header.h"

int getXcoord(int x_index) {
	return FIRST_X + 73 * x_index;
}

int getYcoord(int y_index) {
	return FIRST_Y + 73 * y_index;
}

int getXindex(int x_coord) {
	return (x_coord - FIRST_X) / 73;
}

int getYindex(int y_coord) {
	return (y_coord - FIRST_Y) / 73;
}

void add_booster(int boost, t_player* player) {
	if (boost == 1)
	{
		player->speed++;
	}
	if (boost == 2)
	{
		player->count_of_bombs++;
	}
	if (boost == 3)
	{
		player->bomb_r++;
	}
}

bool isEnemyKill(SDL_Rect hero_rect, t_enemy enemy) {
	int heroX = hero_rect.x + hero_rect.w / 2;
	int heroY = hero_rect.y + hero_rect.h - hero_rect.h / 5;
	int enemyXmin = enemy.enemy_rect.x;
	int enemyXmax = enemy.enemy_rect.x + enemy.enemy_rect.w;
	int enemyYmin = enemy.enemy_rect.y;
	int enemyYmax = enemy.enemy_rect.y + enemy.enemy_rect.h;

	if (heroX >= enemyXmin && heroX <= enemyXmax && heroY >= enemyYmin && heroY <= enemyYmax)
	{
		return true;
	}
	return false;
}

void detonate_bomb(const int x, const int y, int r, int data[17][13], int* count_of_bomb, int boosters[17][13], int booster_chance) {
	int temp_x = -1, temp_y = -1, temp_r = -1;
	data[x][y] = 4;
	*count_of_bomb += 1;
	for (int i = 1; i <= r && x - i >= 0; i++)
	{
		if (data[x - i][y] == 1)
		{
			if (rand() % 100 < booster_chance)
			{
				boosters[x - i][y] = 1 + rand() % 3;
			}
			data[x - i][y] = 4;
			break;
		}
		else if (data[x - i][y] == 0)
		{
			data[x - i][y] = 4;
		}
		else if (data[x - i][y] == -1)
		{
			break;
		}
		else if (data[x - i][y] == 3)
		{
			temp_x = x - i;
			temp_y = y;
			temp_r = r;
		}
	}
	for (int i = 1; i <= r && x + i < 17; i++)
	{
		if (data[x + i][y] == 1)
		{
			if (rand() % 100 < booster_chance)
			{
				boosters[x + i][y] = 1 + rand() % 3;
			}
			data[x + i][y] = 4;
			break;
		}
		else if (data[x + i][y] == 0)
		{
			data[x + i][y] = 4;
		}
		else if (data[x + i][y] == -1)
		{
			break;
		}
		else if (data[x + i][y] == 3)
		{
			temp_x = x + i;
			temp_y = y;
			temp_r = r;
		}
	}
	for (int i = 1; i <= r && y - i >= 0; i++)
	{
		if (data[x][y - i] == 1)
		{
			if (rand() % 100 < booster_chance)
			{
				boosters[x][y - i] = 1 + rand() % 3;
			}
			data[x][y - i] = 4;
			break;
		}
		else if (data[x][y - i] == 0)
		{
			data[x][y - i] = 4;
		}
		else if (data[x][y - i] == -1)
		{
			break;
		}
		else if (data[x][y - i] == 3)
		{
			temp_x = x;
			temp_y = y - i;
			temp_r = r;
		}
	}
	for (int i = 1; i <= r && y + i < 13; i++)
	{
		if (data[x][y + i] == 1)
		{
			if (rand() % 100 < booster_chance)
			{
				boosters[x][y + i] = 1 + rand() % 3;
			}
			data[x][y + i] = 4;
			break;
		}
		else if (data[x][y + i] == 0)
		{
			data[x][y + i] = 4;
		}
		else if (data[x][y + i] == -1)
		{
			break;
		}
		else if (data[x][y + i] == 3)
		{
			temp_x = x;
			temp_y = y + i;
			temp_r = r;
		}
	}

	if (temp_x != -1)
	{
		detonate_bomb(temp_x, temp_y, temp_r, *data, count_of_bomb, *boosters, booster_chance);
	}
}

int start_level(SDL_Renderer* renderer, int level_of_difficulty) {
	SDL_Event event;
	int game_status;
	long sdl_current_time = 0;
	bool running = true;
	char* current_map = get_random_map();
	SDL_Texture* cur_hero_pos;
	SDL_Texture* game_field = IMG_LoadTexture(renderer, current_map); // random
	SDL_Texture* front1 = IMG_LoadTexture(renderer, "./resource/level_textures/front1.png");
	SDL_Texture* right1 = IMG_LoadTexture(renderer, "./resource/level_textures/right1.png");
	SDL_Texture* left1 = IMG_LoadTexture(renderer, "./resource/level_textures/left1.png");
	SDL_Texture* back1 = IMG_LoadTexture(renderer, "./resource/level_textures/back1.png");
	SDL_Texture* front2 = IMG_LoadTexture(renderer, "./resource/level_textures/front2.png");
	SDL_Texture* right2 = IMG_LoadTexture(renderer, "./resource/level_textures/right2.png");
	SDL_Texture* left2 = IMG_LoadTexture(renderer, "./resource/level_textures/left2.png");
	SDL_Texture* back2 = IMG_LoadTexture(renderer, "./resource/level_textures/back2.png");
	SDL_Texture* box = IMG_LoadTexture(renderer, get_box(current_map)); //random
	SDL_Texture* bomb = IMG_LoadTexture(renderer, "./resource/level_textures/bomb.png");
	SDL_Texture* enemy1 = IMG_LoadTexture(renderer, get_random_enemy());
	SDL_Texture* fire = IMG_LoadTexture(renderer, "./resource/level_textures/explosion.png");
	SDL_Texture* boost_fast = IMG_LoadTexture(renderer, "./resource/level_textures/boost_fast.png");
	SDL_Texture* boost_bomb_plus = IMG_LoadTexture(renderer, "./resource/level_textures/boost_bomb_plus.png");
	SDL_Texture* boost_bomb_r = IMG_LoadTexture(renderer, "./resource/level_textures/boost_bomb_r.png");

	int data_hero_x;
	int data_hero_x_plus_size;
	int data_hero_x_plus_size_plus_speed;
	int data_hero_x_minus_speed;
	int data_hero_y_plus_size_minus_speed;
	int data_hero_y_plus_size_plus_speed;
	int data_hero_y_plus_size;
	int change = 0;
	int data_hero_y_plus_size_4_5_minus_speed;
	int data_hero_y_plus_size_4_5_plus_speed;
	int data_hero_y_plus_size_4_5;
	int data[17][13];
	int boosters[17][13];

	if (level_of_difficulty > 5)
		level_of_difficulty = 5;

	int amount_of_box = 40 - level_of_difficulty * 10;
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 13; j++) {
			if (rand() % 100 < amount_of_box) {
				data[i][j] = 1;
			}
			else {
				data[i][j] = 0;
			}
			boosters[i][j] = 0;
		}
	}
	for (int x = 1; x < 17; x += 2) {
		for (int y = 1; y < 13; y += 2) {
			data[x][y] = -1;
		}
	}
	data[0][0] = 0;
	data[0][1] = 0;
	data[1][0] = 0;
	int booster_chance = 60 - level_of_difficulty * 10;

	cur_hero_pos = front2; ////change
	SDL_Rect boost_rect = { FIRST_X, FIRST_Y, 75, 75 };
	SDL_Rect box_rect = { FIRST_X, FIRST_Y, 75, 75 };
	SDL_Rect enemy1_rect = { FIRST_X, FIRST_Y, 70, 70 };
	SDL_Rect bomb_rect = { FIRST_X, FIRST_Y, 75, 75};
	SDL_Rect fire_rect = { FIRST_X, FIRST_Y, 75, 75 };
	int hero_x_size = 31;
	int hero_y_size = 64;
	SDL_Rect hero_rect = { FIRST_X, FIRST_Y, hero_x_size, hero_y_size };
	t_player player;
	player.speed = 5;
	player.player_rect = hero_rect;
	player.bomb_r = 1;
	player.count_of_bombs = 1;
	t_list_enemies* enemies = NULL; 
	t_list* bombs = NULL;
	int enemies_count = level_of_difficulty + 2; 
	for (int i = 0; i < enemies_count; i++) 
	{
		t_enemy enemy;
		enemy.way = 0;
		enemy.speed = 1 + rand() % 2;
		enemy.enemy_rect = enemy1_rect;

		while (true)
			{
				int temp_x = 1 + rand() % 16;
				int temp_y = 1 + rand() % 12;
				if (data[temp_x][temp_y] == 0)
				{
					enemy.enemy_rect.x = getXcoord(temp_x);
					enemy.enemy_rect.y = getYcoord(temp_y);
					mx_push_back_enemy(&enemies, enemy);
					break;
				}

			}
	}
	int tick = 0;
	int fire_tick = 0;
	int count_bombs = 0;

	while (running) {
		if (fire_tick == 0)
		{
			fire_tick = SDL_GetTicks();
		}
		if (tick == 0)
		{
			tick = SDL_GetTicks();
		}
		SDL_RenderCopy(renderer, game_field, NULL, NULL);
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 13; j++) {
				if (data[i][j] == 1)
				{
					box_rect.x = getXcoord(i);
					box_rect.y = getYcoord(j);
					SDL_RenderCopy(renderer, box, NULL, &box_rect);
				}
				else if (data[i][j] == 3)
				{
					bomb_rect.x = getXcoord(i);
					bomb_rect.y = getYcoord(j);
					SDL_RenderCopy(renderer, bomb, NULL, &bomb_rect);
					SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
				}
				else if (data[i][j] == 4)
				{
					fire_rect.x = getXcoord(i);
					fire_rect.y = getYcoord(j);
					SDL_RenderCopy(renderer, fire, NULL, &fire_rect);
					SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
				}
				if (boosters[i][j] == 1)
				{
					boost_rect.x = getXcoord(i);
					boost_rect.y = getYcoord(j);
					SDL_RenderCopy(renderer, boost_fast, NULL, &boost_rect);
				}
				if (boosters[i][j] == 2)
				{
					boost_rect.x = getXcoord(i);
					boost_rect.y = getYcoord(j);
					SDL_RenderCopy(renderer, boost_bomb_plus, NULL, &boost_rect);
				}
				if (boosters[i][j] == 3)
				{
					boost_rect.x = getXcoord(i);
					boost_rect.y = getYcoord(j);
					SDL_RenderCopy(renderer, boost_bomb_r, NULL, &boost_rect);
				}
			}
		}
		SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
		for (int i = 0; i < mx_list_size_enemy(enemies); i++)
		{
			SDL_RenderCopy(renderer, enemy1, NULL, &enemies[0].enemy.enemy_rect);
			mx_push_back_enemy(&enemies, enemies->enemy);
			mx_pop_front_enemy(&enemies);
		}
		while (SDL_PollEvent(&event))
		{

			if (event.type == SDL_QUIT) {
				running = false;
			}
			
			switch (event.type) {
			case SDL_KEYDOWN:
				data_hero_x = getXindex(player.player_rect.x);
				data_hero_x_plus_size = getXindex(player.player_rect.x + player.player_rect.w);
				data_hero_x_plus_size_plus_speed = getXindex(player.player_rect.x + player.player_rect.w + player.speed);
				data_hero_x_minus_speed = getXindex(player.player_rect.x - player.speed);
				data_hero_y_plus_size_minus_speed = getYindex(player.player_rect.y + player.player_rect.h - player.speed);
				data_hero_y_plus_size_plus_speed = getYindex(player.player_rect.y + hero_y_size + player.speed);
				data_hero_y_plus_size = getYindex(player.player_rect.y + player.player_rect.h);
				data_hero_y_plus_size_4_5_minus_speed = getYindex(player.player_rect.y + player.player_rect.h * 4 / 5 - player.speed);
				data_hero_y_plus_size_4_5_plus_speed = getYindex(player.player_rect.y + player.player_rect.h * 4 / 5 + player.speed);
				data_hero_y_plus_size_4_5 = getYindex(player.player_rect.y + player.player_rect.h * 4 / 5);

				if (event.key.keysym.sym == SDLK_UP) {
					if (data[data_hero_x][data_hero_y_plus_size_4_5_minus_speed] == 0
						&& data[data_hero_x_plus_size][data_hero_y_plus_size_4_5_minus_speed] == 0
						&& player.player_rect.y + player.player_rect.h * 4 / 5 - player.speed > FIRST_Y
						|| data[data_hero_x][data_hero_y_plus_size_4_5_minus_speed] == 3
						&& data[data_hero_x_plus_size][data_hero_y_plus_size_4_5_minus_speed] == 3
						&& data[data_hero_x][data_hero_y_plus_size_4_5] == 3
						&& data[data_hero_x_plus_size][data_hero_y_plus_size_4_5] == 3
						&& player.player_rect.y + player.player_rect.h * 4 / 5 - player.speed > FIRST_Y) {

						player.player_rect.y -= player.speed;

						if (change == 20) {
							change = 0;
						}
						if (change < 10) {
							cur_hero_pos = back1;
							SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
							SDL_RenderPresent(renderer);

							change++;
						}
						else if (change < 20 && change > 9) {
							cur_hero_pos = back2;;
							SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
							SDL_RenderPresent(renderer);

							change++;
						}
					}
				}
				if (event.key.keysym.sym == SDLK_DOWN) {
					if (data[data_hero_x][data_hero_y_plus_size_plus_speed] == 0
						&& data[data_hero_x_plus_size][data_hero_y_plus_size_plus_speed] == 0
						&& player.player_rect.y + hero_y_size + player.speed < FIRST_Y + 73 * 13
						|| data[data_hero_x][data_hero_y_plus_size_plus_speed] == 3
						&& data[data_hero_x][data_hero_y_plus_size] == 3
						&& data[data_hero_x_plus_size][data_hero_y_plus_size] == 3
						&& player.player_rect.y + hero_y_size + 5 < FIRST_Y + 73 * 13) {

						player.player_rect.y += player.speed;

						if (change == 20) {
							change = 0;
						}
						if (change < 10) {
							cur_hero_pos = front1;
							SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
							SDL_RenderPresent(renderer);

							change++;
						}
						else if (change < 20 && change >9) {
							cur_hero_pos = front2;;
							SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
							SDL_RenderPresent(renderer);

							change++;
						}
					}
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					if (data[data_hero_x_plus_size_plus_speed][data_hero_y_plus_size] == 0
						&& data[data_hero_x_plus_size_plus_speed][data_hero_y_plus_size_4_5] == 0
						&& player.player_rect.x + hero_x_size + player.speed < FIRST_X + 73 * 17
						|| data[data_hero_x_plus_size_plus_speed][data_hero_y_plus_size] == 3
						&& data[data_hero_x_plus_size][data_hero_y_plus_size] == 3
						&& data[data_hero_x_plus_size_plus_speed][data_hero_y_plus_size_4_5] == 3
						&& data[data_hero_x_plus_size][data_hero_y_plus_size_4_5] == 3
						&& player.player_rect.x + hero_x_size + player.speed < FIRST_X + 73 * 17) {

						player.player_rect.x += player.speed;

						if (change == 20) {
							change = 0;
						}
						if (change < 10) {
							cur_hero_pos = right1;
							SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
							SDL_RenderPresent(renderer);

							change++;
						}
						else if (change > 9 && change < 20) {
							cur_hero_pos = right2;
							SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
							SDL_RenderPresent(renderer);

							change++;
						}
					}
				}
				if (event.key.keysym.sym == SDLK_LEFT) {
					if (data[data_hero_x_minus_speed][data_hero_y_plus_size] == 0
						&& data[data_hero_x_minus_speed][data_hero_y_plus_size_4_5] == 0
						&& player.player_rect.x - player.speed > FIRST_X
						|| data[data_hero_x_minus_speed][data_hero_y_plus_size] == 3
						&& data[data_hero_x][data_hero_y_plus_size] == 3
						&& data[data_hero_x_minus_speed][data_hero_y_plus_size_4_5] == 3
						&& data[data_hero_x][data_hero_y_plus_size_4_5] == 3
						&& player.player_rect.x - player.speed > FIRST_X) {

						player.player_rect.x -= player.speed;

						if (change == 20) {
							change = 0;
						}
						if (change < 10) {
							cur_hero_pos = left1;
							SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
							SDL_RenderPresent(renderer);

							change++;
						}
						else if (change > 9 && change < 20) {
							cur_hero_pos = left2;
							SDL_RenderCopy(renderer, cur_hero_pos, NULL, &player.player_rect);
							SDL_RenderPresent(renderer);

							change++;
						}
					}
				}
				if (event.key.keysym.sym == SDLK_SPACE) {
					if (data[getXindex(player.player_rect.x + hero_x_size / 2)][getYindex(player.player_rect.y + hero_y_size)] == 0) {
						data[getXindex(player.player_rect.x + hero_x_size / 2)][getYindex(player.player_rect.y + hero_y_size)] = 3;
						t_bomb newBomb;
						newBomb.timer = SDL_GetTicks();
						newBomb.x = getXindex(player.player_rect.x + hero_x_size / 2);
						newBomb.y = getYindex(player.player_rect.y + hero_y_size);
						mx_push_back(&bombs, newBomb);
					}
				}
				if (event.key.keysym.sym == SDLK_ESCAPE) {

					if (pause_menu(renderer)) {
						running = false;
						game_status = -1;
					}
					
				}
			}
		}
		if (tick + 10 < SDL_GetTicks())
		{
			tick += 10;

			for (int i = 0; i < mx_list_size_enemy(enemies); i++)
			{
				calculate_enemy_step(&enemies[0].enemy, data);
				mx_push_back_enemy(&enemies, enemies->enemy);
				mx_pop_front_enemy(&enemies);
			}
			
		}
		if (fire_tick + 500 < SDL_GetTicks())
		{
			fire_tick += 490;
			for (int i = 0; i < 17; i++)
			{
				for (int j = 0; j < 13; j++) {
					if (data[i][j] == 4)
					{
						data[i][j] = 0;
					}
				}
			}
		}
		for (int i = 0; i < mx_list_size_enemy(enemies); i++)
		{
			if (isEnemyKill(player.player_rect, enemies[0].enemy) == true) {
				running = false;
				game_status = 0;
			}
			mx_push_back_enemy(&enemies, enemies->enemy);
			mx_pop_front_enemy(&enemies);
		}

		if (mx_list_size(bombs) > 0)
		{
			if (bombs[0].bomb.timer + 2000 < SDL_GetTicks())
			{
				if (data[bombs[0].bomb.x][bombs[0].bomb.y] == 3)
				{
					detonate_bomb(bombs[0].bomb.x, bombs[0].bomb.y, player.bomb_r, data, &player.count_of_bombs, boosters, booster_chance);
				}
				mx_pop_front(&bombs);
			}
		}
		if (data[getXindex(player.player_rect.x + player.player_rect.w / 2)][getYindex(player.player_rect.y + player.player_rect.h)] == 4) 
		{
			game_status = 0;
			running = false;
		}

		if (boosters[getXindex(player.player_rect.x + player.player_rect.w / 2)][getYindex(player.player_rect.y + player.player_rect.h)] > 0)
		{
			add_booster(boosters[getXindex(player.player_rect.x + player.player_rect.w / 2)][getYindex(player.player_rect.y + player.player_rect.h)], &player);
			boosters[getXindex(player.player_rect.x + player.player_rect.w / 2)][getYindex(player.player_rect.y + player.player_rect.h)] = 0;
		}

		for (int i = 0; i < mx_list_size_enemy(enemies); i++)
		{
			if (data[getXindex(enemies[0].enemy.enemy_rect.x + enemies[0].enemy.enemy_rect.w / 2)][getYindex(enemies[0].enemy.enemy_rect.y + enemies[0].enemy.enemy_rect.h / 2)] != 4) {
				mx_push_back_enemy(&enemies, enemies->enemy);
			}
			mx_pop_front_enemy(&enemies);
		}

		if (mx_list_size_enemy(enemies) == 0)
		{
			running = false;
			game_status = 1;
		}
		SDL_RenderPresent(renderer);
	}
	if (game_status == 0) {
		die_walk(renderer, player.player_rect);
	}
	else if (game_status == 1)
	{
		SDL_Texture* arr[8] = { back1, back2, front1, front2, left1, left2, right1, right2 };
		win_walk(renderer, player.player_rect,cur_hero_pos, arr);
	}
	return game_status;
}
