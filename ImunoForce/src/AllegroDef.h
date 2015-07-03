#include <allegro5/allegro.h>

#define __allegro__
#define DISPLAY_H 800
#define DISPLAY_W 800
#define MAX_BULLETS 25
#define true 1
#define false 0
enum {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_ENTER,
	KEY_MAX
};
bool keys[KEY_MAX];
bool keys2[KEY_MAX];

void initialization();
