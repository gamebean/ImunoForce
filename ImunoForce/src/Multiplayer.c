#include <stdio.h>
#include "Multiplayer.h"

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

char* d_receive() {
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

void d_send(Data* buffer) {
	printf("x: %d\ny: %d\ntype: %d\nimg_i: %d\n", buffer[0].x, buffer[0].y, buffer[0].type, buffer[0].img_i);
	if (sendto(sckt, buffer, BUFLEN, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR) {
		printf("sendto() Error. Code: %d\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}