#include <stdio.h>
#include "ImunoEngine.h"
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "AllegroDef.h"

const int vel_max = 15;
const int e_vel_max = 3;

int PLAYER_COUNT = 0;
int SCORE = 0;

Object object_head = { 0, header, "header" };

Object *object_add(Type t, int tag) {
	Object *p;
	Object *a;
	p = (Object *) malloc(sizeof(Object)); /*Aloca p na memoria*/
	p->tag = tag;
	p->next = NULL;
	p->type = t;
	p->dir = 0; // 0 = normal ; 1 = ALLEGRO_FLIP_HORIZONTAL

	if (object_head.next == NULL) {
		object_head.next = p;
		p->prev = &object_head;
	} else {
		for(a = &object_head; a->next != NULL; a = a->next)
			; /* a vira ponteiro do ultimo Object da objecta*/
		a->next = p;
		p->prev = a;
	}
	return p;
}

Object *
object_search(int tag) {
	Object *a;
	for(a = &object_head; a->tag != tag; a = a->next) {
		if (a->next == NULL)
			return NULL;
	}
	return a;
}

Object *
object_del(Object *a) {
	Object *prev;
	Object *next;
	if (a != NULL) {
		prev = a->prev;
		next = a->next;
		if (next != NULL) {
			next->prev = prev;
		}
		if (prev != NULL) {
			prev->next = next;
		}
		free(a);
		return prev;
	} else {
		return NULL;
	}
}

Object *
player_add(char player_name[], int frame_delay, int vector_size) {
	PLAYER_COUNT++;
	Object *p;
	switch(PLAYER_COUNT) {
		case 1:
			p = object_add(player, PLAYER_COUNT);
			p->img_delay = 0;
			p->img_i = 0;
			p->life = 3;
			p->height = al_get_bitmap_height(sprites[player][p->img_i]);
			p->width = al_get_bitmap_width(sprites[player][p->img_i]);
		break;
		case 2:
			p = object_add(player2, PLAYER_COUNT);
			p->img_delay = 0;
			p->img_i = 0;
			p->life = 3;
			p->height = al_get_bitmap_height(sprites[player2][p->img_i]);
			p->width = al_get_bitmap_width(sprites[player2][p->img_i]);
		break;
		default:
			exit(EXIT_FAILURE);
			break;
	}


	p->frame_delay = frame_delay;
	p->vector_size = vector_size;

	strcpy_s(p->String, sizeof(p->String), player_name);
	//strcpy(p->String, player_name);
	p->x = DISPLAY_W / 2 - p->width / 2;
	p->y = DISPLAY_H / 2 - p->height / 2;

	return p;
}

Object *
bullet_add(Object bullet_type_, Object *p) {
	Object *bllt;

	bllt = object_add(bullet, -1);
	bllt->img_delay = 0;
	bllt->img_i = 0;
	bllt->height = bullet_type_.height; //al_get_bitmap_height(bllt->img);
	bllt->width = bullet_type_.width; //al_get_bitmap_width(bllt->img);
	bllt->x = p->x + p->width / 2 - bllt->width / 2;
	bllt->vx = bullet_type_.vx + (0.35 - (float) (rand() % 70) / 100.0); // Uncertainty principle
	bllt->vy = bullet_type_.vy; // +(0.35 - (float)(rand() % 36) / 10.0); // Uncertainty principle
	bllt->y = p->y + ((bllt->vy > 0) ? p->height : -bllt->height);
	bllt->frame_delay = bullet_type_.frame_delay;
	bllt->vector_size = bullet_type_.vector_size;
	bllt->life = bullet_type_.life;

	return bllt;
}

Object *
enemy_add(Object enemy_type, int x, int y) {
	int tag = -2;

	Object *e; // e for enemy!!!! If this dont work I gonna kill my sister!!!!
	e = object_add(enemy_type.type, tag);
	e->img_delay = 0;
	e->img_i = 0;
	e->height = enemy_type.height; //al_get_bitmap_height(e->img);
	e->width = enemy_type.width; //al_get_bitmap_width(e->img);
	e->x = x;
	e->vx = enemy_type.vx; //+ (1 - (rand() % 2)); // Uncertainty principle
	e->vy = enemy_type.vy; //+ (1 - (rand() % 2)); // Uncertainty principle
	e->y = y;
	e->frame_delay = enemy_type.frame_delay;
	e->vector_size = enemy_type.vector_size;
	e->life = enemy_type.life;
	//strcpy(e->String, enemy_type.String);
	strcpy_s(e->String, sizeof(e->String), enemy_type.String);
	return e;
}

Object *
background_add(int x, int y) {
	int tag = -3;

	Object *bg;
	bg = object_add(background, tag);
	bg->img_delay = 0;
	bg->img_i = 0;
	bg->height = al_get_bitmap_height(sprites[background][bg->img_i]);
	bg->width = al_get_bitmap_width(sprites[background][bg->img_i]);
	bg->x = x;
	bg->vx = 0;
	bg->vy = 8;
	bg->y = y;
	bg->frame_delay = 0;
	bg->vector_size = 1;
	bg->life = -1;

	return bg;
}

void *
object_colision() {
	Object *p;
	Object *ob;
	int x, y;
	int top, bottom, left, right;
	int p_count;
	int bullet_life;
	for(p = &object_head; (p != NULL); p = p->next) {
		test: switch(p->type) {
			case player:
			case player2:
				if (p->y <= 0) {
					p->y = 0;
					//keys[KEY_UP] = false;
				} else if (p->y >= DISPLAY_H - p->height) {
					p->y = DISPLAY_H - p->height;
					//keys[KEY_DOWN] = false;
				}
				if (p->x <= 0) {
					p->x = 0;
					//keys[KEY_LEFT] = false;
				} else if (p->x >= DISPLAY_W - p->width) {
					p->x = DISPLAY_W - p->width;
					//keys[KEY_RIGHT] = false;
				}
				if (p->life <= 0) {
					p = object_del(p);
				}
			break;

			case bullet:
				if ((p->y < 0) || p->y > DISPLAY_H + p->height) {
					p = object_del(p);
					goto test;
				}

				for(ob = &object_head; (ob != NULL); ob = ob->next) {
					//ob = object_search(p_count);
					if (enemy_all(ob->type)) {

						top = (p->y > ob->y) ? p->y : ob->y;
						bottom = (p->y + p->height < ob->y + p->height) ? p->y + p->height : ob->y + ob->height;
						left = (p->x > ob->x) ? p->x : ob->x;
						right = (p->x + p->width < ob->x + ob->width) ? p->x + p->width : ob->x + ob->width;

						for(x = left; x < right; x++) {
							for(y = top; y < bottom; y++) {
								if ((masks[p->type][p->img_i])->bits[(int) (x - p->x)][(int) (y - p->y)] == 1
										&& (masks[ob->type][ob->img_i])->bits[(int) (x - ob->x)][(int) (y - ob->y)] == 1) {
									bullet_life = p->life;
									bullet_life += ob->life;

									ob->life += p->life;
									p->life = bullet_life;
									if (ob->life < 0) {
										ob = object_del(ob);
										SCORE++;
									}
									if (p->life >= 0) {
										p = object_del(p);
									}
									goto test;
								}
							}
						}
					}
				}
			break;
			case_enemy_all
			if(p->y > DISPLAY_H + 50)
			{
				p = object_del(p);
				goto test;
			}
			for(ob = &object_head; (ob != NULL); ob = ob->next) {
				//ob = object_search(p_count);
				if ((ob->type == player) || (ob->type == player2)) {

					top = (p->y > ob->y) ? p->y : ob->y;
					bottom = (p->y + p->height < ob->y + p->height) ? p->y + p->height : ob->y + ob->height;
					left = (p->x > ob->x) ? p->x : ob->x;
					right = (p->x + p->width < ob->x + ob->width) ? p->x + p->width : ob->x + ob->width;

					for(x = left; x < right; x++) {
						for(y = top; y < bottom; y++) {
							if ((masks[p->type][p->img_i])->bits[(int) (x - p->x)][(int) (y - p->y)] == 1
									&& (masks[ob->type][ob->img_i])->bits[(int) (x - ob->x)][(int) (y - ob->y)] == 1) {
								p = object_del(p);
								ob->life += -1;
								goto test;
							}
						}
					}
				}
			}
			break;
		}
	}
	return 0;
}

void *
object_draw() {
	Object *p;
	for(p = &object_head; (p != NULL); p = p->next) {
		if (p != &object_head && p->type != background) {
			al_draw_bitmap(sprites[p->type][p->img_i], (int) p->x, (int) p->y, p->dir);
			//mask_draw(masks[p->type][p->img_i],p->x,p->y);
		}

	}
	return 0;
}

void background_draw() {
	Object *p;

	for(p = &object_head; p != NULL; p = p->next) {
		if (p->type == background) {
			al_draw_bitmap(sprites[p->type][p->img_i], (int) p->x, (int) p->y, 0);
		}
	}
}

void *object_move() {
	Object *p;
	Object *pl;
	float dx, dy;
	for(p = &object_head; (p != NULL); p = p->next) {
		switch(p->type) {
			case player:
			case player2:
				p->x += p->vx;
				p->y += p->vy;
				if (p->vx > vel_max)
					p->vx = vel_max;
				if (p->vy > vel_max)
					p->vy = vel_max;

				if (p->vx < -vel_max)
					p->vx = -vel_max;
				if (p->vy < -vel_max)
					p->vy = -vel_max;

				p->vx = p->vx * 0.90;
				p->vy = p->vy * 0.90;

			break;

			case bullet:

				p->x += p->vx;
				p->y += p->vy;
			break;

			case_enemy_all

if			(!strcmp(p->String, "Seeker")) {
				pl = object_search(1);
				if (pl != NULL) {
					dx = (pl->x - p->x) / 10;
					dy = (pl->y - p->y) / 10;
					p->vx += (dx > 0) ? ((dx * dx) / 300 < 0.3) ? (dx * dx) / 300 : 0.3 : ((dx * dx) / 300 < 0.3) ? -(dx * dx) / 300 : -0.3;
					p->vy += (float) dy / 100;
				}

				if (p->vx > e_vel_max)
				p->vx = e_vel_max;
				if (p->vy > e_vel_max)
				p->vy = e_vel_max;
				if (p->vx < -e_vel_max)
				p->vx = -e_vel_max;
				if (p->vy < -e_vel_max)
				p->vy = -e_vel_max;
			}
			p->x += p->vx;
			p->y += p->vy;
			p->dir = (p->vx < 0) ? ALLEGRO_FLIP_HORIZONTAL : 0;
			break;
			case background:
			p->y += p->vy;
			if (p->y >= DISPLAY_H)
			p->y = -DISPLAY_H;
			break;
			default:
			break;
		}
	}
	return 0;
}

Mask *
mask_new(ALLEGRO_BITMAP *btm) {
	Mask *temp;
	int x, y;
	int width = al_get_bitmap_width(btm);
	int height = al_get_bitmap_height(btm);

	//ALLEGRO_COLOR tansColor = al_map_rgb(0,0,0); //Bitmap Backgroud color
	ALLEGRO_COLOR pixel;

	temp = mask_create(width, height);

	if (!temp)
		return NULL;

	mask_clear(temp);

	for(x = 0; x < width; x++) {
		for(y = 0; y < height; y++) {
			pixel = al_get_pixel(btm, x, y);
			if (pixel.a != 0) {
				temp->bits[x][y] = 1;
			}
		}
	}

	return temp;
}

Mask *
mask_create(int width, int height) {
	int i;
	Mask *temp = (Mask *) malloc(sizeof(Mask));
	temp->widht = width;
	temp->height = height;

	temp->bits = (int **) malloc(width * sizeof(int *));
	for(i = 0; i < width; i++) {
		temp->bits[i] = (int *) malloc(height * sizeof(int));
	}

	if (!temp)
		return NULL;

	return temp;

}

void *
mask_clear(Mask *m) {
	int x, y;
	for(x = 0; x < m->widht; x++) {
		for(y = 0; y < m->height; y++) {
			m->bits[x][y] = 0;
		}
	}
	return 0;
}

void *
mask_draw(Mask *temp, int x, int y) {
	int j, k;
	for(j = 0; j < temp->widht; j++) {
		for(k = 0; k < temp->height; k++) {
			if (!temp->bits[j][k])
				al_put_pixel(x + j, y + k, al_map_rgba_f(0.75, 0, 0.75, 0.75));
		}
	}
	return 0;
}

void object_track() {
	Object *p;
	system("cls");
	int o, pl, b, e;
	o = 0;
	pl = 0;
	b = 0;
	e = 0;

	for(p = &object_head; (p != NULL); p = p->next) {
		o++;
		switch(p->type) {
			case player:
				pl++;
			break;
			case bullet:
				b++;
			break;
			case_enemy_all
			e++;
			break;
			default:
			break;
		}
	}

	printf("There is %d Objects,\n%d Players\n%d Bullet's\n%d Enemies\n", o, pl, b, e);
	for(p = &object_head; (p != NULL); p = p->next) {
		printf("Object type:%d\n    x = %.2f\n    y = %.2f \n ", p->type, p->x, p->y);
	}
}

int anim(Object *object, int frame_delay, int vector_size) {
	if (object->img_delay++ >= frame_delay) {
		object->img_delay = 0;
		object->img_i = (object->img_i >= vector_size - 1) ? 0 : object->img_i + 1;
		return 0;
	} else {
		return -1;
	}
}

void object_anim() {
	Object *p;
	for(p = &object_head; (p != NULL); p = p->next) {
		if (p->type == player) {
			if (keys[KEY_UP]) {						// FORWARD
				if (keys[KEY_LEFT]) {			// LEFT
					p->img_i = F_L;
				} else if (keys[KEY_RIGHT]) {		//RIGHT
					p->img_i = F_R;
				} else {						// CENTER
					p->img_i = F_C;
				}
			} else if (keys[KEY_DOWN]) {				// BREAKE
				if (keys[KEY_LEFT]) {			// LEFT
					p->img_i = B_L;
				} else if (keys[KEY_RIGHT]) {		// RIGHT
					p->img_i = B_R;
				} else {						// CENTER
					p->img_i = B_C;
				}
			} else {							// STAND
				if (keys[KEY_LEFT]) {			// LEFT
					p->img_i = S_L;
				} else if (keys[KEY_RIGHT]) {		// RIGHT
					p->img_i = S_R;
				} else {						// CENTER
					p->img_i = S_C;
				}
			}
		} else if (p->type == player2) {
			if (keys2[KEY_UP]) {						// FORWARD
				if (keys2[KEY_LEFT]) {			// LEFT
					p->img_i = F_L;
				} else if (keys[KEY_RIGHT]) {		//RIGHT
					p->img_i = F_R;
				} else {						// CENTER
					p->img_i = F_C;
				}
			} else if (keys2[KEY_DOWN]) {				// BREAKE
				if (keys2[KEY_LEFT]) {			// LEFT
					p->img_i = B_L;
				} else if (keys[KEY_RIGHT]) {		// RIGHT
					p->img_i = B_R;
				} else {						// CENTER
					p->img_i = B_C;
				}
			} else {							// STAND
				if (keys2[KEY_LEFT]) {			// LEFT
					p->img_i = S_L;
				} else if (keys2[KEY_RIGHT]) {		// RIGHT
					p->img_i = S_R;
				} else {						// CENTER
					p->img_i = S_C;
				}
			}
		} else if (p != &object_head) {
			anim(p, p->frame_delay, p->vector_size);
		}
	}
}

#ifdef __linux__
void strcpy_s(char a[], int b, char c[]) {
	strcpy(a, c);
}
#endif

int get_score() {
	return SCORE;
}
int enemy_count() {
	Object *p;
	int e = 0;
	for(p = &object_head; (p != NULL); p = p->next) {
		if (enemy_all(p->type)) {
			if (strcmp(p->String, "Wall")) {
				e++;
			}
		}
	}
	return e;
}
int object_find(char s[]) {
	Object *p;

	for(p = &object_head; (p != NULL); p = p->next) {
		if (!strcmp(p->String, "Wall")) {
			return 1;
		}
	}
	return 0;
}
