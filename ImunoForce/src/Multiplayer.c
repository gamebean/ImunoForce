#include <stdio.h>
#include "Multiplayer.h"
#include "AllegroDef.h"

SOCKET sckt;
struct sockaddr_in server, si_other;
int recv_len, slen = sizeof(si_other);
WSADATA wsa;


void server_initialise() {
	// Initialise winsock
	printf("Initialiasing Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("WSAStartup() Error. Code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	// Create a Socket
	if ((sckt = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		printf("socket() Error. Code: %d\n", WSAGetLastError());
	printf("Socket Created.\n");
}

char* r_receive() {
	fflush(stdout);
	char buffer[BUFLEN];
	memset(buffer, '\0', BUFLEN);

	printf("Waiting for Request... ");
	if ((recv_len = recvfrom(sckt, buffer, sizeof(buffer), 0, (struct sockaddr*) &si_other, &slen)) == SOCKET_ERROR) {
		printf("recvfrom() Error. Code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	return buffer;
}

void r_send() {
	if (sendto(sckt, "Packet Request", strlen("Packet Request"), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Packet Request Sent.\n");
}

void d_receive(Data buffer[]) {
	int i;

	memset(buffer, '\0', BUFLEN); // Clear buffer

	if (recvfrom(sckt, buffer, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR) { // Receive data
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	/*printf("===========================================================================\n");
	for (i = 0; i < 90; i++) {
		if (buffer[i].type != 0 || buffer[i].img_i != 0 || buffer[i].x != 0 || buffer[i].y != 0)
			printf(" x: %d\n y: %d\n type: %d\n img_i: %d\n", buffer[i].x, buffer[i].y, buffer[i].type, buffer[i].img_i);
	}*/
}

void d_send(Data* buffer) {
	printf("x: %d\ny: %d\ntype: %d\nimg_i: %d\n", buffer[0].x, buffer[0].y, buffer[0].type, buffer[0].img_i);
	if (sendto(sckt, buffer, BUFLEN, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR) {
		printf("sendto() Error. Code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
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
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
}

void data_draw(int multiState, Data data[], ALLEGRO_BITMAP* **sprites) {
	int i;

	if (multiState != 0) {
		for (i = 0; i < BUFLEN / sizeof(Data); i++) {
			if (data[i].type != 0 && data[i].type != 4) {
				al_draw_bitmap(sprites[data[i].type][data[i].img_i], data[i].x, data[i].y, 0);
			}
		}
	}
}