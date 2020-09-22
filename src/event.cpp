/*
 * event.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */



#include "event.h"
#include "kevent.h"
#include "system.h"

Event::Event(IVTNo ivtNo){
	lock
	myImpl = new KernelEv(ivtNo);
	unlock
}
Event::~Event(){
	lock
	delete myImpl;
	unlock
}
void Event::wait(){
	lock
	myImpl->wait();
	unlock
}

void Event::signal(){
	lock
	myImpl->signal();
	unlock
}

