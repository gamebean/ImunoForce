#define DISPLAY_H 600
#define DISPLAY_W 800
#define MAX_BULLETS 25


enum {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_MAX
};
bool keys[KEY_MAX];

// GLOBALS
int i, draw_flag=0, frame=1, bTrig=10, bulletFreq=10;


typedef struct {
	int x;
	int y;
	ALLEGRO_BITMAP* img;
	bool live;
}Object;

typedef struct{
	int id;

	int x;
	int y;

	struct Bllt *next;
	struct Bllt *prev; /*prev sera utilizado no bullet_del*/
}Bllt;


Bllt bullet_head = {0,0,0, NULL, NULL };
Bllt *bullet;

Bllt *bullet_add(Bllt *p, int id)	{
	Bllt *a;
	p = (Bllt *)malloc(sizeof(Bllt)); /*Aloca p na memoria*/
	p->id = id;
	p->next = NULL;
	if (bullet_head.next == NULL){
		bullet_head.next = p;
		p->prev = &bullet_head;
	}
	else{
		for (a = &bullet_head; a->next != NULL; a = a->next){} /* a vira ponteiro do ultimo Bllt da lista*/
		a->next = p;
		p->prev = a;
	}
	return p;
}

Bllt *bullet_search(int id){
	Bllt *a;
	for (a = &bullet_head; a->id != id; a = a->next){
		if (a->next == NULL)
			return NULL;
	}
	return a;
}

void bullet_del(int id){
	Bllt *a;
	Bllt *prev;
	Bllt *next;

	a = bullet_search(id);
	prev = a->prev;
	next = a->next;
	next->prev = prev->prev;
	prev->next = next->next;

	free(a);
}


void initialization() {
	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}
	if (!al_init_image_addon()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init_image_addon() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}
	if (!al_install_keyboard()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_install_keyboard() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}
	if (!al_init_primitives_addon()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init_primitives_addon() failed", NULL, 0);
		exit(EXIT_FAILURE);
	}
}

//void creation(ALLEGRO_DISPLAY* &display, ALLEGRO_TIMER* &timer, ALLEGRO_EVENT_QUEUE* &event_queue) {
//	display = al_create_display(DISPLAY_W, DISPLAY_H);
//	if (!display) {
//		al_show_native_message_box(NULL, NULL, NULL,
//								   "al_create_display() failed", NULL, NULL);
//		exit(EXIT_FAILURE);
//	}
//	timer = al_create_timer(1 / 60.0);
//	if (!timer) {
//		al_show_native_message_box(NULL, NULL, NULL,
//								   "al_create_timer() failed", NULL, NULL);
//		exit(EXIT_FAILURE);
//	}
//	event_queue = al_create_event_queue();
//	if (!event_queue) {
//		al_show_native_message_box(NULL, NULL, NULL,
//								   "al_create_event_queue() failed", NULL, NULL);
//		exit(EXIT_FAILURE);
//	}
//}

//void move_player(Object &player) {
//	if (keys[KEY_UP]) {
//		player.y -= 3;
//	}
//	if (keys[KEY_DOWN]) {
//		player.y += 3;
//	}
//	if (keys[KEY_LEFT]) {
//		player.x -= 3;
//		draw_flag = 0;
//	}
//	if (keys[KEY_RIGHT]) {
//		player.x += 3;
//		draw_flag = ALLEGRO_FLIP_HORIZONTAL;
//	}
//}

//void limit_player_move(Object &player) {
//	if (player.y <= 0) {
//		player.y = 0;
//		keys[KEY_UP] = false;
//	}
//	if (player.y >= DISPLAY_H - 64) {
//		player.y = DISPLAY_H - 64;
//		keys[KEY_DOWN] = false;
//	}
//	if (player.x <= 0) {
//		player.x = 0;
//		keys[KEY_LEFT] = false;
//	}
//	if (player.x >= DISPLAY_W - 28) {
//		player.x = DISPLAY_W - 28;
//		keys[KEY_RIGHT] = false;
//	}
//}

//void fire_bullet(/*Object bullet[],*/ Object &player) {
//	/*for (i = 0; i < MAX_BULLETS; i++) {
//				fire_bullet v1
//		if (keys[KEY_SPACE] && !bullet[i].live && frame % 10 == 0) {
//			bullet[i].x = player.x + 14;
//			bullet[i].y = player.y;
//			bullet[i].live = true;
//			break;
//		}
//
//				fire_bullet v2
//		if (keys[KEY_SPACE] && !bullet[i].live && bTrig == 10) {
//			bullet[i].x = player.x + 14;
//			bullet[i].y = player.y;
//			bullet[i].live = true;
//			bTrig = frame % bulletFreq;
//			break;
//		}
//		else if (keys[KEY_SPACE] && !bullet[i].live && frame % bulletFreq == bTrig) {
//			bullet[i].x = player.x + 14;
//			bullet[i].y = player.y;
//			bullet[i].live = true;
//			break;
//		}
//		else if (!keys[KEY_SPACE]) {
//			bTrig = 10;
//		}
//	}*/
//
//	int x=1;
//
//	if (keys[KEY_SPACE] && bTrig == 10) {
//		while (bullet_search(x) != NULL) 
//			x++;
//		bullet = bullet_add(bullet, x);
//		bullet->x = player.x + 14;
//		bullet->y = player.y;
//		bTrig = frame % bulletFreq;
//	}
//	else if (keys[KEY_SPACE] && frame%bulletFreq == bTrig) {
//		while (bullet_search(x) != NULL)
//			x++;
//		bullet = bullet_add(bullet, x);
//		bullet->x = player.x + 14;
//		bullet->y = player.y;
//	}
//	else if (!keys[KEY_SPACE]) {
//		bTrig = 10;
//	}
//}

//void keyboard_verification(ALLEGRO_EVENT &ev) {
//	if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
//		switch (ev.keyboard.keycode) {
//			case ALLEGRO_KEY_UP:
//				keys[KEY_UP] = true;
//				break;
//			case ALLEGRO_KEY_DOWN:
//				keys[KEY_DOWN] = true;
//				break;
//			case ALLEGRO_KEY_LEFT:
//				keys[KEY_LEFT] = true;
//				break;
//			case ALLEGRO_KEY_RIGHT:
//				keys[KEY_RIGHT] = true;
//				break;
//			case ALLEGRO_KEY_SPACE:
//				keys[KEY_SPACE] = true;
//				break;
//		}
//	}
//	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
//		switch (ev.keyboard.keycode) {
//			case ALLEGRO_KEY_UP:
//				keys[KEY_UP] = false;
//				break;
//			case ALLEGRO_KEY_DOWN:
//				keys[KEY_DOWN] = false;
//				break;
//			case ALLEGRO_KEY_LEFT:
//				keys[KEY_LEFT] = false;
//				break;
//			case ALLEGRO_KEY_RIGHT:
//				keys[KEY_RIGHT] = false;
//				break;
//			case ALLEGRO_KEY_SPACE:
//				keys[KEY_SPACE] = false;
//				break;
//		}
//	}
//}