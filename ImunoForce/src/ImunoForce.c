#include <stdio.h>
#include "ImunoEngine.h"
#include "AllegroDef.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

//Object object_head = {0,header,NULL,NULL,NULL,NULL};


int main(int argc, char *argv[])
{
	int frame=1, bTrig=10, bulletFreq=10;
	int currentPlayer = 1; // JUST FOR TEST

	ALLEGRO_DISPLAY*			display;
	ALLEGRO_TIMER*				timer;
	ALLEGRO_EVENT				ev;
	ALLEGRO_EVENT_QUEUE*		event_queue;
	bool quit = false;

	Object* p = object_search(header);
	Object* bllt = object_search(header);

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

	Mask *b = mask_new(al_load_bitmap("Sprites/sperm_0S.png"));
	ALLEGRO_BITMAP* p_sprites[12];
	p_sprites[0] = al_load_bitmap("Sprites/sperm_0M.png");
	p_sprites[1] = al_load_bitmap("Sprites/sperm_1M.png");
	p_sprites[2] = al_load_bitmap("Sprites/sperm_2M.png");
	p_sprites[3] = al_load_bitmap("Sprites/sperm_3M.png");
	p_sprites[4] = al_load_bitmap("Sprites/sperm_4M.png");
	p_sprites[5] = al_load_bitmap("Sprites/sperm_5M.png");
	p_sprites[6] = al_load_bitmap("Sprites/sperm_6M.png");
	p_sprites[7] = al_load_bitmap("Sprites/sperm_7M.png");
	p_sprites[8] = al_load_bitmap("Sprites/sperm_8M.png");
	p_sprites[9] = al_load_bitmap("Sprites/sperm_9M.png");
	p_sprites[10] = al_load_bitmap("Sprites/sperm_10M.png");
	p_sprites[11] = al_load_bitmap("Sprites/sperm_11M.png");


	//initializes 2 players
	p = player_add(p, p_sprites[0]);
	//player_add(p,"Sprites/sperm_0L.png");
	p = object_search(1);

	

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

	while (!quit) {
			al_wait_for_event(event_queue, &ev);

			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				quit = true;
			}

			if (ev.type == ALLEGRO_EVENT_TIMER) {
				//	FRAME COUNT
				frame = (frame >= 60) ? 1 : frame + 1;

				
				//	MOVEMENT
				//move_player(player);
				p = object_search(currentPlayer);

				//p->player->img = p_sprites[(int)(frame / 5)];

				/*switch ((int)(frame / 5)) {
					case 0:
						p->player->img = al_load_bitmap("Sprites/sperm_0M.png");
						break;
					case 1:
						p->player->img = al_load_bitmap("Sprites/sperm_1M.png");
						break;
					case 2:
						p->player->img = al_load_bitmap("Sprites/sperm_2M.png");
						break;
					case 3:
						p->player->img = al_load_bitmap("Sprites/sperm_3M.png");
						break;
					case 4:
						p->player->img = al_load_bitmap("Sprites/sperm_4M.png");
						break;
					case 5:
						p->player->img = al_load_bitmap("Sprites/sperm_5M.png");
						break;
					case 6:
						p->player->img = al_load_bitmap("Sprites/sperm_6M.png");
						break;
					case 7:
						p->player->img = al_load_bitmap("Sprites/sperm_7M.png");
						break;
					case 8:
						p->player->img = al_load_bitmap("Sprites/sperm_8M.png");
						break;
					case 9:
						p->player->img = al_load_bitmap("Sprites/sperm_9M.png");
						break;
					case 10:
						p->player->img = al_load_bitmap("Sprites/sperm_10M.png");
						break;
					case 11:
						p->player->img = al_load_bitmap("Sprites/sperm_11M.png");
						break;
					default:
						printf("cagou\n");
						break;
				}*/

				switch ((int)(frame / 5)) {
					case 0:
						p->player->img = p_sprites[0];
						break;
					case 1:
						p->player->img = p_sprites[1];
						break;
					case 2:
						p->player->img = p_sprites[2];
						break;
					case 3:
						p->player->img = p_sprites[3];
						break;
					case 4:
						p->player->img = p_sprites[4];
						break;
					case 5:
						p->player->img = p_sprites[5];
						break;
					case 6:
						p->player->img = p_sprites[6];
						break;
					case 7:
						p->player->img = p_sprites[7];
						break;
					case 8:
						p->player->img = p_sprites[8];
						break;
					case 9:
						p->player->img = p_sprites[9];
						break;
					case 10:
						p->player->img = p_sprites[10];
						break;
					case 11:
						p->player->img = p_sprites[11];
						break;
					default:
						printf("cagou\n");
						break;
				}

				
				if (keys[KEY_UP]) {
					p->player->y -= 3;
				}
				if (keys[KEY_DOWN]) {
					p->player->y += 3;
				}
				if (keys[KEY_LEFT]) {
					p->player->x -= 3;
				}
				if (keys[KEY_RIGHT]) {
					p->player->x += 3;
				}
 				if (keys[KEY_1]){
					currentPlayer = 1;
				}
				if (keys[KEY_2]){
					currentPlayer = 2;
				}


				//	FIRE
				//fire_bullet(player);
				if (keys[KEY_SPACE] && bTrig == 10) {

					bullet_add(bllt,currentPlayer,"Sprites/sperm_0S.png", b);
					bTrig = frame % bulletFreq;
				}
				else if (keys[KEY_SPACE] && frame%bulletFreq == bTrig) {
					bullet_add(bllt,currentPlayer,"Sprites/sperm_0S.png", b);
				}
				else if (!keys[KEY_SPACE]) {
					bTrig = 10;
				}

				object_colision();
				object_move();
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
					break;
				case ALLEGRO_KEY_2:
					keys[KEY_2] = false;
					break;
				}
			}

			if( al_is_event_queue_empty(event_queue)){


				object_draw();

				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}

		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_destroy_bitmap(p->player->img);

		exit(EXIT_SUCCESS);
}
