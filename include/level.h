#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

struct level {
  char* filename;
  char** level;
  int w;
  int h;
};

typedef struct level level;

ALLEGRO_BITMAP* bmpWall;
ALLEGRO_BITMAP* bmpHero;
ALLEGRO_BITMAP* bmpLava;

ALLEGRO_BITMAP* bmpSpikes1;
ALLEGRO_BITMAP* bmpSpikes2;

ALLEGRO_BITMAP* bmpPowerup;
ALLEGRO_BITMAP* bmpGate;

ALLEGRO_BITMAP* bmpBackground0;
ALLEGRO_BITMAP* bmpBackground1;
ALLEGRO_BITMAP* bmpBackground2;
ALLEGRO_BITMAP* bmpBackground3;
ALLEGRO_BITMAP* bmpBackground4;
ALLEGRO_BITMAP* bmpBackground5;

/*
  Create level from file
 */
level* level_create(char* filename);

/*
  Load level
*/
void level_load(level* level);

/*
  Draw level
*/
void level_draw(level* level);

int level_collide(level* level, int x, int y);

void level_restart(level* level);

/*
  Destroy level
 */
void level_destroy(level* level);
