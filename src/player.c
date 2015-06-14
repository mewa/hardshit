#include <player.h>
#include <stdio.h>
#include <collision.h>
#include <bmputils.h>

extern ALLEGRO_BITMAP* bmpHero;
extern int const kBlockSize;

float const kSpeed = 0.2f;
float const kJumpHeight = 3.5f;

player* player_create(float x, float y, level* level) {
  player* player = malloc(sizeof(player));
  player->x = x;
  player->y = y;
  player->level = level;
  player->canJump = 1;
  player->jumpHeight = 0;
  return player;
}

void player_jump(player* player) {
  if (player->canJump && player->jumpHeight < kJumpHeight) {
    float dy = player->y;
    for (int i = 0; i < 2; ++i) {
      player_move_up(player);
    }
    dy -= player->y;
    player->jumpHeight += dy;
  }
}

void player_stop_jump(player* player) {
  player->canJump = 0;
  player->jumpHeight = 0;
}

void player_move_up(player* player) {
  player->y -= kSpeed;
  if (collide_player_with_level(player, player->level)) {
    player->y += kSpeed;
    player_stop_jump(player);
  }
}

void player_move_left(player* player) {
  player->x -= kSpeed;
  if (collide_player_with_level(player, player->level)) {
    player_move_up(player);
    if (collide_player_with_level(player, player->level)) {
      player->x += kSpeed;
    }
  }
}

void player_move_right(player* player) {
  player->x += kSpeed;
  if (collide_player_with_level(player, player->level)) {
    player_move_up(player);
    if (collide_player_with_level(player, player->level)) {
      player->x -= kSpeed;
    }
  }
}

void player_move_down(player* player) {
  player->y += kSpeed;
  if (collide_player_with_level(player, player->level)) {
    player->y -= kSpeed;
    player->canJump = 1;
  }
}

void player_destroy(player* player) {

}

void player_draw(player* player) {
  bmp_draw(bmpHero, player->x * kBlockSize, player->y * kBlockSize, kBlockSize, kBlockSize);
}
