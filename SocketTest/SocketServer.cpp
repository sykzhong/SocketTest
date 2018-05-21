#define _CRT_SECURE_NO_WARNINGS
#include "SocketServer.h"


SocketServer::~SocketServer()
{

}

int SocketServer::initSocket()
{
	WSADATA Ws;
	/* Init Windows Socket */
	if (WSAStartup(MAKEWORD(2, 2), &Ws) != 0)
	{
		printf("Init Windows Socket Failed::%d\n", GetLastError());
		return -1;
	}
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET || server_socket == SOCKET_ERROR)
	{
		printf("Create Socket Failed::%d\n", GetLastError());
		return -1;
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);
	server_addr.sin_port = htons(PORT);
	if (bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
	{
		printf("Bind Error::%d\n", GetLastError());
		return -1;
	}
	if (listen(server_socket, 10) == -1)
	{
		printf("listen Error::%d\n", GetLastError());
		return -1;
	}
	printf("======server socket init success, waiting for client's requeset======\n");
	printf("echo server startup,listen on port:%d\n", PORT);
	return 0;
}

int SocketServer::listenClient()
{
	sockaddr_in client_addr;
	SOCKET client_socket;
	int socklen = sizeof(sockaddr_in);;
	char buf[BUFFER_SIZE];
	while (1)
	{
		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &socklen);
		if (client_socket < 0)
		{
			printf("Accept Error::%d\n", GetLastError());
			continue;
		}
		sprintf(buf, "accept form %s:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
		printf(buf, "");
		handle(client_socket);
	}
}

void SocketServer::handle(SOCKET client_socket)
{
	int n;
	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		n = recv(client_socket, buffer, BUFFER_SIZE, 0);
		if (n < 0)
		{
			printf("Receive Error::%d\n", GetLastError());
			break;
		}
		if (n == 0)
		{
			//client_socket is closed by client
			closesocket(client_socket);
			printf("client exit\n");
			break;
		}
		if (strncmp("exit", buffer, 4) == 0)
		{
			closesocket(client_socket);
			printf("client exit\n");
			break;
		}
		send(client_socket, buffer, n, 0);
		printf("%s\n", buffer);
	}
}

void SocketServer::getFloatDataFromBuffer(float &x, float &y, float &z)
{
	for (int i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i] == 'x' || buffer[i] == 'y' || buffer[i] == 'z')
		{
			string str_tmp;
			int j = i + 1;
			for (; j < strlen(buffer) && buffer[j] != ' '; j++)
			{
				str_tmp += buffer[j];
			}
			float tmp;
			tmp = stof(str_tmp);
			switch (buffer[i])
			{
			case 'x':
				x = tmp;
				break;
			case 'y':
				y = tmp;
				break;
			case 'z':
				z = tmp;
				break;
			default:
				std::cout << "Error: reading wrong data from socket client" << std::endl;
				break;
			}
			i = j;
		}
	}
}

//int main()
//{
//	SocketServer socketserver;
//	socketserver.initSocket();
//	socketserver.listenClient();
//	system("pause");
//	return 0;
//}