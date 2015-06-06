#include <stdio.h>
#include <allegro5/allegro.h>
#include "ImunoEngine.h"

int main(int argc, char *argv[])
{
    ALLEGRO_DISPLAY *janela = NULL;
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro 5\n");
        return -1;
    }

    janela = al_create_display(640, 480);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar a janela\n");
        return -1;
    }
    //TEST
	int x;
	Object *oi;
	Object *p;

	for(x = 1; x < 5; x++){
		oi = list_add(oi,bullet, x);
	}
	for(x = 7; x < 9; x++){
		oi = list_add(oi,player, x);
	}

	oi = list_search(0);
	for(x = 0; (oi == NULL) || (oi->next != NULL); x++){
		oi = list_search(x);
		if(oi != NULL){
		printf("A tag deste Object ser: %d\nTipo: %d\n",oi->tag, oi->type);
		}
	}

	p = list_search(7);
    strcpy(p->player->String, "Este é o player");
	printf("	Objeto tag: %d \n	Intentificação: %s\n",p->tag,p->player->String);

    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_flip_display();

    al_rest(10.0);

    al_destroy_display(janela);

    return 0;
}


