/*
 * ithread.h
 *
 *  Created on: Aug 27, 2018
 *      Author: OS1
 */

#ifndef H_ITHREAD_H_
#define H_ITHREAD_H_


#include "thread.h"

class IThread : public Thread{
public:
	IThread();
	void start();
	virtual void run();
};


#endif /* H_ITHREAD_H_ */
