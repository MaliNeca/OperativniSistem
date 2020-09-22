/*
 * pcb.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: OS1
 */

#include "pcb.h"
#include <stdlib.h>
#include <iostream.h>
#include <dos.h>
#include "system.h"
#include "SCHEDULE.H"
#include "thread.h"


PCB::PCB(Thread *myThread, StackSize stackSize, Time timeSlice) {
	this->myThread = myThread;
//	if (stackSize < 0x8000)
//		this->stackSize = 0x8000;
//	else
		this->stackSize = stackSize;

	this->timeSlice = timeSlice;
	this->timeToCount = timeSlice;
	this->ss = 0;
	this->sp = 0;
	this->bp = 0;
	this->status = NEW;
	this->stack = NULL;
	this->blockedQueue = new Queue();
	this->val = 0;

}
PCB::~PCB() {

	delete[] stack;
	delete blockedQueue;

}
void PCB::createStack() {
	lock
	this->stack = new unsigned[this->stackSize / sizeof(unsigned)];

	this->stackSize = this->stackSize / sizeof(unsigned);


	stack[stackSize-1] = 0x200;

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-2] = FP_SEG(PCB::runWrapper);
	stack[stackSize-3] = FP_OFF(PCB::runWrapper);

	sp = FP_OFF(stack + stackSize - 12);
	ss = FP_SEG(stack + stackSize - 12);


#endif
	unlock
}

void PCB::runWrapper() {

		System::running->myThread->run();
		lock

		System::running->status= OVER;
		while(System::running->blockedQueue->first != 0 ){
			PCB *pcb = System::running->blockedQueue->getFirst();
			pcb->status = READY;
			Scheduler::put(pcb);

		}
		unlock

		System::dispatch();


}

