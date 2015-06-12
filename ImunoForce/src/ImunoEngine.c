/*
 * ImunoEngine.c
 *
 *  Created on: 06/06/2015
 *      Author: felipe
 */
#include <stdio.h>
#include "ImunoEngine.h"
#include "AllegroDef.h"
#include <allegro5/allegro_primitives.h>


Object object_head = {0,header,NULL,NULL,NULL,NULL};

Object *object_add(Object *p,Type t, int tag)
{
    Object *a;
    p = (Object *)malloc(sizeof(Object)); /*Aloca p na memoria*/
    p->tag = tag;
    p->next = NULL;
    p->type = t;
    switch(t){
    case player:
			p->player = (Player *)malloc(sizeof(Player));
			p->bullet = NULL;
			p->enemy = NULL;
		break;
    case bullet:
			p->player = NULL;
			p->bullet = (Bullet *)malloc(sizeof(Bullet));
			p->enemy = NULL;
		break;
    case enemy:
			p->player = NULL;
			p->bullet = NULL;
			p->enemy = (Enemy *)malloc(sizeof(Enemy));
    	break;
    case header:
    	default:
			p->player = NULL;
			p->bullet = NULL;
			p->enemy  = NULL;
    	 break;

    }
    if(object_head.next == NULL){
        object_head.next = p;
        p->prev = &object_head;
    }
    else{
        for(a = &object_head; a->next != NULL; a = a->next){} /* a vira ponteiro do ultimo Object da objecta*/
        a->next = p;
        p->prev = a;
    }
    return p;
}

Object *object_search(int tag){
    Object *a;
    for(a = &object_head; a->tag != tag; a = a->next){
        if(a->next == NULL)
            return NULL;
    }
    return a;
}

Object *object_del(Object *a){
	Object *prev;
	Object *next;
	if (a != NULL){
		prev = a->prev;
		next = a->next;
		if(next != NULL){
			next->prev = prev;
		}
		if(prev != NULL){
			prev->next = next;
		}
//		Free every possible element in the struct
		if(a->player != NULL){
			free(a->player);
		}
		if(a->bullet != NULL){
			free(a->bullet);
		}
		if(a->enemy != NULL){
			free(a->enemy);
		}
		free(a);
		return prev;
	}
	else {
		return NULL;
	}
}

Object *player_add(Object *p,char bitmap[]){
	int tag = 1;

	p = object_add(p,player,tag);
	p->player->img = al_load_bitmap(bitmap);
	p->player->mask =  mask_new(p->player->img);
	p->player->height = al_get_bitmap_height(p->player->img);
	p->player->width = al_get_bitmap_width(p->player->img);

	p->player->x = DISPLAY_W / 2 - p->player->width/2 ;
	p->player->y = DISPLAY_H / 2 - p->player->height/2;

	return p;
}

Object *bullet_add(Object *bllt,int player_tag, char bitmap[], Mask *b){
	Object *p;
	p = object_search(player_tag);
	bllt = object_add(bllt, bullet,8);

	bllt->bullet->img = al_load_bitmap(bitmap);
	bllt->bullet->mask = b;
	bllt->bullet->height = al_get_bitmap_height(bllt->bullet->img);
	bllt->bullet->width = al_get_bitmap_width(bllt->bullet->img);
	bllt->bullet->x = p->player->x + p->player->width/2 - bllt->bullet->width/2;
	bllt->bullet->y = p->player->y;
	bllt->bullet->vx = 0;
	bllt->bullet->vy = -10;

	return bllt;
}

Object *enemy_add(Object *p,char bitmap[]){
	int tag = 1;

	p = object_add(p,enemy,tag);
	p->enemy->img = al_load_bitmap(bitmap);
	p->enemy->mask =  mask_new(p->enemy->img);
	p->enemy->height = al_get_bitmap_height(p->player->img);
	p->enemy->width = al_get_bitmap_width(p->player->img);

	p->enemy->x = DISPLAY_W / 2 - p->enemy->width/2 ;
	p->enemy->y = DISPLAY_H / 2 - p->enemy->height/2;

	return p;
}

void *object_colision(){
	Object *p;
	 for(p = &object_head; (p != NULL); p = p->next){
		 switch(p->type){
		 case player:
			 	 if (p->player->y <= 0) {
					p->player->y = 0;
					//keys[KEY_UP] = false;
				}
				if (p->player->y >= DISPLAY_H - p->player->height) {
					p->player->y = DISPLAY_H - p->player->height;
					//keys[KEY_DOWN] = false;
				}
				if (p->player->x <= 0) {
					p->player->x = 0;
					//keys[KEY_LEFT] = false;
				}
				if (p->player->x >= DISPLAY_W - p->player->width) {
					p->player->x = DISPLAY_W - p->player->width;
					//keys[KEY_RIGHT] = false;
				}
			break;

		 case bullet:
				if (p->bullet->y < 0) {
					p = object_del(p);
				}
			 break;
		 }
	 }
	 return 0;
}

void *object_draw(){
	Object *p;
	for(p = &object_head; (p != NULL); p = p->next){
		if(p->player != NULL){
			al_draw_bitmap(p->player->img, p->player->x, p->player->y, 0);
			mask_draw(p->player->mask,p->player->x,p->player->y);
		}
		if(p->bullet != NULL) {
			//al_draw_bitmap(p->bullet->img, p->bullet->x, p->bullet->y, 0);
			al_draw_filled_circle(p->bullet->x, p->bullet->y, 5, al_map_rgb(255, 0, 255));
		}
	}
	return 0;
}

void *object_move(){
	Object *p;
	for(p = &object_head; (p != NULL); p = p->next){
		if(p->player != NULL){

		}
		if(p->bullet != NULL){
			p->bullet->x += p->bullet->vx;
			p->bullet->y += p->bullet->vy;
		}
	}
	return 0;
}

Mask *mask_new(ALLEGRO_BITMAP *btm){
	Mask *temp;
	int x,y;
	int width = al_get_bitmap_width(btm);
	int height = al_get_bitmap_height(btm);

	//ALLEGRO_COLOR tansColor = al_map_rgb(0,0,0); //Bitmap Backgroud color
	ALLEGRO_COLOR pixel;

	temp = mask_create(width, height);

	if(!temp)
		return NULL;

	mask_clear(temp);

	for(x = 0; x < width; x++){
		for(y = 0; y < height; y++){
			pixel = al_get_pixel(btm, x, y);
			if(pixel.a != 0){
				temp->bits[x][y] = 1;
			}
		}
	}

	return temp;
}

Mask *mask_create(int width, int height){
	int i;
	Mask *temp = (Mask *)malloc(sizeof(Mask));
	temp->widht = width;
	temp->height = height;

	temp->bits = (int **)malloc( width *sizeof(int *));
	for(i = 0; i < width; i++){
		temp->bits[i] = (int *)malloc( height *sizeof(int));
	}

	if(!temp)
		return NULL;

	return temp;

}

void *mask_clear(Mask *m){
	int x,y;
	for(x= 0; x < m->widht; x++){
		for(y= 0; y < m->height; y++){
			m->bits[x][y] = 0;
		}
	}
	return 0;
}

void *mask_draw(Mask *temp, int x, int y){
	int j, k;
	for(j = 0; j < temp->widht; j++){
			for(k = 0; k < temp->height; k++){
				if(!temp->bits[j][k])
					al_put_pixel(x+j, y+k, al_map_rgba_f(0.75,0,0.75,0.75));
			}
		}
	return 0;
}
