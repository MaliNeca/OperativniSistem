/*
 * thread.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: OS1
 */

#include "system.h"

#include <iostream.h>
#include <stdlib.h>
#include <dos.h>
#include "SCHEDULE.H"

void Thread::start() {
	lock

	myPCB->status = READY;
	myPCB->createStack();
	Scheduler::put (myPCB);

	unlock

}

	void Thread::waitToComplete() {
	lock
	if (this->myPCB == System::running || this->myPCB->status == OVER || this->myPCB == System::idlle || this->myPCB->status == NEW) {
	unlock

		return;
	}

	System::running->status = BLOCKED;
	this->myPCB->blockedQueue->put(System::running);
	System::dispatch();

	unlock

	}


	 Thread::~Thread(){
	    waitToComplete();
		lock

		delete this->myPCB;
		unlock
	}


	  Thread::Thread(StackSize stackSize, Time timeSlice ){
	  			lock
	  			myPCB = new PCB(this,stackSize,timeSlice);
	  			System::pcbList->put(myPCB);
	  			unlock



	  	}
	  void Thread::sleep(Time timeToSleep){
			if(timeToSleep <=0) return;
			System::running->status = BLOCKED;
			System::sleepQueue->putSleep(System::running,timeToSleep);

			System::dispatch();


		}

	  void dispatch(){
	  	lock
	  	System::dispatch();
	  	unlock
	  }
