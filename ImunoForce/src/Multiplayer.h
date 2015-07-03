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

#define SERVER "172.16.104.163"		//ip address of udp server
#define BUFLEN	1500	// Buffer length in bytes
#define PORT	21234

//#pragma pack(1)
typedef struct {
	char type;
	int x;
	int y;
	char img_i;
	char dir;
}Data;
//#pragma pack(0)


void server_initialise();
void r_receive();
void r_send();
void d_receive();
void d_send(Data *buffer);
void set_server();
void set_client();
//void data_draw(Data , ALLEGRO_BITMAP* );
