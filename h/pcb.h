/*
 * pcb.h
 *
 *  Created on: Jun 12, 2018
 *      Author: OS1
 */

#ifndef H_PCB_H_
#define H_PCB_H_


#include "thread.h"
#include "queue.h"
class Queue;
enum Status {NEW, READY, BLOCKED, OVER};
class PCB{



public:
	unsigned int ss, sp, bp;
		unsigned *stack;
		Status status;
		Time timeSlice, timeToCount;//timeToCount
		Thread *myThread;
		StackSize stackSize;
		Queue *blockedQueue;

		PCB(Thread *myThread, StackSize stackSize ,Time timeSlice);
		virtual ~PCB();
	void createStack();
	static void runWrapper();
	int volatile val;

};




#endif /* H_PCB_H_ */
