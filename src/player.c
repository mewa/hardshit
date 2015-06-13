#include <player.h>
#include <stdio.h>
#include <collision.h>
#include <bmputils.h>

extern ALLEGRO_BITMAP* bmpHero;
extern int const kBlockSize;

struct player {
  float x;
  float y;
  level* level;
};


player* player_create(float x, float y, level* level) {
  player* player = malloc(sizeof(player));
  player->x = x;
  player->y = y;
  player->level = level;
  return player;
}

void player_move_up(player* player) {
  if (!collide_player_with_level(player, player->level)) {
    player->y -= 0.1f;
  }
}

void player_move_left(player* player) {
  if (!collide_player_with_level(player, player->level)) {
    player->x -= 0.1f;
  }
}

void player_move_right(player* player) {
  if (!collide_player_with_level(player, player->level)) {
    player->x += 0.1f;
  }
}

void player_move_down(player* player) {
  if (!collide_player_with_level(player, player->level)) {
    player->y += 0.1f;
  }
}

void player_destroy(player* player) {

}

void player_draw(player* player) {
  bmp_draw(bmpHero, player->x * kBlockSize, player->y * kBlockSize, kBlockSize, kBlockSize);
}
