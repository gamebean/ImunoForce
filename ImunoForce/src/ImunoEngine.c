/*
 * ImunoEngine.c
 *
 *  Created on: 06/06/2015
 *      Author: felipe
 */
#include <stdio.h>
#include "ImunoEngine.h"

Object list_head = {0,header,NULL,NULL,NULL,NULL};

Object *list_add(Object *p,Type t, int tag)
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
    if(list_head.next == NULL){
        list_head.next = p;
        p->prev = &list_head;
    }
    else{
        for(a = &list_head; a->next != NULL; a = a->next){} /* a vira ponteiro do ultimo Object da lista*/
        a->next = p;
        p->prev = a;
    }
    return p;
}

Object *list_search(int tag){
    Object *a;
    for(a = &list_head; a->tag != tag; a = a->next){
        if(a->next == NULL)
            return NULL;
    }
    return a;
}
/*
void list_del(int tag){
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
int list_del(Object *a){
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

