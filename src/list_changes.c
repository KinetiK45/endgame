#include "../inc/header.h"

t_list* mx_create_node(t_bomb bomb) {
    t_list* node = (t_list*)malloc(sizeof(t_list));
    node->bomb = bomb;
    node->next = NULL;
    return node;
}

int mx_list_size(t_list* list) {
    if (list == NULL) return 0;
    int count = 0;
    t_list* temp = list;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

void mx_pop_front(t_list** list) {
    if (list == NULL)
        return;
    t_list* temp = *list;
    *list = temp->next;
    free(temp);
    temp = NULL;
}

void mx_clear_list(t_list** list) {
    if (!*list) return;
    t_list* temp;
    while (*list) {
        temp = (*list)->next;
        (*list)->next = NULL;
        free(*list);
        *list = temp;
    }
    list = NULL;
}

void mx_push_back(t_list** list, t_bomb bomb) {
    if (!*list) {
        *list = mx_create_node(bomb);
    }
    else {
        t_list* temp = *list;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = mx_create_node(bomb);
    }
}

t_list_enemies* mx_create_node_enemy(t_enemy enemy) {
    t_list_enemies* node = (t_list_enemies*)malloc(sizeof(t_list_enemies));
    node->enemy = enemy;
    node->next = NULL;
    return node;
}

int mx_list_size_enemy(t_list_enemies* list) {
    if (list == NULL) return 0;
    int count = 0;
    t_list_enemies* temp = list;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

void mx_pop_front_enemy(t_list_enemies** list) {
    if (list == NULL)
        return;
    t_list_enemies* temp = *list;
    if (temp->next) {
        *list = temp->next;
    }
    else
    {
        *list = NULL;
    }
    free(temp);
    temp = NULL;
}

void mx_clear_list_enemy(t_list_enemies** list) {
    if (!*list) return;
    t_list_enemies* temp;
    while (*list) {
        temp = (*list)->next;
        (*list)->next = NULL;
        free(*list);
        *list = temp;
    }
    list = NULL;
}

void mx_push_back_enemy(t_list_enemies** list, t_enemy enemy) {
    if (!*list) {
        *list = mx_create_node_enemy(enemy);
    }
    else {
        t_list_enemies* temp = *list;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = mx_create_node_enemy(enemy);
    }
}
