#include "ImunoEngine.h"
//#include "AllegroDef.h"
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

	*bits = new int[width];

	for (int i = 0; i < width; i++) {
		bits[i] = new int[height];
	}
	
	this->clear_bits();

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (pixel.a != 0) {
				bits[i][j] = 1;
			}
		}
	}
}

void Mask::clear_bits() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			bits[i][j] = 0;
		}
	}
}

void Mask::draw(int x, int y) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (!bits[i][j])
				al_put_pixel(x + i, y + j, al_map_rgba_f(0.75, 0, 0.75, 0.75));
		}
	}
}