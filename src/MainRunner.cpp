/*
 * MainRunner.cpp
 *
 *  Created on: Mar 9, 2020
 *      Author: ceph1
 */

#include <iostream>

#include <iostream>
#include <memory>
#include "threadcpp/Thread.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

using namespace std;

// shared variable
int s = 0;

class communicatingThread: public Thread {
public:
	communicatingThread(int ID) :
			myID(ID) {
	}
	virtual void* run();
private:
	int myID;
};

void* communicatingThread::run() {
	cout << "Thread " << myID << " is running!" << endl;
	for (int i = 0; i < 1000000; i++)
		s += 1;
	return 0;
}

#define PORT 8080

int main(int argc, char **argv) {
//	auto_ptr<communicatingThread> thread1(new communicatingThread(1));
//	auto_ptr<communicatingThread> thread2(new communicatingThread(2));
//	thread1->start();
//	thread2->start();
//	thread1->join();
//	thread2->join();
//
//	cout << "s = " << s << endl;

	int server_fd, new_socket, valread;
	int opt = 1;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	char *hello = "Hello from server";

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	return 0;
}

