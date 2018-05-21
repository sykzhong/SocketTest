#include<iostream>
#include<thread>
#include<list>
#include<algorithm>
#include<mutex>

using namespace std;

std::list<int> myList;
std::mutex mtx;

void addList()
{
	
	while (myList.size() < 10)
	{
		mtx.lock();
		////changing data////
		for (int i = 0; i < 10000; i++)
		{
			for (int j = 0; j < 10000; j++)
			{
				
			}
		}
		myList.push_back(1);
		////////////////////
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	
}

void readList()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));	//Áît1³ÖËø
	while (myList.size() < 10)
	{
		//mtx.lock();
		//////read data////
		//cout << myList.size() << endl;
		///////////////////
		//mtx.unlock();
		//std::this_thread::sleep_for(std::chrono::milliseconds(2));
		if (mtx.try_lock())
		{
			cout << myList.size() << endl;
			mtx.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
	}
}

//int main()
//{
//	std::thread t1(addList);
//	std::thread t2(readList);
//	t1.join();
//	t2.join();
//	system("pause");
//	return 0;
//}