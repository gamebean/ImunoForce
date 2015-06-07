/*
 * ImunoEngine.h
 *
 *  Created on: 06/06/2015
 *      Author:  Author: Bruno Pachceco & Felipe Sens Bonetto
 */
//Object object_head = {0,header,NULL,NULL,NULL,NULL};

// Define the possible types of object in the game
#include <stdio.h>
#include <allegro5/allegro.h>

typedef int Type;
enum Types {header ,player, bullet};

// Define Player structure
typedef struct{
    char String[20];
    int x,y;
    int width, height;
    ALLEGRO_BITMAP* img;
}Player;

// Define the Bullet structure
typedef struct{
    int tag;
    int x,y;
    int vx,vy;
    int width, height;
    ALLEGRO_BITMAP* img;
}Bullet;

// The Object struct have private pointers to every type of object in the game
typedef struct{
	int tag; // Used to identify the structure, should be unique
	Type type;

// Pointers for every possible type object type in the game
    Player *player;
    Bullet *bullet;

    struct Object *next; //Next Element
    struct Object *prev; //Prev Element
}Object;


// Object manipulation functions
	Object *object_add(Object *,Type t, int); // Add an object of a certain type
	Object *object_search(int); // Finds an object based on its tag
	//void object_del(int);
	int object_del(Object *); // return 0 if successful, -1 if ocurrs an error
	Object *player_add(Object *,char[]);
	Object *bullet_add(Object *,int player_tag, char[]);
	void *object_colision();
	void object_draw();

