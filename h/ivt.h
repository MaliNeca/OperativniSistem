/*
 * ivt.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef H_IVT_H_
#define H_IVT_H_
#include "kevent.h"
#include "system.h"
typedef void interrupt(*pInterrupt)(...);

#define PREPAREENTRY(ivtno,old) \
void interrupt routine##ivtno(...);\
		IVTEntry ent##ivtno(ivtno,routine##ivtno);\
void interrupt routine##ivtno(...){\
			if(old) ent##ivtno.callOld();\
			ent##ivtno.signal();\
		}

class IVTEntry{
public:
	static IVTEntry *ivTable[];
	unsigned ivtNum;
	KernelEv *myEvent;
	pInterrupt old;
	IVTEntry(unsigned ivtNum, pInterrupt New);
	~IVTEntry();
	void signal();
	void callOld();
};


#endif /* H_IVT_H_ */
