#include <level.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stack.h>
#include <bmputils.h>
#include <consts.h>
#include <player.h>
#include <consts.h>

extern int const kBlockSize;

extern player* gPlayer;

extern float cameraX;
extern float cameraY;

extern float kSpeed;
extern float kJumpHeight;

extern int const screenWidth;
extern int const screenHeight;

level* level_create(char* filename) {
  level* level = malloc(sizeof(level));
  level->filename = strdup(filename);
  bmpWall = al_load_bitmap("textures/wall001.png");
  bmpHero = al_load_bitmap("textures/player001.png");
  bmpLava = al_load_bitmap("textures/lava001.png");

  bmpSpikes1 = al_load_bitmap("textures/spikes001.png");

  bmpPowerup = al_load_bitmap("textures/powerup001.png");

  bmpGate = al_load_bitmap("textures/gate001.png");
  
  bmpBackground0 = al_load_bitmap("textures/bg005.png");
  printf("001 loaded\n");
  bmpBackground1 = al_load_bitmap("textures/bg004.jpg");
  bmpBackground2 = al_load_bitmap("textures/bg003.jpg");
  bmpBackground3 = al_load_bitmap("textures/bg002.png");
  bmpBackground4 = al_load_bitmap("textures/bg001.png");
  bmpBackground5 = al_load_bitmap("textures/bg001.png");
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
        if (c == 'P' && !gPlayer) {
          gPlayer = player_create(j, i, level);
        }
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
      float x, y;
      x = j - cameraX;
      y = i - cameraY;
      switch (level->level[i][j]) {
      case '#':
        bmp_draw(bmpWall, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
        break;
      case 'L':
	bmp_draw(bmpLava, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	break;
      case 'P':
	bmp_draw(bmpBackground0, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
        break;
      case 'A':
	bmp_draw(bmpSpikes1, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	break;
      case 'G':
	bmp_draw(bmpPowerup, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	break;
      case 'E':
	bmp_draw(bmpGate, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	break;
      case ' ':
	switch ((int) (i / (float) level->h * 6.5f)) {
	case 0:
	  //bmp_draw(bmpBackground0, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	  break;
	case 1:
	  bmp_draw(bmpBackground1, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	  break;
	case 2:
	  bmp_draw(bmpBackground2, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	  break;
	case 3:
	  bmp_draw(bmpBackground3, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	  break;
	case 4:
	  bmp_draw(bmpBackground4, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	  break;
	case 5:
	  bmp_draw(bmpBackground5, x * kBlockSize, y * kBlockSize, kBlockSize, kBlockSize);
	  break;
	}
	break;
      }
    }
    //printf("\n");
  }
}

int level_collide(level* level, int x, int y) {
  switch (level->level[y][x]) {
  case '#':
    player_stop_jump(gPlayer);
    return 1;
  case 'L':
    printf("dead\n");
    level_restart(level);
    return 0;
  case 'A':
    printf("dead\n");
    level_restart(level);
    return 0;
  case 'G':
    kSpeed = 0.2f;
    kJumpHeight = 5.0f;
    return 0;
  case 'E':
    kSpeed = 0.2f;
    kJumpHeight = 5.0f;
    printf("Level complete/too lazy to update GUI\n");
    return 0;
  }
  return 0;
}

void level_restart(level* level) {
  kJumpHeight = 3.5f;
  kSpeed = 0.1f;
  for (int i = 0; i < level->h; ++i) {
    for (int j = 0; j < level->w; ++j) {
      //printf("%c", level->level[i][j]);
      float x, y;
      x = j - cameraX;
      y = i - cameraY;
      switch (level->level[i][j]) {
      case 'P':
	gPlayer->x = j;
	gPlayer->y = i;
        break;
      }
    }
  }
}

void level_destroy(level* level) {
  free(level->filename);
  free(level);
}
