/*
 * ksem.cpp
 *
 *  Created on: Aug 28, 2018
 *      Author: OS1
 */



#include "ksem.h"
#include "pcb.h"
#include "schedule.h"
#include "system.h"



KernelSem::KernelSem(int init){
	this->val = init;
	this->semQueue = new Queue();
}
KernelSem::~KernelSem(){
	PCB *pcb;
	while(this->semQueue->first ){
		pcb = this->semQueue->getFirst();
		pcb->status = READY;
		Scheduler::put(pcb);
	}
	delete this->semQueue;
}
int KernelSem::wait(int toBlock){
	lock
	if(toBlock!=0){
		if(--val<0){
			System::running->status = BLOCKED;
			semQueue->put(System::running);
			System::dispatch();
			unlock
			return 1;
		}

		unlock
		return 0;
	}

	if(this->val<=0){
		unlock
		return -1;
	}
	this->val--;
	unlock
	return 0;


}

void KernelSem::signal(){
	lock
	if(this->val++ < 0 && semQueue->first ){

		PCB *pcb = semQueue->getFirst();
		pcb->status = READY;
		Scheduler::put(pcb);
	}
	unlock
}

int KernelSem::value() const {
	return this->val;
}

