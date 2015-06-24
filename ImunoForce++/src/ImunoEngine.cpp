#include "ImunoEngine.h"
#include "AllegroDef.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>

using namespace std;

const int vel_max = 15;
const int e_vel_max = 3;


// MASKS

Mask::Mask(ALLEGRO_BITMAP* bitmap) {
	width = al_get_bitmap_width(bitmap);
	height = al_get_bitmap_height(bitmap);

	ALLEGRO_COLOR pixel;

	bits = new
}

void Mask::mask_create(int width, int height) {
	int i;
	bits = new int(width);
}