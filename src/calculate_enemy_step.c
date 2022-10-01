#include "../inc/header.h"

void calculate_enemy_step(t_enemy* enemy, int data[17][13]) {
	if (enemy->way == 0)
	{
		enemy->way = 1 + rand() % 4;
	}
	if (enemy->way == 1 && data[getXindex(enemy->enemy_rect.x - enemy->speed)][getYindex(enemy->enemy_rect.y)] == 0 && data[getXindex(enemy->enemy_rect.x - enemy->speed)][getYindex(enemy->enemy_rect.y + enemy->enemy_rect.h)] == 0 && enemy->enemy_rect.x - enemy->speed > FIRST_X)
	{
		enemy->enemy_rect.x -= enemy->speed;
		if (data[getXindex(enemy->enemy_rect.x - enemy->speed)][getYindex(enemy->enemy_rect.y)] != 0)
		{
			enemy->way = 0;
		}
	}
	else if (enemy->way == 2 && data[getXindex(enemy->enemy_rect.x + enemy->enemy_rect.w + enemy->speed)][getYindex(enemy->enemy_rect.y)] == 0 && data[getXindex(enemy->enemy_rect.x + enemy->enemy_rect.w + enemy->speed)][getYindex(enemy->enemy_rect.y + enemy->enemy_rect.h)] == 0 && enemy->enemy_rect.x + enemy->enemy_rect.h + enemy->speed < FIRST_X + 73 * 17)
	{
		enemy->enemy_rect.x += enemy->speed;
		if (data[getXindex(enemy->enemy_rect.x + enemy->speed)][getYindex(enemy->enemy_rect.y)] != 0)
		{
			enemy->way = 0;
		}
	}
	else if (enemy->way == 3 && data[getXindex(enemy->enemy_rect.x)][getYindex(enemy->enemy_rect.y - enemy->speed)] == 0 && data[getXindex(enemy->enemy_rect.x + enemy->enemy_rect.w)][getYindex(enemy->enemy_rect.y - enemy->speed)] == 0 && enemy->enemy_rect.y - enemy->speed > FIRST_Y)
	{
		enemy->enemy_rect.y -= enemy->speed;
		if (data[getXindex(enemy->enemy_rect.x)][getYindex(enemy->enemy_rect.y - enemy->speed)] != 0)
		{
			enemy->way = 0;
		}
	}
	else if (enemy->way == 4 && data[getXindex(enemy->enemy_rect.x)][getYindex(enemy->enemy_rect.y + enemy->enemy_rect.h + enemy->speed)] == 0 && data[getXindex(enemy->enemy_rect.x + enemy->enemy_rect.w)][getYindex(enemy->enemy_rect.y + enemy->enemy_rect.h + enemy->speed)] == 0 && enemy->enemy_rect.y + enemy->enemy_rect.w + enemy->speed < FIRST_Y + 73 * 13)
	{
		enemy->enemy_rect.y += enemy->speed;
		if (data[getXindex(enemy->enemy_rect.x)][getYindex(enemy->enemy_rect.y + enemy->speed)] != 0)
		{
			enemy->way = 0;
		}
	}
	else
	{
		enemy->way = 0;
	}
}
