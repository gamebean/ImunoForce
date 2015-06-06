//#include <stdio.h>
//#include <stdlib.h>
//#include <allegro5\allegro.h>
//#include <allegro5\allegro_native_dialog.h>
//#include <allegro5\allegro_image.h>
//#include <allegro5\allegro_primitives.h>
//#include "header.h"
//
//
//int main() {
//	ALLEGRO_DISPLAY*			display;
//	ALLEGRO_TIMER*				timer;
//	ALLEGRO_EVENT				ev;
//	ALLEGRO_EVENT_QUEUE*		event_queue;
//
//	bool quit = false;
//
//	Object player;
//	player.x = DISPLAY_W / 2 - 14;
//	player.y = DISPLAY_H / 2 - 32;
//
//	/*Object bullet[MAX_BULLETS];
//	for (i = 0; i < MAX_BULLETS; i++) {
//		bullet[i].live = false;
//	}*/
//
//	initialization();
//
//	creation(display, timer, event_queue);
//
//	// IMAGES
//	player.img = al_load_bitmap("Sprites/sperm_0M.png");
//
//	//	EVENTS
//	al_register_event_source(event_queue, al_get_display_event_source(display));
//	al_register_event_source(event_queue, al_get_timer_event_source(timer));
//	al_register_event_source(event_queue, al_get_keyboard_event_source());
//
//	//	TIMER
//	al_start_timer(timer);
//
//
//	//	MAIN LOOP
//	while (!quit) {
//		al_wait_for_event(event_queue, &ev);
//
//		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
//			quit = true;
//		}
//
//		if (ev.type == ALLEGRO_EVENT_TIMER) {
//			//	FRAME COUNT
//			frame = (frame >= 60) ? 1 : frame + 1;
//
//			//	LIMIT COLISSION
//			limit_player_move(player);
//			
//			//	MOVEMENT
//			move_player(player);
//
//			//	FIRE
//			fire_bullet(player);
//
//
//			//	DRAW
//			/*		bullets v1
//			for (i = 0; i < MAX_BULLETS; i++) {
//				if (bullet[i].live) {
//					al_draw_filled_circle(bullet[i].x, bullet[i].y, 5, al_map_rgb(255, 0, 255));
//					bullet[i].y -= 10;
//					if (bullet[i].y < 0) {
//						bullet[i].live = false;
//					}
//				}
//			}*/
//
//			for (i = 1; bullet_search(i) != NULL; i++) {
//				bullet = bullet_search(i);
//				al_draw_filled_circle(bullet->x, bullet->y, 5, al_map_rgb(255, 0, 255));
//				bullet->y -= 10;
//				if (bullet->y < 0) {
//					bullet_del(i);
//				}
//			}
//
//			al_draw_bitmap(player.img, player.x, player.y, draw_flag);
//
//			al_flip_display();
//			al_clear_to_color(al_map_rgb(0,0,0));
//		}
//
//		//	KEYBOARD VERIFICATION
//		keyboard_verification(ev);
//	}
//
//	al_destroy_display(display);
//	al_destroy_timer(timer);
//	al_destroy_event_queue(event_queue);
//	al_destroy_bitmap(player.img);
//
//	exit(EXIT_SUCCESS);
//}