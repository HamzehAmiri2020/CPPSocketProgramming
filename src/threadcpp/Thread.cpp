/*
 * Thread.cpp
 *
 *  Created on: Mar 10, 2020
 *      Author: ceph1
 */

#include "Thread.h"

Thread::Thread(auto_ptr<Runnable> r, bool isDetached) :
		runnable(r), detached(isDetached) {
	if (!runnable.get()) {
		cout << "Thread::Thread(auto_ptr<Runnable> r, bool isDetached)" "failed at " << " " << __FILE__ << ":" << __LINE__ << "-" << " runnable is NULL" << endl;
		exit(-1);
	}
}

Thread::Thread(bool isDetached) :
		runnable(NULL), detached(isDetached) {
}

void* Thread::startThreadRunnable(void *pVoid) {
	Thread *runnableThread = static_cast<Thread*>(pVoid);
	assert(runnableThread);
	runnableThread->result = runnableThread->runnable->run();
	runnableThread->setCompleted();
	return runnableThread->result;
}

void* Thread::startThread(void *pVoid) {
	Thread *aThread = static_cast<Thread*>(pVoid);
	assert(aThread);
	aThread->result = aThread->run();
	aThread->setCompleted();
	return aThread->result;
}

Thread::~Thread() {
}

void Thread::start() {
	int status = pthread_attr_init(&threadAttribute);
	if (status) {
		printError("pthread_attr_init failed at", status, __FILE__, __LINE__);
		exit(status);
	}

	status = pthread_attr_setscope(&threadAttribute, PTHREAD_SCOPE_SYSTEM);
	if (status) {
		printError("pthread_attr_setscope failed at", status,
		__FILE__, __LINE__);
		exit(status);
	}

	if (!detached) {
		if (!runnable.get()) {
			status = pthread_create(&PthreadThreadID, &threadAttribute, Thread::startThread, (void*) this);
			if (status) {
				printError("pthread_create failed at", status, __FILE__, __LINE__);
				exit(status);
			}
		} else {
			status = pthread_create(&PthreadThreadID, &threadAttribute, Thread::startThreadRunnable, (void*) this);
			if (status) {
				printError("pthread_create failed at", status,
				__FILE__, __LINE__);
				exit(status);
			}
		}
	} else {
		status = pthread_attr_setdetachstate(&threadAttribute, PTHREAD_CREATE_DETACHED);
		if (status) {
			printError("pthread_attr_setdetachstate failed at", status,
			__FILE__, __LINE__);
			exit(status);
		}

		if (!runnable.get()) {
			status = pthread_create(&PthreadThreadID, &threadAttribute, Thread::startThread, (void*) this);
			if (status) {
				printError("pthread_create failed at", status,
				__FILE__, __LINE__);
				exit(status);
			}
		} else {
			status = pthread_create(&PthreadThreadID, &threadAttribute, Thread::startThreadRunnable, (void*) this);
			if (status) {
				printError("pthread_create failed at", status, __FILE__, __LINE__);
				exit(status);
			}
		}
	}
	status = pthread_attr_destroy(&threadAttribute);
	if (status) {
		printError("pthread_attr_destroy failed at", status,
		__FILE__, __LINE__);
		exit(status);
	}
}

void* Thread::join() {
	int status = pthread_join(PthreadThreadID, NULL);
	if (status) {
		printError("pthread_join failed at", status,
		__FILE__, __LINE__);
		exit(status);
	}
	return result;
}

void Thread::setCompleted() {
}

void Thread::printError(char *msg, int status, char *fileName, int lineNumber) {
	cout << msg << " " << fileName << ":" << lineNumber << "-" ; //<< strerror(status) << endl
}

