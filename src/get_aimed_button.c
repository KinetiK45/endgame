#include "../inc/header.h"
int get_aimed_button(Sint32 mouse_x, Sint32 mouse_y) {
    if (mouse_x >= START_X
        && mouse_x <= START_X + BUTTON_SIZE_X
        && mouse_y >= START_Y
        && mouse_y <= START_Y + BUTTON_SIZE_Y) {
        return 0;
    }
    else if (mouse_x >= EXIT_X
        && mouse_x <= EXIT_X + BUTTON_SIZE_X
        && mouse_y >= EXIT_Y
        && mouse_y <= EXIT_Y + BUTTON_SIZE_Y) {
        return 2;
    }
    else if (mouse_x >= SETTINGS_X
        && mouse_x <= SETTINGS_X + BUTTON_SIZE_X
        && mouse_y >= SETTINGS_Y
        && mouse_y <= SETTINGS_Y + BUTTON_SIZE_Y) {
        return 1;
    }
    else if (mouse_x >= BACK_X
        && mouse_x <= BACK_X + BUTTON_SIZE_X
        && mouse_y >= BACK_Y
        && mouse_y <= BACK_Y + BUTTON_SIZE_Y) {
        return 3;
    }
    else if (mouse_x >= SOUND_SHIFT_X
        && mouse_x <= SOUND_SHIFT_X + BUTTON_SIZE_X
        && mouse_y >= SOUND_SHIFT_Y
        && mouse_y <= SOUND_SHIFT_Y + BUTTON_SIZE_Y) {
        return 4;
    }
    else if (mouse_x >= INCREASE_VOLUME_X
        && mouse_x <= INCREASE_VOLUME_X + INCREASE_VOLUME_SIZE_X
        && mouse_y >= INCREASE_VOLUME_Y
        && mouse_y <= INCREASE_VOLUME_Y + BUTTON_SIZE_Y) {
        return 5;
    }
    else if (mouse_x >= DECREASE_VOLUME_X
        && mouse_x <= DECREASE_VOLUME_X + DECREASE_VOLUME_SIZE_X
        && mouse_y >= DECREASE_VOLUME_Y
        && mouse_y <= DECREASE_VOLUME_Y + BUTTON_SIZE_Y) {
        return 6;
    }   
    else 
        return -1;
}
