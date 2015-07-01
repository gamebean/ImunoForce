#ifndef __linux__
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <allegro5/allegro.h>

#define SERVER "127.0.0.1"		//ip address of udp server
#define BUFLEN	1500	// Buffer length in bytes
#define PORT	21234


typedef struct {
	int type;
	int x;
	int y;
	int img_i;
	int dir;
}Data;



void server_initialise();
void r_receive();
void r_send();
void d_receive();
void d_send(Data *buffer);
void set_server();
void set_client();
//void data_draw(Data , ALLEGRO_BITMAP* );
