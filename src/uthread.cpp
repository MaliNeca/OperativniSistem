/*
 * uthread.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: OS1
 */

#include "uthread.h"
#include <iostream.h>

UThread::UThread(int argc, char *argv[]) : Thread(2*defaultStackSize,0){
	this->argc = argc;
	this->argv = argv;
	retValue = 0;
}

void UThread::run(){
	this->retValue = userMain(this->argc, this->argv);
}
