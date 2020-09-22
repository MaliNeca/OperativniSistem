/*
 * kevent.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */



#include "kevent.h"
#include "ivt.h"
#include "system.h"


KernelEv::KernelEv(IVTNo ivtNo){
	if(IVTEntry::ivTable[ivtNo]){
		this->myThread = System::running->myThread;
		this->ivtNo = ivtNo;
		this->mySem = new KernelSem(0);
		IVTEntry::ivTable[this->ivtNo]->myEvent = this;
	}
}

KernelEv::~KernelEv(){
	IVTEntry::ivTable[ivtNo]->myEvent = 0;
	delete mySem;
}

void KernelEv::wait(){
	lock
	if(System::running->myThread != this->myThread ) return;
	mySem->wait(0);
	unlock
}

void KernelEv::signal(){
	if(mySem->val == 1) return;
	mySem->signal();
}
