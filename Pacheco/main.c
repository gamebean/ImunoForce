#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "header.h"


  int main() {
	ALLEGRO_DISPLAY*			display;
	ALLEGRO_TIMER*				timer;
	ALLEGRO_EVENT				ev;
	ALLEGRO_EVENT_QUEUE*		event_queue;

	bool quit = false;

	Object player;
	player.x = DISPLAY_W / 2 - 14;
	player.y = DISPLAY_H / 2 - 32;

	/*Object bullet[MAX_BULLETS];
	for (i = 0; i < MAX_BULLETS; i++) {
	bullet[i].live = false;
	}*/

	initialization();

	//creation(display, timer, event_queue);
	display = al_create_display(DISPLAY_W, DISPLAY_H);
	if (!display) {
		al_show_native_message_box(NULL, NULL, NULL,
			"al_create_display() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}
	timer = al_create_timer(1 / 60.0);
	if (!timer) {
		al_show_native_message_box(NULL, NULL, NULL,
			"al_create_timer() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(NULL, NULL, NULL,
			"al_create_event_queue() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}

	// IMAGES
	player.img = al_load_bitmap("Sprites/sperm_0M.png");

	//	EVENTS
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//	TIMER
	al_start_timer(timer);


	//	MAIN LOOP
	while (!quit) {
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			quit = true;
		}

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//	FRAME COUNT
			frame = (frame >= 60) ? 1 : frame + 1;

			//	LIMIT COLISSION
			//limit_player_move(player);
			if (player.y <= 0) {
				player.y = 0;
				keys[KEY_UP] = false;
			}
			if (player.y >= DISPLAY_H - 64) {
				player.y = DISPLAY_H - 64;
				keys[KEY_DOWN] = false;
			}
			if (player.x <= 0) {
				player.x = 0;
				keys[KEY_LEFT] = false;
			}
			if (player.x >= DISPLAY_W - 28) {
				player.x = DISPLAY_W - 28;
				keys[KEY_RIGHT] = false;
			}

			//	MOVEMENT
			//move_player(player);
			if (keys[KEY_UP]) {
				player.y -= 3;
			}
			if (keys[KEY_DOWN]) {
				player.y += 3;
			}
			if (keys[KEY_LEFT]) {
				player.x -= 3;
				draw_flag = 0;
			}
			if (keys[KEY_RIGHT]) {
				player.x += 3;
				draw_flag = ALLEGRO_FLIP_HORIZONTAL;
			}

			//	FIRE
			//fire_bullet(player);
			int x = 1;

			if (keys[KEY_SPACE] && bTrig == 10) {
				while (bullet_search(x) != NULL)
					x++;
				bullet = bullet_add(bullet, x);
				bullet->x = player.x + 14;
				bullet->y = player.y;
				bTrig = frame % bulletFreq;
			}
			else if (keys[KEY_SPACE] && frame%bulletFreq == bTrig) {
				while (bullet_search(x) != NULL)
					x++;
				bullet = bullet_add(bullet, x);
				bullet->x = player.x + 14;
				bullet->y = player.y;
			}
			else if (!keys[KEY_SPACE]) {
				bTrig = 10;
			}


			//	DRAW
			/*		bullets v1
			for (i = 0; i < MAX_BULLETS; i++) {
			if (bullet[i].live) {
			al_draw_filled_circle(bullet[i].x, bullet[i].y, 5, al_map_rgb(255, 0, 255));
			bullet[i].y -= 10;
			if (bullet[i].y < 0) {
			bullet[i].live = false;
			}
			}
			}*/
			//bullet = bullet_search(0); // Points to header
			for (bullet = &bullet_head; bullet->next != NULL; bullet = bullet->next  ) { //Scans the all the structs;
				//bullet = bullet_search(i);
				if(bullet != NULL){
					al_draw_filled_circle(bullet->x, bullet->y, 5, al_map_rgb(255, 0, 255));
					bullet->y -= 10;
					if (bullet->y < 0) {
						//bullet_del(bullet);
					}
				}
			}

			al_draw_bitmap(player.img, player.x, player.y, draw_flag);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		//	KEYBOARD VERIFICATION
		//keyboard_verification(ev);
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
			}
		}
	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(player.img);

	exit(EXIT_SUCCESS);
}


