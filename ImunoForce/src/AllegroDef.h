/*
 * AllegroDef.h
 *
 *  Created on: 07/06/2015
 *      Author's: Bruno Pacheco & Felipe Sens Bonetto
 */
#include <allegro5/allegro.h>

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

// GLOBALS
//int i, draw_flag=0, frame=1, bTrig=10, bulletFreq=10;


void initialization();
