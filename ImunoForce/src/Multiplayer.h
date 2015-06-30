#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFLEN	1500	// Buffer length in bytes
#define PORT	21234


typedef struct {
	int type;
	int x;
	int y;
	int img_i;
}Data;



void server_initialise();
char* d_receive();
void d_send(Data *buffer);