/*
 * Thread.h
 *
 *  Created on: Mar 10, 2020
 *      Author: ceph1
 */

#ifndef THREADCPP_THREAD_H_
#define THREADCPP_THREAD_H_

#include <iostream>
#include <pthread.h>
#include <cassert>
#include <error.h>
#include <memory>
#include "Runnable.h"

using namespace std;

class Thread {
public:
	Thread(auto_ptr<Runnable> run, bool isDetached = false);
	Thread(bool isDetached = false);
	virtual ~Thread();
	void start();
	void* join();
private:
	Thread(const Thread&);

	pthread_t PthreadThreadID;
	pthread_attr_t threadAttribute;
	auto_ptr<Runnable> runnable;

	const Thread& operator=(const Thread&);
	void setCompleted();
	void *result;
	bool detached;

	virtual void* run() {
	}
	void printError(char *msg, int status, char *fileName, int lineNumber);

	static void* startThreadRunnable(void *pVoid);
	static void* startThread(void *pVoid);
};

#endif /* THREADCPP_THREAD_H_ */
