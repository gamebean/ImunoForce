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

void data_serialize(Data data[], unsigned char *buffer, GameVar var){
	int i;
	buffer[0] = var.gameState;
	buffer[1] = var.score;
	buffer[2] = var.life;
	buffer[3] = var.dna;

	for (i = 4; (i < BUFLEN) && (i / DATA_SIZE < DATA_LENGHT); i += DATA_SIZE){
		buffer[i + 0] = data[i / DATA_SIZE].dir;
		buffer[i + 1] = data[i / DATA_SIZE].img_i;
		buffer[i + 2] = data[i / DATA_SIZE].type;
		buffer[i + 3] = (data[i / DATA_SIZE].x >> 8) & 0xFF;
		buffer[i + 4] = (data[i / DATA_SIZE].x >> 0) & 0xFF;
		buffer[i + 5] = ((data[i / DATA_SIZE].y + 50) >> 8) & 0xFF;
		buffer[i + 6] = (((data[i / DATA_SIZE].y + 50) >> 0) & 0xFF);
	}
}
void data_deserialize(Data data[], unsigned char *buffer, GameVar *var){
	int i;
	var->gameState = buffer[0];
	var->score = buffer[1];
	var->life = buffer[2];
	var->dna = buffer[3];

	for (i = 4; (i < BUFLEN) && (i / DATA_SIZE < DATA_LENGHT); i += DATA_SIZE){
		data[i / DATA_SIZE].dir = buffer[i + 0];
		data[i / DATA_SIZE].img_i = buffer[i + 1];
		data[i / DATA_SIZE].type = buffer[i + 2];
		data[i / DATA_SIZE].x = (((buffer[i + 3] << 8) | (buffer[i + 4] << 0)) & 0xFFFF);
		data[i / DATA_SIZE].y = (((buffer[i + 5] << 8) | (buffer[i + 6] << 0)) & 0xFFFF) - 50;
	}
}

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
}

void r_send(bool keys[]) {

	if (sendto(sckt, keys, 9, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR) {
		printf("r_send failed. Error: %d\n", WSAGetLastError());
		//exit(EXIT_FAILURE);
	}
	printf("r_send");
}

void d_receive(Data buffer[], GameVar *var) {
	int i;
	unsigned char d[BUFLEN];
	memset(d, '\0', BUFLEN); // Clear buffer
	//memset(buffer, '\0', BUFLEN);
	if (recvfrom(sckt, d, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) >= 0) { // Receive data
		data_deserialize(buffer, d, var);

	}else{
		printf("d_receive failed. Error: %d\n", WSAGetLastError());
	}
	printf("d_receive\n");
}

void d_send(Data* buffer, GameVar var) {
	unsigned char d[BUFLEN];
	data_serialize(buffer, d, var);
	if (sendto(sckt, d, BUFLEN, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR) {
		printf("d_send failed. Error: %d\n", WSAGetLastError());
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

void set_client(char ip[]) {
	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
#ifndef __linux__
	si_other.sin_addr.S_un.S_addr = inet_addr(ip);
#else
	si_other.sin_addr.s_addr = inet_addr(ip);
#endif
}










