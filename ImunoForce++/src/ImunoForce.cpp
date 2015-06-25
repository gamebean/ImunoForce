#include "ImunoEngine.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>

using namespace std;

//==========================		ALLEGRO DEF HEADER		============================

#define DISPLAY_H 600
#define DISPLAY_W 800

enum {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_MAX
};
bool keys[KEY_MAX];

void initialization(){
	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init() failed", NULL, 0);
		::exit(EXIT_FAILURE);
	}
	if (!al_init_image_addon()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init_image_addon() failed", NULL, 0);
		::exit(EXIT_FAILURE);
	}
	if (!al_install_keyboard()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_install_keyboard() failed", NULL, 0);
		::exit(EXIT_FAILURE);
	}
	if (!al_init_primitives_addon()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init_primitives_addon() failed", NULL, 0);
		::exit(EXIT_FAILURE);
	}
}
//=======================================================================================

int main(int argc, char *argv[]) {
	int frame = 1, bTrig = 10, bulletFreq = 10;
	int currentPlayer = 1;  int dead = 1; int monkey = 1; // JUST FOR TEST

	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE* event_queue;
	bool quit = false;

	initialization();

	srand((unsigned)time(NULL)); // Uncertainty principle

	display = al_create_display(DISPLAY_W, DISPLAY_H);
	if (!display) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_create_display() failed", NULL, 0);
		::exit(EXIT_FAILURE);
	}
	timer = al_create_timer(1 / 60.0);
	if (!timer) {
		al_show_native_message_box(NULL, NULL, NULL, "al_create_timer() failed",
								   NULL, 0);
		::exit(EXIT_FAILURE);
	}
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_create_event_queue() failed", NULL, 0);
		::exit(EXIT_FAILURE);
	}

	ALLEGRO_BITMAP* sprites[4][20];
	sprites[player][0] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_0M.png");
	sprites[player][1] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_1M.png");
	sprites[player][2] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_2M.png");
	sprites[player][3] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_3M.png");
	sprites[player][4] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_4M.png");
	sprites[player][5] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_5M.png");
	sprites[player][6] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_6M.png");
	sprites[player][7] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_7M.png");
	sprites[player][8] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_8M.png");
	sprites[player][9] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_9M.png");
	sprites[player][10] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_10M.png");
	sprites[player][11] = al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_11M.png");

	Mask masks(al_load_bitmap("C:/Users/chosethecake/Documents/GitHub/ImunoForce/ImunoForce++/Sprites/sperm_0M.png"));
	/*for (int i = 0; i < 12; i++) {
		masks[player][i](sprites[player][i]);
		printf("Creating mask n%d\n", i + 1);
	}*/

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(timer);

	while (!quit) {
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			quit = true;

		/*if (ev.type == ALLEGRO_EVENT_TIMER) {
			
		}*/

		//	KEYBOARD VERIFICATION
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					keys[KEY_UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[KEY_DOWN] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[KEY_LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[KEY_RIGHT] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[KEY_SPACE] = true;
					break;
				case ALLEGRO_KEY_1:
					keys[KEY_1] = true;
					break;
				case ALLEGRO_KEY_2:
					keys[KEY_2] = true;
					break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					keys[KEY_UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[KEY_DOWN] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[KEY_LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[KEY_RIGHT] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[KEY_SPACE] = false;
					break;
				case ALLEGRO_KEY_1:
					keys[KEY_1] = false;
					dead = 1;
					break;
				case ALLEGRO_KEY_2:
					keys[KEY_2] = false;
					monkey = 1;
					break;
			}
		}

		if (al_is_event_queue_empty(event_queue)) {
			cout << "rola" << endl;
			masks.draw(DISPLAY_W / 2, DISPLAY_H / 2);
			al_draw_bitmap(sprites[player][0], DISPLAY_W / 2, DISPLAY_H / 2, 0);
			cout << "rola" << endl;

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	::exit(EXIT_SUCCESS);
}