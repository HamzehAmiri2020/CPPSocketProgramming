/*
 * CondVar.h
 *
 *  Created on: Mar 21, 2020
 *      Author: root
 */

#ifndef THREADCPP_POOL1_CONDVAR_H_
#define THREADCPP_POOL1_CONDVAR_H_

#include <pthread.h>
#include <unistd.h>
#include <deque>
#include <iostream>
#include <vector>

#include "Global.h"

using namespace std;

class CondVar {
public:
	CondVar();
	~CondVar();
	void wait(pthread_mutex_t *mutex);
	void signal();
	void broadcast();
private:
	pthread_cond_t m_cond_var;
};

#endif /* THREADCPP_POOL1_CONDVAR_H_ */
