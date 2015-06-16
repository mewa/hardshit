#include <player.h>
#include <stdio.h>
#include <collision.h>
#include <bmputils.h>
#include <consts.h>
#include <level.h>

extern ALLEGRO_BITMAP* bmpHero;
extern int const kBlockSize;

extern int const screenWidth;
extern int const screenHeight;

float kSpeed = 0.1f;
float const kGravity = 0.2f;
float kJumpHeight = 3.5f;

float cameraX = 0.0f;
float cameraY = 0.0f;

float startX;
float startY;

player* player_create(float x, float y, level* level) {
  player* player = malloc(sizeof(player));
  player->x = x;
  player->y = y;
  startX = x;
  startY = y;
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
    //printf("jump: %f\n", player->jumpHeight);
  }
}

void player_stop_jump(player* player) {
  //printf("stop jump\n");
  player->canJump = 0;
  player->jumpHeight = 0;
}

void player_move_up(player* player) {
  player->y -= kGravity;
  if (collide_player_with_level(player, player->level)) {
    player->y +=  kGravity;
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
  player->y += kGravity;
  if (collide_player_with_level(player, player->level)) {
    player->y -= kGravity;
    player->canJump = 1;
  }
}

void player_destroy(player* player) {

}

void player_draw(player* player, level* level) {
  cameraX = player->x - (screenWidth / 2.0f) / (float) kBlockSize;
  cameraY = player->y - (screenHeight / 4.0f) / (float) kBlockSize;
  if (cameraX < 0) cameraX = 0;
  if (cameraY < 0) cameraY = 0;
  if (cameraX > level->w - screenWidth / (float)  kBlockSize) cameraX = level->w - screenWidth / (float) kBlockSize;
  if (cameraY > level->h - screenHeight / (float) kBlockSize) cameraY = level->h - screenHeight / (float) kBlockSize;
  float x = player->x - cameraX;
  float y = player->y - cameraY;
  bmp_draw(bmpHero, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
}
