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

using namespace std;

class Double {
public:
	Double(double d = 0) :
			dValue(d) {
		cout << "constructor: " << dValue << endl;
	}
	~Double() {
		cout << "destructor: " << dValue << endl;
	}
	void setDouble(double d) {
		dValue = d;
	}
private:
	double dValue;
};

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
// increment s by million times
	for (int i = 0; i < 1000000; i++)
		s += 1;
	return 0;
}

int main(int argc, char **argv) {
	auto_ptr<Double> ptr(new Double(3.14));
	ptr->setDouble(6.28);
	(*ptr).setDouble(6.28);

	auto_ptr<communicatingThread> thread1(new communicatingThread(1));
	auto_ptr<communicatingThread> thread2(new communicatingThread(2));
	thread1->start();
	thread2->start();
	thread1->join();
	thread2->join();

	cout << "s = " << s << endl;
}

