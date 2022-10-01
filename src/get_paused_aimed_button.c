#include "../inc/header.h"

int get_paused_aimed_button(Sint32 mouse_x, Sint32 mouse_y) {
    if (mouse_x >= RESUME_X
        && mouse_x <= RESUME_X + BUTTON_SIZE_X
        && mouse_y >= RESUME_Y
        && mouse_y <= RESUME_Y + BUTTON_SIZE_Y) {
        return 7;
    }
    else if (mouse_x >= BACK_TO_MENU_X
        && mouse_x <= BACK_TO_MENU_X + BUTTON_SIZE_X
        && mouse_y >= BACK_TO_MENU_Y
        && mouse_y <= BACK_TO_MENU_Y + BUTTON_SIZE_Y) {
        return 8;
    }
    else
        return -1;
}
