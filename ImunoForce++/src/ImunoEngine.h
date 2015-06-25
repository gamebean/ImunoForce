//Object object_head = {0,header,NULL,NULL,NULL,NULL};

// Define the possible types of object in the game
#include <allegro5/allegro.h>
#include <iostream>

using namespace std;

enum {
	header,
	player,
	enemy,
	bullet
};


class Mask {
public:
	int width, height;
	int **bits;

	Mask (ALLEGRO_BITMAP* bitmap);

	void clear_bits();
	void draw(int x, int y);
};

//Mask masks[4][20];
//ALLEGRO_BITMAP* sprites[4][20];

// The Object struct have private pointers to every type of object in the game
class Object {
public:
	//int tag; // Used to identify the structure, should be unique
	//Type type;

	float x, y;
	float vx, vy;
	int width, height;
	int mask_i;

	//Animation variables
	int img_i;
	int img_delay;
	int frame_delay;
	int vector_size;

	int life;

	Object();
};

class Player : public Object {
public:
	char String[20];

	Player();
};

class Player1 : public Player {

	Player1();
};

class Player2 : public Player {

	Player2();
};

class Enemy : public Object {
public:
	Enemy *next;
	Enemy *prev;

	virtual void move() = 0;

	Enemy();
};

class Seeker : public Enemy {
	void move();

	Seeker();
};

class nSeeker : public Enemy {
	void move();

	nSeeker();
};

class Bullet : public Object {
public:
	Bullet *next;
	Bullet *prev;

	Bullet();
};



// Object manipulation functions
//Object *object_add(Type t, int); // Add an object of a certain type
Object *object_search(int); // Finds an object based on its tag
Object *object_del(Object *); // return 0 if successful, -1 if ocurrs an error
//Object *player_add(char player_name[], int frame_delay, int vector_size);
//Object *bullet_add(Object, Object *);
//Object *enemy_add(Object, int, int);

//Object *player_add(char[], char[]);
//Object *bullet_add(Object, int);

void *object_colision();
void *object_draw();
void *object_move();
void object_track();
int anim(Object *object, int frame_delay, int vector_size);
void object_anim();