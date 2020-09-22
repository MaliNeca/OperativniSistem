/*
 * ivt.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include "ivt.h"
#include "system.h"
#include <dos.h>
#include <iostream.h>
#include <stdlib.h>

IVTEntry *IVTEntry::ivTable[256];

IVTEntry::IVTEntry(unsigned int ivtNum, pInterrupt New){
	lock
	ivTable[ivtNum] = this;
	this->ivtNum = ivtNum;
	this->myEvent = NULL;
#ifndef BCC_BLOCK_IGNORE
	old = getvect(this->ivtNum);
	setvect(this->ivtNum,New);
#endif
	unlock
}

IVTEntry::~IVTEntry(){
	lock
#ifndef BCC_BLOCK_IGNORE
	setvect(this->ivtNum,old);
#endif
	unlock
}



void IVTEntry::signal(){
	lock
	if(myEvent) myEvent->signal();
	unlock
}
void IVTEntry::callOld(){
	if(old) (*old)();
}

