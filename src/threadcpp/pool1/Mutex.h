/*
 * Mutex.h
 *
 *  Created on: Mar 21, 2020
 *      Author: root
 */

#ifndef THREADCPP_POOL1_MUTEX_H_
#define THREADCPP_POOL1_MUTEX_H_

#include <pthread.h>
#include <unistd.h>
#include <deque>
#include <iostream>
#include <vector>
#include <errno.h>
#include <string.h>

#include "Global.h"

using namespace std;

class Mutex {
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
	pthread_mutex_t* get_mutex_ptr();

private:
	pthread_mutex_t m_lock;
	volatile bool is_locked;
};

#endif /* THREADCPP_POOL1_MUTEX_H_ */
