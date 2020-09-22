/*
 * kevent.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef H_KEVENT_H_
#define H_KEVENT_H_
#include "ksem.h"
#include "pcb.h"
#include "thread.h"
typedef unsigned char IVTNo;

class KernelEv{
public:
	IVTNo ivtNo;
	KernelSem *mySem;

	KernelEv (IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal();
private:
	Thread *myThread;
};



#endif /* H_KEVENT_H_ */
