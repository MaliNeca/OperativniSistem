/*
 * semaphore.cpp
 *
 *  Created on: Aug 28, 2018
 *      Author: OS1
 */




#include "../h/semaphor.h"
#include "ksem.h"
#include "system.h"
#include "schedule.h"

Semaphore::Semaphore(int init){
	lock
	myImpl = new KernelSem(init);
	unlock
}

Semaphore::~Semaphore(){
	lock
	delete myImpl;
	unlock
}

int Semaphore::wait(int toBlock){
	lock
	int ret = myImpl->wait(toBlock);
	unlock
	return ret;
}

void Semaphore::signal(){
	lock
	myImpl->signal();
	unlock
}

int Semaphore::val() const{
	return myImpl->value();
}
