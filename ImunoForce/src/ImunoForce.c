/*
 ============================================================================
 Name        : ImunoForce.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <allegro5/allegro.h>

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

    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_flip_display();

    al_rest(10.0);

    al_destroy_display(janela);

    return 0;
}
