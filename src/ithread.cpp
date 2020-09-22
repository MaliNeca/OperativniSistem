/*
 * ithread.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: OS1
 */




#include "ithread.h"
#include "pcb.h"
IThread::IThread() : Thread(800,1){

}

void IThread::start(){
	this->myPCB->status = READY;
	this->myPCB->createStack();
}

void IThread::run(){
	while(1){}
}
