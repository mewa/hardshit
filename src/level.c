#include <level.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stack.h>
#include <bmputils.h>
#include <consts.h>
#include <player.h>

extern int const kBlockSize;

extern player* gPlayer;

level* level_create(char* filename) {
  level* level = malloc(sizeof(level));
  level->filename = strdup(filename);
  bmpWall = al_load_bitmap("textures/wall001.png");
  bmpHero = al_load_bitmap("textures/player001.png");
  level_load(level);
  return level;
}

void level_load(level* level) {
  FILE* f = fopen(level->filename, "rb");
  if (f) {
    int w, h;
    level->level = malloc(h * sizeof(char));
    fscanf(f, "%d %d", &w, &h);
    level->w = w;
    level->h = h;
    printf("w%dh%d, next char: %d\n", w, h, getc(f));
    for (int i = 0; i < h; ++i) {
      
      level->level[i] = malloc(w * sizeof(char));
      
      for (int j = 0; j < w; ++j) {
	int c = getc(f);
	level->level[i][j] = c;
      }
      getc(f);
    }
  } else {
    fprintf(stderr, "Could not open level `%s`\n", level->filename);
    return;
  }
  fclose(f);
}

void level_draw(level* level) {
  //printf("Drawing level `%s`\nSize %dx%d\n", level->filename, level->w, level->h);
  for (int i = 0; i < level->h; ++i) {
    for (int j = 0; j < level->w; ++j) {
      //printf("%c", level->level[i][j]);
      switch (level->level[i][j]) {
      case '#':
	bmp_draw(bmpWall, j * kBlockSize, i * kBlockSize, kBlockSize, kBlockSize);
	break;
      case 'P':
	if (!gPlayer) {
	  gPlayer = player_create(j, i, level);
	}
	break;
      }
    }
    //printf("\n");
  }
}

void level_destroy(level* level) {
  free(level->filename);
  free(level);
}
