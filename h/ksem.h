/*
 * ksem.h
 *
 *  Created on: Aug 28, 2018
 *      Author: OS1
 */

#ifndef H_KSEM_H_
#define H_KSEM_H_

#include "queue.h"

class KernelSem{
public:
	int val;

	KernelSem(int init = 1);
	~KernelSem();
	int wait(int toBlock);
	void signal();
	int value() const;
	Queue *semQueue;


};


#endif /* H_KSEM_H_ */
