//Object object_head = {0,header,NULL,NULL,NULL,NULL};

// Define the possible types of object in the game
#include <stdio.h>
#include <allegro5/allegro.h>

typedef int Type;
enum Types {
	header, player, bullet, enemy
};

enum {
	B_L,
	B_C,
	B_R,
	S_L,
	S_C,
	S_R,
	F_L,
	F_C,
	F_R
};

typedef struct Mask_s {
	int widht, height;
	int **bits;
} Mask;

Mask *masks[4][20];
ALLEGRO_BITMAP* sprites[4][20];

// The Object struct have private pointers to every type of object in the game
typedef struct {
	int tag; // Used to identify the structure, should be unique
	Type type;

	char String[20];
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

	struct Object *next; //Next Element
	struct Object *prev; //Prev Element
} Object;

// Object manipulation functions
Object *object_add(Type t, int); // Add an object of a certain type
Object *object_search(int); // Finds an object based on its tag
//void object_del(int);
Object *object_del(Object *); // return 0 if successful, -1 if ocurrs an error
Object *player_add(char player_name[], int frame_delay, int vector_size);
Object *bullet_add(Object, Object *);
Object *enemy_add(Object, int, int);

//Object *player_add(char[], char[]);
//Object *bullet_add(Object, int);

void *object_colision();
void *object_draw();
void *object_move();
Mask *mask_create(int, int);
Mask *mask_new(ALLEGRO_BITMAP *);
void *mask_clear(Mask *);
void *mask_draw(Mask *, int, int);
void object_track();
int anim(Object *object, int frame_delay, int vector_size);
void object_anim();