// ZeroMQ_Test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define __WINDOWS__

#include "zmq.hpp"
#include <string>
#include <iostream>
#include <windows.h>
#include "zhelpers.hpp"
using namespace std;

/*
DWORD WINAPI MyThread_client(LPVOID lpParamter)
{
	zmq::context_t context(1);
	//建立套接字
	zmq::socket_t socket(context, ZMQ_REQ);

	std::cout << "Connecting to hello world server..." << std::endl;
	//连接服务器
	socket.connect("tcp://localhost:5555");

	for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
		s_send(socket, "hello");
		std::cout << "Client1 Received :" << s_recv(socket) << std::endl;

		Sleep(1000);
	}
	return 0;

}

DWORD WINAPI MyThread_client1(LPVOID lpParamter)
{
	zmq::context_t context(1);
	//建立套接字
	zmq::socket_t socket(context, ZMQ_REQ);

	std::cout << "Connecting to hello world server..." << std::endl;
	//连接服务器
	socket.connect("tcp://localhost:5555");

	for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
		s_send(socket, "SB");
		std::cout << "Client2 Received :" << s_recv(socket) << std::endl;

		Sleep(1000);
	}
	return 0;

}

DWORD WINAPI MyThread_servce(LPVOID lpParamter)
{
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	//绑定端口
	socket.bind("tcp://*:5555");

	while (true) {
		std::cout << "Servce Received: " << s_recv(socket) << std::endl;
		s_send(socket, "world");
	}
}

int main()
{

	HANDLE hThread1 = CreateThread(NULL, 0, MyThread_client, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread_servce, NULL, 0, NULL);

	HANDLE hThread3 = CreateThread(NULL, 0, MyThread_client1, NULL, 0, NULL);

	while (1);
	return 0;
}



*/



//订阅1
DWORD WINAPI MyThread_sub1(LPVOID lpParamter)
{
	zmq::context_t context(1);
	zmq::socket_t subscriber(context, ZMQ_SUB);
	//连接
	subscriber.connect("tcp://localhost:5563");
	//设置频道B
	subscriber.setsockopt(ZMQ_SUBSCRIBE, "A", 1);
	while (1) {

		//  Read envelope with address
		std::string address = s_recv(subscriber);
		//  Read message contents
		std::string contents = s_recv(subscriber);

		std::cout << "订阅1：[" << address << "] " << contents << std::endl;
	}
	return 0;

}
//订阅2
DWORD WINAPI MyThread_sub2(LPVOID lpParamter)
{
	zmq::context_t context(1);
	zmq::socket_t subscriber(context, ZMQ_SUB);
	//连接
	subscriber.connect("tcp://localhost:5563");
	//设置频道B
	subscriber.setsockopt(ZMQ_SUBSCRIBE, "B", 1);
	while (1) {

		//  Read envelope with address
		std::string address = s_recv(subscriber);
		//  Read message contents
		std::string contents = s_recv(subscriber);

		std::cout << "订阅2：[" << address << "] " << contents << std::endl;
	}
	return 0;

}
//订阅3
DWORD WINAPI MyThread_sub3(LPVOID lpParamter)
{
	zmq::context_t context(1);
	zmq::socket_t subscriber(context, ZMQ_SUB);
	//连接
	subscriber.connect("tcp://localhost:5563");
	//设置频道B
	// subscriber.setsockopt( ZMQ_SUBSCRIBE, "B", 1);
	while (1) {

		//  Read envelope with address
		std::string address = s_recv(subscriber);
		//  Read message contents
		std::string contents = s_recv(subscriber);

		std::cout << "订阅3：[" << address << "] " << contents << std::endl;
	}
	return 0;

}
//发布线程
DWORD WINAPI MyThread_pub(LPVOID lpParamter)
{
	//  Prepare our context and publisher
	zmq::context_t context(1);
	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5563");

	while (1) {
		//  Write two messages, each with an envelope and content
		s_sendmore(publisher, "A");
		s_send(publisher, "We don't want to see this");

		Sleep(100);
		s_sendmore(publisher, "B");
		s_send(publisher, "We would like to see this");
		Sleep(100);

	}
}

int main()
{
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread_pub, NULL, 0, NULL);
	Sleep(1000);
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread_sub1, NULL, 0, NULL);
	HANDLE hThread3 = CreateThread(NULL, 0, MyThread_sub2, NULL, 0, NULL);
	HANDLE hThread4 = CreateThread(NULL, 0, MyThread_sub3, NULL, 0, NULL);
	while (1);
	return 0;
}