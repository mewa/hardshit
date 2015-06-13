#pragma once

#include <level.h>

struct player;

typedef struct player player;

player* player_create(float x, float y, level* level);

void player_move_up(player* player);

void player_move_left(player* player);

void player_move_right(player* player);

void player_move_down(player* player);

void player_destroy(player* player);

void player_draw(player* player);
