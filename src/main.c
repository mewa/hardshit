#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <main.h>
#include <stack.h>
#include <level.h>
#include <player.h>

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* eventQueue;
ALLEGRO_EVENT_SOURCE* keyboardEvents;

player* gPlayer;

int init() {
  printf("initialising allegro\n");
  if (!al_init()) {
    fprintf(stderr, "Could not initialise allegro-5.0\n");
    return -1;
  }
  if (!al_init_image_addon()) {
    fprintf(stderr, "Could not initialise image addon\n");
    return -2;
  }
  if (!al_install_keyboard()) {
    fprintf(stderr, "Could not install keyboard\n");
    return -10;
  }
  display = al_create_display(1024, 768);
  eventQueue =  al_create_event_queue();
  keyboardEvents = al_get_keyboard_event_source();
  al_register_event_source(eventQueue, keyboardEvents);
  
  printf("allegro initialised\n");
  return 0;
}

int main(int argc, char** argv) {
  int (*fptr)(void);
  fptr = &init;
  fptr();

  int x = 5;
  stack* stack = stack_push(NULL, &x);
  printf("contains %d\n", stack_contains(stack, &x));
  stack = stack_pop(stack, &x);
  printf("contains %d\n", stack_contains(stack, &x));
  
  level* level = level_create("levels/level001.lvl");

  /*
void al_draw_scaled_bitmap(ALLEGRO_BITMAP *bitmap,
   float sx, float sy, float sw, float sh,
   float dx, float dy, float dw, float dh, int flags)
  */

   ALLEGRO_EVENT event;
  while (1) {
    al_wait_for_event(eventQueue, &event);
    if (event.type == ALLEGRO_EVENT_KEY_UP) {
      printf("Key up %d\n", event.keyboard.keycode);
      if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
	break;
      }
    } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      printf("Key down %d\n", event.keyboard.keycode);
    } else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
      printf("Key char %d\n", event.keyboard.keycode);
      switch (event.keyboard.keycode) {
      case ALLEGRO_KEY_UP:
	player_move_up(gPlayer);
	break;
      case ALLEGRO_KEY_LEFT:
	player_move_left(gPlayer);
	break;
      case ALLEGRO_KEY_RIGHT:
	player_move_right(gPlayer);
	break;
      case ALLEGRO_KEY_DOWN:
	player_move_down(gPlayer);
	break;
      }
    }
    al_clear_to_color(al_map_rgb(55, 65, 140));
    level_draw(level);
    player_draw(gPlayer);
    al_flip_display();
  }
  level_destroy(level);
  return  0;
}
