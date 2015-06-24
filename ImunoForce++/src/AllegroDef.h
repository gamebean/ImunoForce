#include <allegro5/allegro.h>

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
int keys[KEY_MAX];

// GLOBALS
//int i, draw_flag=0, frame=1, bTrig=10, bulletFreq=10;


void initialization();