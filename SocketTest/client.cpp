// SocketTest.cpp : 定义控制台应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#define PORT 6666
#define IP_ADDRESS "192.168.123.93"
#define BUFFER_SIZE 1024

int main()
{
	WSADATA Ws;
	SOCKET client_socket;
	struct sockaddr_in serv_addr;
	int ret = 0;
	char send_buffer[BUFFER_SIZE];

	/* Init Windows Socket */
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)
	{
		printf("Init Windows Socket Failed::%d\n", GetLastError());
		return -1;
	}

	/* Create Socket */
	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket == INVALID_SOCKET)
	{
		printf("Create Socket Failed::%d\n", GetLastError());
		return -1;
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	serv_addr.sin_port = htons(PORT);
	memset(serv_addr.sin_zero, 0x00, 8);
	
	/* connect socket */
	ret = connect(client_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (ret == SOCKET_ERROR)
	{
		printf("Connect Error::%d\n", GetLastError());
		return -1;
	}
	else
	{
		printf("Connect succedded!\n");
	}
	while (1)
	{
		scanf("%s", send_buffer);

		/* send data to server */
		ret = send(client_socket, send_buffer, (int)strlen(send_buffer), 0);
		if (ret == SOCKET_ERROR)
		{
			printf("Send Info Error::%d\n", GetLastError());
			break;
		}
		if ('q' == send_buffer[0])
		{
			break;
		}
	}

	closesocket(client_socket);
	WSACleanup;

	system("pause");

	return 0;
}

