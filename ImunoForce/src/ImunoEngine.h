//Object object_head = {0,header,NULL,NULL,NULL,NULL};

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// Define the possible types of object in the game
typedef char Type;
enum Types {
	background, player, player2, bullet, enemy, enemy_b, enemy_c, enemy_d, header
};

#define enemy_all(x) (x == enemy || x == enemy_b || x == enemy_c || x == enemy_d)
#define case_enemy_all case enemy: case enemy_b: case enemy_c: case enemy_d:

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
	bool **bits ;
} Mask;

Mask *masks[header][20];
ALLEGRO_BITMAP* sprites[header][20];

// The Object struct have private pointers to every type of object in the game
typedef struct {
	int tag; // Used to identify the structure, should be unique
	Type type;

	char String[20];
	float x, y;
	float vx, vy;
	int width, height;
	int mask_i;
	bool dir;

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
Object *object_del(Object *);
Object *player_add(char player_name[], int frame_delay, int vector_size);
Object *bullet_add(Object, Object *);
Object *enemy_add(Object, int, int);
Object *background_add(int , int);

void object_colision();
void object_draw();
void background_draw();
void object_move();
Mask *mask_create(int, int);
Mask *mask_new(ALLEGRO_BITMAP *);
void mask_clear(Mask *);
void mask_draw(Mask *, int, int);
int anim(Object *object, int frame_delay, int vector_size);
void object_anim();
int get_score();
int enemy_count();
int object_find(char[]);
bool player_alive();
void game_reset();
void list_destroy();
void object_track();
void engine_init();
void keyboard_read(ALLEGRO_EVENT , char[] , int);

#ifdef __linux__
void strcpy_s(char[], int, char[]);
#endif

void draw_loading(float , ALLEGRO_FONT* );
