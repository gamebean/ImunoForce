#include<winsock2.h>
#include<stdio.h>

 
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"		//ip address of udp server
#define BUFLEN 1500				//Max length of bufferin bytes
#define PORT 21234				//The port on which to listen for incoming data

typedef int Type;
enum Types {
	header, player, bullet, enemy, background
};

typedef struct {
	Type type;
	int x;
	int y;
	int img_i;
}Data;

int main(void)
{
	struct sockaddr_in server, si_other;
	int i, s, slen = sizeof(si_other);
	char buf[BUFLEN];
//	char message[BUFLEN];
	WSADATA wsa;

	Data data[BUFLEN / sizeof(Data)];

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	// Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//// Bind
	//if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
	//	printf("bind() Error. Code: %d\n", WSAGetLastError());
	//	exit(EXIT_FAILURE);
	//}
	//puts("Bind done");

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//start communication
	while (1)
	{
		//send the message
		if (sendto(s, "Packet Request", strlen("Packet Request"), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("Packet Request Sent.\n");

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(data, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, data, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		//printf("%s\n", buf);
		printf("===========================================================================\n");
		for ( i = 0; i < 90; i++) {
			if (data[i].type != 0 || data[i].img_i != 0 || data[i].x != 0 || data[i].y != 0)
				printf(" x: %d\n y: %d\n type: %d\n img_i: %d\n", data[i].x, data[i].y, data[i].type, data[i].img_i);
		}
		
	}

	closesocket(s);
	WSACleanup();

	return 0;
}