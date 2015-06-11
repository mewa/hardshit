#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <main.h>
#include <stack.h>

ALLEGRO_DISPLAY* hWnd;
ALLEGRO_EVENT_QUEUE* eventQueue;
ALLEGRO_EVENT_SOURCE* keyboardEvents;

int init() {
  printf("Initialising\n");
  if (!al_init()) {
    fprintf(stderr, "Could not initialise allegro-5.0\n");
    return -1;
  }
  if (!al_install_keyboard()) {
    fprintf(stderr, "Could not install keyboard\n");
    return -2;
  }
  hWnd = al_create_display(1024, 768);
  al_clear_to_color(al_map_rgb(55, 65, 140));
  al_flip_display();
  eventQueue =  al_create_event_queue();
  keyboardEvents = al_get_keyboard_event_source();
  al_register_event_source(eventQueue, keyboardEvents);
  printf("Initialised\n");
  return 0;
}

int main(int argc, char** argv) {
  init();
  
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
    }
  }
  return  0;
}
