/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** struct_game.h
*/

#ifndef STRUCT_GAME_H_
    #define STRUCT_GAME_H_

    #include "my.h"
/**
* @file struct_game.h
* @brief defines data structures used in the project for the game
*/
    #define DENSITY_FOOD 0.5
    #define DENSITY_LINEMATE 0.3
    #define DENSITY_DERAUMERE 0.15
    #define DENSITY_SIBUR 0.1
    #define DENSITY_MENDIANE 0.1
    #define DENSITY_PHIRAS 0.08
    #define DENSITY_THYSTAME 0.05

typedef struct egg_s {
    int x_pos;
    int y_pos;
    int egg_id;
    struct egg_s *next;
} egg_t;

/**
* @struct team_s
* @brief struct that holds the team name and the max number of clients
*/
typedef struct team_s {
    char *name;
    int max_clients;
    int cpt_egg;
    int slots_available;
    egg_t *egg;
} team_t;

/**
* @struct game_s
* @brief struct that holds the game data
*/
typedef struct game_s {
    int width;
    int height;
    int freq;
    int cycle;
    int nb_teams;
    int player_slots;
    bool graphical;
    team_t **teams;
    int nb_eggs_layed;
} game_t;

#endif /* !STRUCT_GAME_H_ */
