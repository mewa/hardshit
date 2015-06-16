#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <main.h>
#include <stack.h>
#include <level.h>
#include <player.h>

extern int screenWidth;
extern int screenHeight;

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* eventQueue;
ALLEGRO_EVENT_SOURCE* keyboardEvents;
ALLEGRO_SAMPLE* themeSound;
ALLEGRO_SAMPLE* jumpSound;

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
	if (! al_init_acodec_addon()) {
		fprintf(stderr, "Could not install audio\n");
		return -4;
	}
	if (!al_install_audio()) {
		fprintf(stderr, "Could not install audio\n");
		return -5;
	}
	display = al_create_display(screenWidth, screenHeight);
	eventQueue =  al_create_event_queue();
	keyboardEvents = al_get_keyboard_event_source();
	al_register_event_source(eventQueue, keyboardEvents);
	al_reserve_samples(5);
	themeSound = al_load_sample("sounds/theme001.wav");
	jumpSound = al_load_sample("sounds/jump.wav");

	printf("allegro initialised\n");
	return 0;
}

int UP = 1;
int LEFT = 1 << 1;
int RIGHT = 1 << 2;

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
	bool al_play_sample(ALLEGRO_SAMPLE *spl, float gain, float pan, float speed,
	ALLEGRO_PLAYMODE loop, ALLEGRO_SAMPLE_ID *ret_id)
	*/
	al_play_sample(themeSound, 0.7f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, NULL);

	ALLEGRO_EVENT event;
	ALLEGRO_SAMPLE_ID jumpSoundId;
	int exit = 0;
	int state = 0;
	while (1) {
		for (int i = 0; i < 2 && al_get_next_event(eventQueue, &event); ++i) {
			if (event.type == ALLEGRO_EVENT_KEY_UP) {
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					exit = 1;
				}
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					state ^= UP;
					break;
				case ALLEGRO_KEY_SPACE:
					state ^= UP;
					break;
				case ALLEGRO_KEY_LEFT:
					state ^= LEFT;
					break;
				case ALLEGRO_KEY_RIGHT:
					state ^= RIGHT;
					break;
				case ALLEGRO_KEY_DOWN:
					break;
				}
			} else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					state |= UP;
					al_play_sample(jumpSound, 0.8f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, &jumpSoundId);
					break;
				case ALLEGRO_KEY_SPACE:
					state |= UP;				      
					al_play_sample(jumpSound, 0.8f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, &jumpSoundId);
					break;
				case ALLEGRO_KEY_LEFT:
					state |= LEFT;
					break;
				case ALLEGRO_KEY_RIGHT:
					state |= RIGHT;
					break;
				case ALLEGRO_KEY_DOWN:
					break;
				}
			}
		}
		if (exit)
			break;
		if (state & UP)
			player_jump(gPlayer);
		if (state & LEFT)
			player_move_left(gPlayer);
		if (state & RIGHT)
			player_move_right(gPlayer);
		al_clear_to_color(al_map_rgb(110, 120, 190));
		level_draw(level);
		player_move_down(gPlayer);
		player_draw(gPlayer, level);
		al_flip_display();
	}
	level_destroy(level);
	return  0;
}
