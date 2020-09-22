/*
 * system.h
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#ifndef H_SYSTEM_H_
#define H_SYSTEM_H_



#include "thread.h"
#include "pcb.h"
#include "ithread.h"


typedef void interrupt(*pInterrupt)(...);

#define unlock if(System::running->val == 1 && System::change == 1){\
	System::change = 0;\
	System::dispatch();\
}\
System::running->val--;
#define lock System::running->val++;



class System{


public:
	static PCB *idlle;
	static PCB *running;
	static PCB *starting;
	friend class PCB;
	static void dispatch();
	static Queue *sleepQueue;
	static Queue *pcbList;
	static int retValue;
	volatile static unsigned int change;
	volatile static int forced;

	static void interrupt timer(...);

	static pInterrupt oldRoutine;

	static void replaceRoutine();
	static void restoreInterrupt();

	static void sleepUp();
	static void initialization();
	static void restore();

	friend class PCB;
	friend class Queue;
	friend class Thread;
};
extern void tick();

#endif /* H_SYSTEM_H_ */
