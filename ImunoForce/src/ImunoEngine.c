/*
 * ImunoEngine.c
 *
 *  Created on: 06/06/2015
 *      Author:  Author: Bruno Pachceco & Felipe Sens Bonetto
 */
#include <stdio.h>
#include "ImunoEngine.h"
#include "AllegroDef.h"

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
		break;
    case bullet:
			p->player = NULL;
			p->bullet = (Bullet *)malloc(sizeof(Bullet));
		break;
    case header:
    	default:
			p->player = NULL;
			p->bullet = NULL;
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
/*
void object_del(int tag){
	Object  *a;
	Object *prev;
	Object *next;

	//a = bullet_search(id);
	prev = a->prev;
	next = a->next;
	if(next != NULL){
 	next->prev = prev;
	}if(prev != NULL){
	prev->next = next;
	}
	free(a);
}
*/
int object_del(Object *a){
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
		free(a);
		return 0;
	}else{
		return -1;
	}
}

Object *player_add(Object *p,char bitmap[]){
	int tag = 1;
	 for(p = &object_head; p != NULL; p = p->next){
		 if(p->type == player)
			 tag ++;
	 }
	p = object_add(p,player,tag);
	p->player->img = al_load_bitmap(bitmap);
	p->player->height = al_get_bitmap_height(p->player->img);
	p->player->width = al_get_bitmap_width(p->player->img);

	p->player->x = DISPLAY_W / 2 - p->player->width/2 + 100*(tag-1);
	p->player->y = DISPLAY_H / 2 - p->player->height/2;

	return p;
}

Object *bullet_add(Object *bllt,int player_tag, char bitmap[]){
	Object *p;
	p = object_search(player_tag);
	bllt = object_add(bllt, bullet,8);

	bllt->bullet->img = al_load_bitmap(bitmap);
	bllt->bullet->height = al_get_bitmap_height(bllt->bullet->img);
	bllt->bullet->width = al_get_bitmap_width(bllt->bullet->img);
	bllt->bullet->x = p->player->x + p->player->width/2 - bllt->bullet->width/2;
	bllt->bullet->y = p->player->y;
	bllt->bullet->vx = 0;
	bllt->bullet->vy = -10;

	return bllt;
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
					object_del(p);
				}
			 break;
		 }
	 }
	 return 0;
}

void object_draw(){
	Object *p;
	for(p = &object_head; (p != NULL); p = p->next){
		if(p->player != NULL){
			al_draw_bitmap(p->player->img, p->player->x, p->player->y, 1);
		}
		if(p->bullet != NULL){
			p->bullet->x += p->bullet->vx;
			p->bullet->y += p->bullet->vy;
			al_draw_bitmap(p->bullet->img, p->bullet->x, p->bullet->y, 1);
		}
	}
}



