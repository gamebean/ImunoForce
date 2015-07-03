#include "Multiplayer.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>
#include <allegro5/allegro_font.h>  // Biblioteca para utilização de fontes
#include <allegro5/allegro_ttf.h>   // Biblioteca para utilização de fontes
#include "AllegroDef.h"
#include "ImunoEngine.h"


//Object object_head = {0,header,NULL,NULL,NULL,NULL};
main(int argc, char *argv[]) {
	int frame = 1, bTrig = 10, bTrig2 = 10 , bulletFreq = 10, i,j;
	int shoot_enable = 0;
	int shoot_enable2 = 0;
	int bullet_type = 1;
	int DNA_points = 0;
	int DNA_spent = 0;
	int UPGRADE[3] = {1, 1, 1};
	char ip[15] = "127.0.0.1";

	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE* event_queue;

	bool isSet = false;
	bool quit = false;
	bool playMenuSong = false;
	bool stopMenuSong = false;
	bool playHit = false;

	int host = false;
	int join = 0;
	int gameState = 0;
	int multiState = 0;
	int select = 0;

	char DOWN = 1, UP = 1, RIGHT = 1;

	//Multi-player variables
	Data data[DATA_LENGHT];
	GameVar var = {0,0,0,0};

	Object* p = object_search(0); // p is used to access the objects in the list

	//Initialize allegro addons
	initialization();

	ALLEGRO_FONT *pressstart_20 = al_load_font("PressStart2P.ttf", 20, 0);

//SOUNDS
	al_reserve_samples(10);
	ALLEGRO_SAMPLE* sega_sound = al_load_sample("Sounds/GameBean.wav");
	ALLEGRO_SAMPLE* hit = al_load_sample("Sounds/Hit_Hurt.wav");
	ALLEGRO_SAMPLE* shoot = al_load_sample("Sounds/Piu.wav");
	ALLEGRO_SAMPLE* menu_sound = al_load_sample("Sounds/MenuSong.wav");
	ALLEGRO_SAMPLE_ID* menu_sound_id = NULL;
	ALLEGRO_SAMPLE* game_sound = al_load_sample("Sounds/GameSong.wav");
	ALLEGRO_SAMPLE_ID* game_sound_id = NULL;

	srand((unsigned) time(NULL)); // Uncertainty principle
	
	//creation(display, timer, event_queue);
	display = al_create_display(DISPLAY_W, DISPLAY_H);
	if (!display) {

		al_show_native_message_box(NULL, NULL, NULL, "al_create_display() failed", NULL, 0);
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
		al_show_native_message_box(NULL, NULL, NULL, "al_create_event_queue() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}

	server_initialise();
	engine_init();

	ALLEGRO_BITMAP *cursor = al_load_bitmap("Sprites/Select.png");
	ALLEGRO_BITMAP *menu = al_load_bitmap("Sprites/Menu 256color_2.png");
	ALLEGRO_BITMAP *opening = al_load_bitmap("Sprites/Opening.png");

	float alfa;
	al_clear_to_color(al_map_rgb(255, 255, 255));

	for (alfa = 0.0001; alfa <= 1; alfa+=0.0003) {
		al_draw_tinted_bitmap(opening, al_map_rgba_f(1,1,1, alfa), 0, 0, 0);
		al_flip_display();
		//al_rest(0.0002);
	}
	// PLAY SEGA SOUND
	al_play_sample(sega_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
	al_rest(2);

	for (alfa = 1; alfa >= 0; alfa-=0.0003) {
		//al_rest(0.0002);
		al_draw_tinted_bitmap(opening, al_map_rgba_f(1,1,1, alfa), 0, 0, 0);
		al_flip_display();
	}

//Start loading screen
	float l_pctg;
	draw_loading(l_pctg=0, pressstart_20);
	
//Add background
	background_add(0, 0);
	background_add(0, -DISPLAY_H);

//Define bullets and enemies characteristics
	Object normal;
	normal.type = bullet;
	normal.vector_size = 1;
	normal.frame_delay = 10;
	normal.img_i = 0;
	normal.height = al_get_bitmap_height(sprites[normal.type][normal.img_i]);
	normal.width = al_get_bitmap_width(sprites[normal.type][normal.img_i]);
	normal.vx = 0;
	normal.vy = -12;
	normal.life = -1;

	Object left;
	left.type = bullet;
	left.vector_size = 1;
	left.frame_delay = 10;
	left.img_i = 0;
	left.height = al_get_bitmap_height(sprites[left.type][left.img_i]);
	left.width = al_get_bitmap_width(sprites[left.type][left.img_i]);
	left.vx = 3;
	left.vy = -10;
	left.life = -1;

	Object right;
	right.type = bullet;
	right.vector_size = 1;
	right.frame_delay = 10;
	right.img_i = 0;
	right.height = al_get_bitmap_height(sprites[right.type][right.img_i]);
	right.width = al_get_bitmap_width(sprites[right.type][right.img_i]);
	right.vx = -3;
	right.vy = -10;
	right.life = -1;

	Object d_normal;
	d_normal.type = bullet;
	d_normal.vector_size = 1;
	d_normal.frame_delay = 10;
	d_normal.img_i = 0;
	d_normal.height = al_get_bitmap_height(sprites[d_normal.type][d_normal.img_i]);
	d_normal.width = al_get_bitmap_width(sprites[d_normal.type][d_normal.img_i]);
	d_normal.vx = 0;
	d_normal.vy = 12;
	d_normal.life = -1;

	Object d_left;
	d_left.type = bullet;
	d_left.vector_size = 1;
	d_left.frame_delay = 10;
	d_left.img_i = 0;
	d_left.height = al_get_bitmap_height(sprites[d_left.type][d_left.img_i]);
	d_left.width = al_get_bitmap_width(sprites[d_left.type][d_left.img_i]);
	d_left.vx = 3;
	d_left.vy = 10;
	d_left.life = -1;

	Object d_right;
	d_right.type = bullet;
	d_right.vector_size = 1;
	d_right.frame_delay = 10;
	d_right.img_i = 0;
	d_right.height = al_get_bitmap_height(sprites[d_right.type][d_right.img_i]);
	d_right.width = al_get_bitmap_width(sprites[d_right.type][d_right.img_i]);
	d_right.vx = -3;
	d_right.vy = 10;
	d_right.life = -1;

	Object enemies[5];
	enemies[0].type = enemy_c;
	enemies[0].vector_size = 4;
	enemies[0].frame_delay = 7;
	enemies[0].img_i = 0;
	enemies[0].height = al_get_bitmap_height(sprites[enemies[0].type][enemies[0].img_i]);
	enemies[0].width = al_get_bitmap_width(sprites[enemies[0].type][enemies[0].img_i]);
	enemies[0].vx = 0.6;
	enemies[0].vy = 3;
	enemies[0].life = 3;
	strcpy_s(enemies[0].String, sizeof(enemies[0].String), "NonSeeker");	// defines if its a seeker or not (1 yes 0 no)

	enemies[1].type = enemy;
	enemies[1].vector_size = 1;
	enemies[1].frame_delay = 5;
	enemies[1].img_i = 0;
	enemies[1].height = al_get_bitmap_height(sprites[enemies[1].type][enemies[1].img_i]);
	enemies[1].width = al_get_bitmap_width(sprites[enemies[1].type][enemies[1].img_i]);
	enemies[1].vx = 0;
	enemies[1].vy = 1;
	enemies[1].life = 3;
	strcpy_s(enemies[1].String, sizeof(enemies[1].String), "Seeker");	// defines if its a seeker or not (1 yes 0 no)

	enemies[2].type = enemy_b;
	enemies[2].vector_size = 1;
	enemies[2].frame_delay = 5;
	enemies[2].img_i = 0;
	enemies[2].height = al_get_bitmap_height(sprites[enemies[2].type][enemies[2].img_i]);
	enemies[2].width = al_get_bitmap_width(sprites[enemies[2].type][enemies[2].img_i]);
	enemies[2].vx = 0;
	enemies[2].vy = 4;
	enemies[2].life = 5;
	strcpy_s(enemies[2].String, sizeof(enemies[2].String), "Wall");

	enemies[3].type = enemy_c;
	enemies[3].vector_size = 4;
	enemies[3].frame_delay = 7;
	enemies[3].img_i = 0;
	enemies[3].height = al_get_bitmap_height(sprites[enemies[3].type][enemies[3].img_i]);
	enemies[3].width = al_get_bitmap_width(sprites[enemies[3].type][enemies[3].img_i]);
	enemies[3].vx = -0.6;
	enemies[3].vy = 3;
	enemies[3].life = 3;
	strcpy_s(enemies[3].String, sizeof(enemies[3].String), "NonSeeker");	// defines if its a seeker or not (1 yes 0 no)

	enemies[4].type = enemy;
	enemies[4].vector_size = 1;
	enemies[4].frame_delay = 5;
	enemies[4].img_i = 0;
	enemies[4].height = al_get_bitmap_height(sprites[enemies[4].type][enemies[4].img_i]);
	enemies[4].width = al_get_bitmap_width(sprites[enemies[4].type][enemies[4].img_i]);
	enemies[4].vx = 0;
	enemies[4].vy = 10;
	enemies[4].life = 3;
	strcpy_s(enemies[4].String, sizeof(enemies[4].String), "Shooter");	// defines if its a seeker or not (1 yes 0 no)
//All defined by here...

//God we have things loading...
//	Creating Masks for pixel perfect collision
	for (i = 0; i < 9; i++) {
		draw_loading(l_pctg+=6.25, pressstart_20);
		masks[player][i] = mask_new(sprites[player][i]);
		masks[player2][i] = masks[player][i];
		printf("Creating player and player2 mask n%d\n", i + 1);
	}
	
	draw_loading(l_pctg += 6.25, pressstart_20);
	masks[enemy][0] = mask_new(sprites[enemy][0]);
	
	draw_loading(l_pctg += 6.25, pressstart_20);
	masks[enemy_b][0] = mask_new(sprites[enemy_b][0]);
	
	for (i = 0; i < 4; i++) {
		draw_loading(l_pctg += 6.25, pressstart_20);
		masks[enemy_c][i] = mask_new(sprites[enemy_c][i]);
		printf("Creating enemy_c mask n%d\n", i + 1);
	}
	draw_loading(l_pctg += 6.25, pressstart_20);
	
	masks[bullet][0] = mask_new(sprites[bullet][0]);
	printf("Creating bullet mask n%d\n", i + 1);
// You better watch you pixels son...
	
//Allegro bureaucracy
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

//You will play with this guy
	p = player_add("Ronaldo", 5, 12);
	p = object_search(1); //p starts to pointer to player one

//Starts the timer and some good old music
	al_start_timer(timer);
	al_play_sample(menu_sound, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &menu_sound_id);

//	The main loop, let the game begin
	while (!quit) {
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			quit = true;
		}

		if (ev.type == ALLEGRO_EVENT_TIMER && gameState==1) {
			//	FRAME COUNT
			frame = (frame >= 60) ? 1 : frame + 1;

			//	MOVEMENT
			p = object_search(1);//Moves player one
				p->vy += 0.8 * keys[KEY_DOWN] - 0.8 * keys[KEY_UP];
				p->vx += 0.8 * keys[KEY_RIGHT] - 0.8 * keys[KEY_LEFT];

			p = object_search(2);//Moves player two if there is one
				p->vy += 0.8 * keys2[KEY_DOWN] - 0.8 * keys2[KEY_UP];
				p->vx += 0.8 * keys2[KEY_RIGHT] - 0.8 * keys2[KEY_LEFT];

			// Add enemies based on you score
			int offset = rand() % 400 + 200;// Where enemies will spawn
			int enemy_rand = rand() % 2;
			if (enemy_count() < log2(get_score() + 2) * 2) {
				int level = get_score() / 5;
				level = (level > 5) ? 5 : level;
				switch(rand() % (level + 1)) {
					case 5:
						p = object_search(1);
						for(i = 0; i < 4; i++) {
							enemy_add(enemies[4], p->x, -50 - 30 * i);
						}
					break;
					case 4:
						for(i = 0; i < 3; i++) {
							enemy_add(enemies[1], enemy_rand * 900 - 50, offset + 200 * i - 200);
						}
					break;
					case 3:
						for(i = 0; i < 3; i++) {
							enemy_add(enemies[1], offset + 200 * i - 200, -50);
						}
					break;
					case 2:
						if (!object_find("Wall")) {
							for(i = 0; i < 50; i++) {
								enemy_add(enemies[2], offset - 180, -50 - 50 * i);
								enemy_add(enemies[2], offset + 180, -50 - 50 * i);
							}
						}

					break;
					case 1:
						for(i = 0; i < 10; i++) {
							enemy_add(enemies[3 * enemy_rand], 50 * i, (enemy_rand == 1) ? (-300 + 25 * i) : (-50 - 25 * i));
						}
					break;
					case 0:
						for(i = 0; i < 3; i++) {
							enemy_add(enemies[3 * enemy_rand], offset + 50 * i, (enemy_rand == 1) ? (-125 + 25 * i) : (-50 - 25 * i));
						}
					break;
				}
			}

			//	FIRE FIRE BANG BANG!!
			//bTrig and bulletFreq set the speed that you can shoot
			if (keys[KEY_SPACE] && bTrig == 10) {
				shoot_enable = 1;
				al_play_sample(shoot, 2, 0, 3, ALLEGRO_PLAYMODE_ONCE, 0);
				bTrig = frame % bulletFreq;
			} else if (keys[KEY_SPACE] && frame % bulletFreq == bTrig) {
				al_play_sample(shoot, 2, 0, 3, ALLEGRO_PLAYMODE_ONCE, 0);
				shoot_enable = 1;
			} else if (!keys[KEY_SPACE]) {
				bTrig = 10;
			}

			if (keys2[KEY_SPACE] && bTrig2 == 10) {
				shoot_enable2 = 1;
				bTrig2 = frame % bulletFreq;
			} else if (keys2[KEY_SPACE] && frame % bulletFreq == bTrig2) {
				shoot_enable2 = 1;
			} else if (!keys2[KEY_SPACE]) {
				bTrig2 = 10;
			}

// Fire the bullets for player one and two
			switch(bullet_type * shoot_enable) {
				case 3:
					bullet_add(d_normal, object_search(1));
					bullet_add(d_left, object_search(1));
					bullet_add(d_right, object_search(1));
				case 2:
					bullet_add(left, object_search(1));
					bullet_add(right, object_search(1));
				case 1:
					bullet_add(normal, object_search(1));
					shoot_enable = 0;
				break;
				default:
				break;
			}
			p = object_search(2);
			switch(bullet_type * shoot_enable2) {
				case 3:
					bullet_add(d_normal, object_search(2));
					bullet_add(d_left, object_search(2));
					bullet_add(d_right, object_search(2));
				case 2:
					bullet_add(left, object_search(2));
					bullet_add(right, object_search(2));
				case 1:
					bullet_add(normal, object_search(2));
					shoot_enable2 = 0;
				break;
				default:
				break;
			}

			object_anim();		//Animate every object in the list
			object_colision(&playHit);	//Collide some types of objects with others
			object_move();		//Move the objects
		}

		//	KEYBOARD VERIFICATION
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
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
			switch(ev.keyboard.keycode) {
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
					RIGHT = 1;
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
				case ALLEGRO_KEY_ENTER:
					keys[KEY_ENTER] = false;
				break;
				case ALLEGRO_KEY_ESCAPE:
					if (gameState == 1)
						playMenuSong = true;
					gameState = 0;
				break;
			}
		}

		if (al_is_event_queue_empty(event_queue)) {
			if (playHit) {
				al_play_sample(hit, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				playHit = false;
			}
			if (playMenuSong) {
				al_stop_sample(&game_sound_id);
				al_play_sample(menu_sound, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &menu_sound_id);
				playMenuSong = false;
			}
			if (stopMenuSong) {
				al_stop_sample(&menu_sound_id);
				al_play_sample(game_sound, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &game_sound_id);
				stopMenuSong = false;
			}
			// Local variables for the menus
			int cost[sizeof(UPGRADE) / (sizeof(UPGRADE[0]))];
			DNA_points = get_score() - DNA_spent;
			int width, height, forigin_x=300, forigin_y=500;

			switch(gameState) {
				case 0:			// MENU
					al_draw_bitmap(menu, 0, 0, 0);

					select = (select > 3) ? 3 : select;
					select = (select < 0) ? 0 : select;
					multiState = 0;
					width = al_get_bitmap_width(cursor);
					height = al_get_bitmap_height(cursor);
					// Draw the main menu options
					al_draw_scaled_bitmap(cursor, 0, 0, width, height, forigin_x, forigin_y-9 + 25 * select, width*0.8, height*0.8, 0);
					if(host == true){
						al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y, 0, "RETURN TO GAME");
					}else{
						al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y, 0, "SINGLE-PLAYER");
					}
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y+1*25, 0, "MULTI-PLAYER  ");
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y+2*25, 0, "UPGRADE  ");
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y+3*25, 0, "QUIT  ");

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
						if (gameState == 1)
							stopMenuSong = true;
						keys[KEY_ENTER] = false;
					}
				break;
				case 1: //PLAYING
					background_draw();
					object_draw();
					//Is there a player alive, be one or two?
					if(!player_alive()){
						gameState = 5; // Go to the gameOver screen
						playMenuSong = true;
					}
					p = object_search(1);// p points to player one and display player info
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), 75, 10, 0, "LIFE: %d ", p->life);
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), 275, 10, 0, "SCORE: %d ", get_score()*100);
					al_draw_textf(pressstart_20, al_map_rgb(242, 210, 99), 600, 10, 0, "DNA: %d ", DNA_points);
					//In case of multi-player game
					if(host == true){
						// DATA WRITE
						var.gameState = gameState;
						var.score = get_score();
						p = object_search(2);
						var.life = p->life;
						var.dna = DNA_points;
						memset(data, '\0', BUFLEN);
						for(i = 0,p = object_search(0); (i < BUFLEN / sizeof(Data)) && (p != NULL); p = p->next) {
							if ( (p->type != background) && (p->type != header) ) {
								data[i].img_i = p->img_i;
								data[i].type = p->type;
								data[i].x = p->x;
								data[i].y = p->y;
								data[i].dir = p->dir;
								i++;
							}
						}

						r_receive(keys2);

						d_send(data, var);
					}
				break;
				case 2:			// MULTIPLAYER
					al_draw_bitmap(menu, 0, 0, 0);
					switch(multiState) {
						case 0:			// Menu
							select = (select > 1) ? 1 : select;
							select = (select < 0) ? 0 : select;

							width = al_get_bitmap_width(cursor);
							height = al_get_bitmap_height(cursor);

							al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y, 0, "HOST");
							al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y + 1 * 25, 0, "JOIN  ");
							width = al_get_bitmap_width(cursor);
							height = al_get_bitmap_height(cursor);
							al_draw_scaled_bitmap(cursor, 0, 0, width, height, forigin_x, forigin_y - 9 + 25 * select, width*0.8, height*0.8, 0);

							if (keys[KEY_UP] * UP) {
								select += -1;
								UP = 0;
							}
							if (keys[KEY_DOWN] * DOWN) {
								select += 1;
								DOWN = 0;
							}

							if (keys[KEY_ENTER]) {
								multiState = select + 1;
								keys[KEY_ENTER] = false;
							}
						break;
						case 1:			// Host
							if (!isSet) {
								set_server();
								isSet = true;
								p = player_add("Jefferson", 5, 12);
							}
							host = true;
							gameState = 1;
						break;
						case 2:			// Join
							switch(join){
								case 0:
									//Read the IP address of HOST
									keyboard_read(ev, &ip, sizeof(ip));
									al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x, forigin_y, 0, "IP:%s ", ip);
									al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + 75, forigin_y + 1 * 25, 0, "> CONNECT ");

									if (keys[KEY_ENTER]) {
										if (strcmp(ip, "AIDS") == 0) {
											p = object_search(1);
											p->life = 0;
											gameState = 5;
										}
										else {
											join = 1;
										}
										keys[KEY_ENTER] = false;
									}

								break;
								case 1:
									background_draw();
									// Starts the client socket configuration
									if (!isSet) {
										set_client(&ip);
										isSet = true;
										// Deletes player one, Bye Ronaldo!! You will live in the host game... I Hope..
										p = object_search(1);
										p = object_del(p);
									}
									//Send keyboard info to host
									r_send(keys);

									//Receive bitmaps positions and types from host
									d_receive(data, &var);

									//Draw bitmaps from host on the screen
									for(i = 0; i < BUFLEN / sizeof(Data); i++) {
										if (&data[i] != NULL) {
											if((data[i].type >= background) && (data[i].type <= header)){
											if (data[i].type != header && data[i].type != background) {
												al_draw_bitmap(sprites[data[i].type][data[i].img_i], data[i].x, data[i].y, data[i].dir);
											}
											}
										}
									}
									//Player info:
									al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), 75, 10, 0, "LIFE: %d ", var.life);
									al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), 275, 10, 0, "SCORE: %d ", var.score*100);
									al_draw_textf(pressstart_20, al_map_rgb(242, 210, 99), 600, 10, 0, "DNA: %d ", var.dna);
									//In case of death
									if(var.gameState == 5){
										gameState = 5;
									}
								break;

							}


						break;
					}
				break;
				case 3://UPGRADES
					al_draw_bitmap(menu, 0, 0, 0);
					select = (select > (sizeof(UPGRADE) / (sizeof(UPGRADE[0]))) - 1) ? (sizeof(UPGRADE) / (sizeof(UPGRADE[0]))) - 1 : select;
					select = (select < 0) ? 0 : select;
					cost[0] = UPGRADE[0] * 10;
					cost[1] = UPGRADE[1] * 5;
					cost[2] = UPGRADE[2] * 20;

					width = al_get_bitmap_width(cursor);
					height = al_get_bitmap_height(cursor);

					// Draw Menus
					al_draw_textf(pressstart_20, al_map_rgb(242, 210, 99), forigin_x-200, forigin_y, 0, "DNA: %d ", DNA_points);
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y, 0, "TRIGGER: %d", 11 - bulletFreq);
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y + 1 * 25, 0, "FORCE: %d", -normal.life);
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), forigin_x + width, forigin_y + 2 * 25, 0, "BULLET: %d", bullet_type);
					width = al_get_bitmap_width(cursor);
					height = al_get_bitmap_height(cursor);
					al_draw_scaled_bitmap(cursor, 0, 0, width, height, forigin_x, forigin_y - 9 + 25 * select, width*0.8, height*0.8, 0);

					for(i = 0; i < sizeof(UPGRADE) / (sizeof(UPGRADE[0])); i++) {
						al_draw_textf(pressstart_20, al_map_rgb(242, 210, 99), forigin_x+300, forigin_y + i * 25, 0, " %d ", cost[i]);
					}
					if (keys[KEY_UP] * UP) {
						select += -1;
						UP = 0;
					}
					if (keys[KEY_DOWN] * DOWN) {
						select += 1;
						DOWN = 0;
					}
					if (keys[KEY_RIGHT] * RIGHT * (DNA_points >= cost[select])) {
						DNA_spent += cost[select];
						UPGRADE[select] += 1;
						RIGHT = 0;
					}

					UPGRADE[0] = (UPGRADE[0] > 10) ? 10 : UPGRADE[0];
					bulletFreq = 10 - (UPGRADE[0] - 1);
					normal.life = -UPGRADE[1];
					UPGRADE[2] = (UPGRADE[2] > 3) ? 3 : UPGRADE[2];
					bullet_type = UPGRADE[2];

				break;
				case 4:

					quit = true;
				break;

				case 5:
					// You are dead my friend!!!
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), DISPLAY_W / 2, DISPLAY_H / 2 - 20, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
					al_draw_textf(pressstart_20, al_map_rgb(255, 255, 255), DISPLAY_W / 2, DISPLAY_H / 2 + 5, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER TO CONTINUE");

					// Reset the game when you get over it...
					if (keys[KEY_ENTER]) {
						game_reset();
						gameState = 0;
						multiState = 0;
						host = 0;
						for(i = 0; i < sizeof(UPGRADE) / (sizeof(UPGRADE[0])); i++) {
							UPGRADE[i] = 1;
						}
						UPGRADE[0] = (UPGRADE[0] > 10) ? 10 : UPGRADE[0];
						bulletFreq = 10 - (UPGRADE[0] - 1);
						normal.life = -UPGRADE[1];
						bullet_type = UPGRADE[2];
						DNA_spent = 0;
						p = player_add("Ronaldo", 5, 12);
						keys[KEY_ENTER] = false;
					}
					break;
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

//Destroy everything that was created, like an apocalypse
	for(i = 0; i < header; i++){
		for(j = 0; j < 20; j++){
				al_destroy_bitmap(sprites[i][j]);
				//free(masks[i][j]);
		}
	}
	list_destroy();
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(pressstart_20);
	al_destroy_sample(sega_sound);
	al_destroy_sample(menu_sound);
	al_destroy_sample(game_sound);
	al_destroy_sample(shoot);
	al_destroy_sample(hit);

	exit(EXIT_SUCCESS);
}
