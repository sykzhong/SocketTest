#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#define PORT 6666
#define BUFFER_SIZE 1024
#define IP_ADDRESS "192.168.123.156"

using namespace std;
class SocketServer
{
public:
	SocketServer();
	~SocketServer();

	int initSocket();
	int listenClient();
	void getFloatDataFromBuffer(float &x, float &y, float &z);

	void handle(SOCKET client_socket);
private:
	sockaddr_in server_addr;
	SOCKET server_socket;
	char buffer[BUFFER_SIZE];
};

#endif