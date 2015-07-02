#include <stdio.h>
#include "Multiplayer.h"
#include <allegro5/allegro.h>



#ifdef __linux__
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR  -1
#define WSAGetLastError() -6969
#endif

SOCKET sckt;
struct sockaddr_in server, si_other;
int recv_len, slen = sizeof(si_other);
#ifndef __linux__
WSADATA wsa;
#endif

void server_initialise() {
	// Initialise winsock
#ifndef __linux__
	printf("Initialiasing Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("WSAStartup() Error. Code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
#endif
	printf("Initialised.\n");
	struct timeval tv;

	tv.tv_sec = 0;  /* 30 Secs Timeout */
	tv.tv_usec = 100000;  // Not init'ing this can cause strange errors
	// Create a Socket
	if ((sckt = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		printf("socket() Error. Code: %d\n", WSAGetLastError());

	setsockopt(sckt, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
	printf("Socket Created.\n");
}

void r_receive(bool keys[]) {
	fflush(stdout);
	int i;
	memset(keys, '\0', 9);

	if ((recv_len = recvfrom(sckt, keys, 9, 0, (struct sockaddr*) &si_other, &slen)) >= 0) {

	}else{
		for(i = 0; i < 9; i++){
			keys[i] = false;
		}
		printf("r_receive failed. Error: %d\n", WSAGetLastError());
	}
	printf("r_receive\n");
	//return buffer;
}

void r_send(bool keys[]) {

	if (sendto(sckt, keys, 9, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR) {
		printf("r_send failed. Error: %d\n", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}
//	if (sendto(sckt, "Packet Request", strlen("Packet Request"), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
//	{
//		printf("sendto() failed with error code : %d", WSAGetLastError());
//		exit(EXIT_FAILURE);
//	}
	printf("r_send");
}

void d_receive(Data buffer[]) {
	int i;

	memset(buffer, '\0', BUFLEN); // Clear buffer

	if (recvfrom(sckt, buffer, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) >= 0) { // Receive data
		/*for (i = 0; i < 90; i++) {
			if (buffer[i].type != 0 || buffer[i].img_i != 0 || buffer[i].x != 0 || buffer[i].y != 0)
				printf(" x: %d\n y: %d\n type: %d\n img_i: %d\n", buffer[i].x, buffer[i].y, buffer[i].type, buffer[i].img_i);
		}*/

	}else{
		printf("d_receive failed. Error: %d\n", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}
	printf("d_receive\n");
}

void d_send(Data* buffer) {
	//printf("x: %d\ny: %d\ntype: %d\nimg_i: %d\n", buffer[0].x, buffer[0].y, buffer[0].type, buffer[0].img_i);
	if (sendto(sckt, buffer, BUFLEN, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR) {
		printf("d_send failed. Error: %d\n", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}
	printf("d_send\n");
}

void set_server() {
	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	// Bind
	if (bind(sckt, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("bind() Error. Code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");
}

void set_client() {
	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
#ifndef __linux__
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
#else
	si_other.sin_addr.s_addr = inet_addr(SERVER);
#endif
}

void data_draw(Data data[], ALLEGRO_BITMAP* **sprites) {
	int i;
	al_init();
	al_init_image_addon();

	for (i = 0; i < BUFLEN / sizeof(Data); i++) {
		if (&data[i] != NULL) {
			if (data[i].type != 7 && data[i].type != 3) {
				al_draw_bitmap(sprites[data[i].type][data[i].img_i], data[i].x, data[i].y, 0);
			}
		}
	}
}