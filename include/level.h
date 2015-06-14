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

/*
  Destroy level
 */
void level_destroy(level* level);
