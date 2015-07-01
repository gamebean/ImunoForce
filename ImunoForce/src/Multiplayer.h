#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER "172.16.104.163"		//ip address of udp server
#define BUFLEN	1500	// Buffer length in bytes
#define PORT	21234


typedef struct {
	int type;
	int x;
	int y;
	int img_i;
}Data;



void server_initialise();
char* r_receive();
void r_send();
void d_receive();
void d_send(Data *buffer);
void set_server();
void set_client();
//void data_draw(int , Data , ALLEGRO_BITMAP* );