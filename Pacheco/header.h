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


int i, draw_flag=0, frame=1, bTrig=10, bulletFreq=10;


typedef struct {
	int x;
	int y;
	ALLEGRO_BITMAP* img;
	bool live;
}Object;


void initialization() {
	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init() failed", NULL, NULL);
		exit(EXIT_FAILURE);
	}
	if (!al_init_image_addon()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init_image_addon() failed", NULL, NULL);
		exit(EXIT_FAILURE);
	}
	if (!al_install_keyboard()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_install_keyboard() failed", NULL, NULL);
		exit(EXIT_FAILURE);
	}
	if (!al_init_primitives_addon()) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_init_primitives_addon() failed", NULL, NULL);
		exit(EXIT_FAILURE);
	}
}

void creation(ALLEGRO_DISPLAY* &display, ALLEGRO_TIMER* &timer, ALLEGRO_EVENT_QUEUE* &event_queue) {
	display = al_create_display(DISPLAY_W, DISPLAY_H);
	if (!display) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_create_display() failed", NULL, NULL);
		exit(EXIT_FAILURE);
	}
	timer = al_create_timer(1 / 60.0);
	if (!timer) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_create_timer() failed", NULL, NULL);
		exit(EXIT_FAILURE);
	}
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(NULL, NULL, NULL,
								   "al_create_event_queue() failed", NULL, NULL);
		exit(EXIT_FAILURE);
	}
}

void movePlayer(Object &player) {
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
}

void limitPlayerMove(Object &player) {
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
}

void fireBullet(Object bullet[], Object &player) {
	for (i = 0; i < MAX_BULLETS; i++) {
		//if (keys[KEY_SPACE] && !bullet[i].live /*&& frame % 10 == 0*/) {
		//	bullet[i].x = player.x + 14;
		//	bullet[i].y = player.y;
		//	bullet[i].live = true;
		//	break;
		//}
		if (keys[KEY_SPACE] && !bullet[i].live && bTrig == 10) {
			bullet[i].x = player.x + 14;
			bullet[i].y = player.y;
			bullet[i].live = true;
			bTrig = frame % bulletFreq;
			break;
		}
		else if (keys[KEY_SPACE] && !bullet[i].live && frame % bulletFreq == bTrig) {
			bullet[i].x = player.x + 14;
			bullet[i].y = player.y;
			bullet[i].live = true;
			break;
		}
		else if (!keys[KEY_SPACE]) {
			bTrig = 10;
		}
	}
}

void keyboardVerification(ALLEGRO_EVENT &ev) {
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