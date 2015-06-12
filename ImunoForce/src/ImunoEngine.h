/*
 * ImunoEngine.h
 *
 *  Created on: 06/06/2015
 *      Author: felipe
 */
//Object object_head = {0,header,NULL,NULL,NULL,NULL};

// Define the possible types of object in the game
#include <stdio.h>
#include <allegro5/allegro.h>

typedef int Type;
enum Types {header ,player, bullet, enemy};

typedef struct{
	int widht, height;
	int **bits;
}Mask;

// Define Player structure
typedef struct{
    char String[20];
    float x,y;
    float vx, vy;
    int width, height;
    ALLEGRO_BITMAP* img;
    Mask *mask;
}Player;

// Define the Bullet structure
typedef struct{
    int tag;
    float x,y;
    float vx,vy;
    int width, height;
    ALLEGRO_BITMAP* img;
    Mask *mask;
}Bullet;

// Define the Enemy structure
typedef struct{
    int tag;
    float x,y;
    float vx,vy;
    int width, height;
    ALLEGRO_BITMAP* img;
    Mask *mask;
}Enemy;

// The Object struct have private pointers to every type of object in the game
typedef struct{
	int tag; // Used to identify the structure, should be unique
	Type type;

// Pointers for every possible type object type in the game
    Player *player;
    Bullet *bullet;
    Enemy  *enemy;

    struct Object *next; //Next Element
    struct Object *prev; //Prev Element
}Object;

// Object manipulation functions
	Object *object_add(Object *,Type t, int); // Add an object of a certain type
	Object *object_search(int); // Finds an object based on its tag
	//void object_del(int);
	Object *object_del(Object *); // return 0 if successful, -1 if ocurrs an error
	Object *player_add(Object *,char[]);
	Object *bullet_add(Object *,int player_tag, char[], Mask *);
	void *object_colision();
	void *object_draw();
	void *object_move();
	Mask *mask_create(int, int);
	Mask *mask_new(ALLEGRO_BITMAP *);
	void *mask_clear(Mask *);
	void *mask_draw(Mask *, int , int);
