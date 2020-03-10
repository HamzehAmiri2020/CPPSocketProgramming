/*
 * Runnable.h
 *
 *  Created on: Mar 10, 2020
 *      Author: ceph1
 */

#ifndef THREADCPP_RUNNABLE_H_
#define THREADCPP_RUNNABLE_H_

class Runnable {
public:
	virtual void* run() = 0;
	virtual ~Runnable() = 0;
};

Runnable::~Runnable(){};

#endif /* THREADCPP_RUNNABLE_H_ */
