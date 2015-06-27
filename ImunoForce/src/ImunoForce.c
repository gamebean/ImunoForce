#include <stdio.h>
#include "ImunoEngine.h"
#include "AllegroDef.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <allegro5/allegro_font.h>  // Biblioteca para utilização de fontes
#include <allegro5/allegro_ttf.h>   // Biblioteca para utilização de fontes

//Object object_head = {0,header,NULL,NULL,NULL,NULL};

int main(int argc, char *argv[]) {
	int frame = 1, bTrig = 10, bulletFreq = 10, i;
	int currentPlayer = 1;
	int dead = 1;
	int monkey = 1; // JUST FOR TEST

	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE* event_queue;
	bool quit = false;
	bool draw = false;
	int gameState = 0;
	int select = 0;
	char DOWN = 1, UP = 1;

	Object* p = object_search(header);
	Object* bllt = object_search(header);

	initialization();
	srand((unsigned) time(NULL)); // Uncertainty principle
	//creation(display, timer, event_queue);
	display = al_create_display(DISPLAY_W, DISPLAY_H);
	if (!display) {
		al_show_native_message_box(NULL, NULL, NULL,
				"al_create_display() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}
	timer = al_create_timer(1 / 60.0);
	if (!timer) {
		al_show_native_message_box(NULL, NULL, NULL, "al_create_timer() failed",
		NULL, 0);
		exit(EXIT_FAILURE);
	}
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(NULL, NULL, NULL,
				"al_create_event_queue() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}

	Mask *b =
			mask_new(
					al_load_bitmap(
							"Sprites/sperm_0S.png"));

	sprites[player][B_L] =
			al_load_bitmap(
					"Sprites/ShipB_L.png");
	sprites[player][B_C] =
			al_load_bitmap(
					"Sprites/ShipB_C.png");
	sprites[player][B_R] =
			al_load_bitmap(
					"Sprites/ShipB_R.png");
	sprites[player][S_L] =
			al_load_bitmap(
					"Sprites/ShipS_L.png");
	sprites[player][S_C] =
			al_load_bitmap(
					"Sprites/ShipS_C.png");
	sprites[player][S_R] =
			al_load_bitmap(
					"Sprites/ShipS_R.png");
	sprites[player][F_L] =
			al_load_bitmap(
					"Sprites/ShipF_L.png");
	sprites[player][F_C] =
			al_load_bitmap(
					"Sprites/ShipF_C.png");
	sprites[player][F_R] =
			al_load_bitmap(
					"Sprites/ShipF_R.png");

	sprites[enemy][0] =
			al_load_bitmap(
					"Sprites/Seeker0.png");
	sprites[enemy][1] =
			al_load_bitmap(
					"Sprites/Seeker1.png");
	sprites[enemy][2] =
			al_load_bitmap(
					"Sprites/Seeker2.png");
	sprites[enemy][3] =
			al_load_bitmap(
					"Sprites/Seeker3.png");
	sprites[enemy][4] =
			al_load_bitmap(
					"Sprites/Seeker4.png");
	sprites[enemy][5] =
			al_load_bitmap(
					"Sprites/Seeker5.png");
	sprites[enemy][6] =
			al_load_bitmap(
					"Sprites/Seeker6.png");
	sprites[enemy][7] =
			al_load_bitmap(
					"Sprites/Seeker7.png");

	sprites[bullet][0] =
			al_load_bitmap(
					"Sprites/bullet0.png");
	sprites[bullet][1] =
			al_load_bitmap(
					"Sprites/bullet1.png");
	sprites[bullet][2] =
			al_load_bitmap(
					"Sprites/bullet2.png");
	sprites[bullet][3] =
			al_load_bitmap(
					"Sprites/bullet3.png");

	for (i = 0; i < 9; i++) {
		masks[player][i] = mask_new(sprites[player][i]);
		printf("Creating player mask n%d\n", i + 1);
	}
	for (i = 0; i < 8; i++) {
		masks[enemy][i] = mask_new(sprites[enemy][i]);
		printf("Creating enemy mask n%d\n", i + 1);
	}
	for (i = 0; i < 4; i++) {
		masks[bullet][i] = mask_new(sprites[bullet][i]);
		printf("Creating bullet mask n%d\n", i + 1);
	}

	//initializes 2 players
	p = player_add("Ronaldo", 5, 12);
	//player_add(p,"Sprites/sperm_0L.png");
	p = object_search(1);

	Object normal;
	normal.type = bullet;
	normal.vector_size = 4;
	normal.frame_delay = 10;
	normal.img_i = 0;
	normal.height = al_get_bitmap_height(sprites[normal.type][normal.img_i]);
	normal.width = al_get_bitmap_width(sprites[normal.type][normal.img_i]);
	normal.vx = 0;
	normal.vy = -12;
	normal.life = -1;

	Object enemy1;
	enemy1.type = enemy;
	enemy1.vector_size = 8;
	enemy1.frame_delay = 5;
	enemy1.img_i = 0;
	enemy1.height = al_get_bitmap_height(sprites[enemy1.type][enemy1.img_i]);
	enemy1.width = al_get_bitmap_width(sprites[enemy1.type][enemy1.img_i]);
	enemy1.vx = 0.3;
	enemy1.vy = 1;
	enemy1.life = 3;
	//strcpy(enemy1.String,"NonSeeker"); // defines if its a seeker or not (1 yes 0 no)
	strcpy_s(enemy1.String, sizeof(enemy1.String), "NonSeeker");

	Object enemy2;
	enemy2.type = enemy;
	enemy2.vector_size = 8;
	enemy2.frame_delay = 5;
	enemy2.img_i = 0;
	enemy2.height = al_get_bitmap_height(sprites[enemy2.type][enemy2.img_i]);
	enemy2.width = al_get_bitmap_width(sprites[enemy2.type][enemy2.img_i]);
	enemy2.vx = 0.3;
	enemy2.vy = 1;
	enemy2.life = 3;
	//strcpy(enemy2.String,"Seeker"); // defines if its a seeker or not (1 yes 0 no)

	strcpy_s(enemy2.String, sizeof(enemy2.String), "Seeker");
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT *arial_24 = al_load_font("arial.ttf", 24, 0);
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
			p->vy += 0.8 * keys[KEY_DOWN] - 0.8 * keys[KEY_UP];
			p->vx += 0.8 * keys[KEY_RIGHT] - 0.8 * keys[KEY_LEFT];

			// ADD enemy
			if (keys[KEY_1] * dead) {
				enemy_add(enemy1, rand() % 540, -50);
				dead = 0;
			}
			if (keys[KEY_2] * monkey) {
				enemy_add(enemy2, rand() % 540, -50);
				monkey = 0;
			}

			//	FIRE
			if (keys[KEY_SPACE] && bTrig == 10) {
				bullet_add(normal, object_search(currentPlayer));
				bTrig = frame % bulletFreq;
			} else if (keys[KEY_SPACE] && frame % bulletFreq == bTrig) {
				bullet_add(normal, object_search(currentPlayer));
			} else if (!keys[KEY_SPACE]) {
				bTrig = 10;
			}

			//anim(p, 5, p_sprites, p_masks, 12);
			object_anim();
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
			case ALLEGRO_KEY_ENTER:
				keys[KEY_ENTER] = true;
				break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                keys[KEY_UP] = false;
                UP = 1;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[KEY_DOWN] = false;
                DOWN = 1;
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
			case ALLEGRO_KEY_ENTER:
				keys[KEY_ENTER] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				gameState = 0;
				break;
			}
		}

		if (al_is_event_queue_empty(event_queue)) {
			switch (gameState) {
			case 0:
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100, 100, 0,
						"         SINGLE-PLAYER");
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100, 125, 0,
						"         MULTI-PLAYER  ");
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100, 150, 0,
						"         UPGRADE  ");
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100, 175, 0,
						"         QUIT  ");
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100,
						100 + select * 25, 0, "       >");

				if (keys[KEY_UP] * UP) {
					select += -1;
					UP = 0;
				}
				if (keys[KEY_DOWN] * DOWN) {
					select += 1;
					DOWN = 0;
				}

				if (keys[KEY_ENTER]) {
					gameState = select + 1;
				}
				break;
			case 1:
				object_draw();
				p = object_search(1);
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100, 150, 0,
						"         LIFE: %d ", p->life);
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100, 350, 0,
						"         SCORE: %d ", get_score());
				break;
			case 2:
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100, 100, 0,
						" ASS HOLE!!!!");
				quit = true;
				break;
			case 3:
				al_draw_textf(arial_24, al_map_rgb(255, 255, 255), 100, 100, 0,
						"         TRIGGER: %d", 10 - bulletFreq);
				if (keys[KEY_UP] * UP) {
					bulletFreq += -1;
					UP = 0;
				}
				if (keys[KEY_DOWN] * DOWN) {
					bulletFreq += 1;
					DOWN = 0;
				}
				break;
			case 4:
				quit = true;
				break;
			}
			//object_track();

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	exit(EXIT_SUCCESS);
}
