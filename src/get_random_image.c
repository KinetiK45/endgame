#include "../inc/header.h"

char* get_random_image(void) {
	char* image_addresses[] = {
		"./resource/backgrounds/Blue_Nebula/Blue_Nebula1.png",
		"./resource/backgrounds/Blue_Nebula/Blue_Nebula2.png",
		"./resource/backgrounds/Blue_Nebula/Blue_Nebula3.png",
		"./resource/backgrounds/Blue_Nebula/Blue_Nebula5.png",
		"./resource/backgrounds/Blue_Nebula/Blue_Nebula6.png",
		"./resource/backgrounds/Blue_Nebula/Blue_Nebula8.png",
		//"./resource/backgrounds/Green_Nebula/Green_Nebula5.png",
		//"./resource/backgrounds/Green_Nebula/Green_Nebula6.png",
		//"./resource/backgrounds/Green_Nebula/Green_Nebula7.png",
		//"./resource/backgrounds/Green_Nebula/Green_Nebula8.png",
		"./resource/backgrounds/Purple_Nebula/Purple_Nebula1.png",
		"./resource/backgrounds/Purple_Nebula/Purple_Nebula2.png",
		"./resource/backgrounds/Purple_Nebula/Purple_Nebula3.png",
		"./resource/backgrounds/Purple_Nebula/Purple_Nebula4.png",
		"./resource/backgrounds/Purple_Nebula/Purple_Nebula5.png",
		//"./resource/backgrounds/Purple_Nebula/Purple_Nebula6.png",
		//"./resource/backgrounds/Purple_Nebula/Purple_Nebula7.png",
		//"./resource/backgrounds/Purple_Nebula/Purple_Nebula8.png"
	};
	return image_addresses[rand() % 11];
}
