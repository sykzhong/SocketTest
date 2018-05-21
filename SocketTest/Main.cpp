#include "SocketServer.h"
#include <thread>
#include <chrono>
#include <mutex>

std::chrono::milliseconds interval(10);		//10ms time interval for mutex
std::mutex mtx;

void getSocketData(SocketServer socketserver)
{
	socketserver.listenClient();
}

void processSocketData(SocketServer socketserver)
{
	std::this_thread::sleep_for(interval);
	float x, y, z;
	while (1)
	{
		socketserver.getFloatDataFromBuffer(x, y, z);
		printf("x = %.2f, y = %.2f, z = %.2f\n", x, y, z);
	}
}

int main()
{
	SocketServer socketserver;
	socketserver.initSocket();

	
}