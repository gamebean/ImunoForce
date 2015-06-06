/*
 * ImunoEngine.h
 *
 *  Created on: 06/06/2015
 *      Author: felipe
 */
//Object list_head = {0,header,NULL,NULL,NULL,NULL};

// Define the possible types of object in the game
#include <stdio.h>
#include <allegro5/allegro.h>

typedef int Type;
enum Types {player, bullet, header};

// Define Player structure
typedef struct{
    char String[20];
    int x,y;

    ALLEGRO_BITMAP* img;
}Player;

// Define the Bullet structure
typedef struct{
    int tag;
    int x,y;
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
	Object *list_add(Object *,Type t, int); // Add an object of a certain type
	Object *list_search(int); // Finds an object based on its tag
	//void list_del(int);
	int list_del(Object *); // return 0 if successful, -1 if ocurrs an error
