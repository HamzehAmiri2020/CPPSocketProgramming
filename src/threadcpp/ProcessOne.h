/*
 * ProcessOne.h
 *
 *  Created on: Mar 9, 2020
 *      Author: ceph1
 */

#ifndef THREADCPP_PROCESSONE_H_
#define THREADCPP_PROCESSONE_H_

#include <pthread.h>
#include <iostream>

class ProcessOne {
private:
	pthread_t *t1;
public:
	ProcessOne();
	virtual ~ProcessOne();
	void start();
};

#endif /* THREADCPP_PROCESSONE_H_ */
