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
	// thread ID
	pthread_t PthreadThreadID;
	// true if thread created in detached state
	bool detached;
	pthread_attr_t threadAttribute;
	// runnable object will be deleted automatically
	auto_ptr<Runnable> runnable;
	Thread(const Thread&);
	const Thread& operator=(const Thread&);
	// called when run() completes
	void setCompleted();
	// stores return value from run()
	void* result;

	virtual void* run() {}
	static void* startThreadRunnable(void* pVoid);
	static void* startThread(void* pVoid);
	void printError(char * msg, int status, char* fileName, int lineNumber);
};

#endif /* THREADCPP_THREAD_H_ */
