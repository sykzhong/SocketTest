#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#define PORT 6666
#define BUFFER_SIZE 1024
#define IP_ADDRESS "192.168.123.156"





void handle(int connfd);

int main()
{
	WSADATA Ws;
	/* Init Windows Socket */
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)
	{
		printf("Init Windows Socket Failed::%d\n", GetLastError());
		return -1;
	}
	SOCKET server_socket;
	struct sockaddr_in serv_addr;
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET || server_socket == SOCKET_ERROR)
	{
		printf("Create Socket Failed::%d\n", GetLastError());
		return -1;
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	serv_addr.sin_port = htons(PORT);
	if (bind(server_socket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
	{
		printf("Bind Error::%d\n", GetLastError());
		return -1;
	}
	if (listen(server_socket, 10) == -1)
	{
		printf("listen Error::%d\n", GetLastError());
		return -1;
	}
	printf("======waiting for client's requeset======\n");
	while (1)
	{
		struct sockaddr_in client_addr;
		SOCKET client_socket;
		int length = sizeof(sockaddr_in);
		char buffer[BUFFER_SIZE];
		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);
		sprintf(buffer, "accept from %s:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
		printf(buffer, "");
		if (client_socket < 0)
		{
			//printf("Server Accept Failed\n");
			continue;
		}
		printf("Recieve Connect!\n");
		/* receive data from client */
		while (1)
		{
			memset(buffer, 0, BUFFER_SIZE);
			length = recv(client_socket, buffer, BUFFER_SIZE, 0);
			if (length < 0)
			{
				printf("Server Receive Data Failed!\n");
				break;
			}
			else if (length == 0)
			{
				closesocket(client_socket);
				break;
			}
			if ('q' == buffer[0])
			{
				printf("Quit from client!\n");
				closesocket(client_socket);
				break;
			}
			printf("%s\n", buffer);
		}
	}
	closesocket(server_socket);
	return 0;
}

void handle(int connfd)
{

}



