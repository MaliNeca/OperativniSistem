/*
 * event.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef H_EVENT_H_
#define H_EVENT_H_
#include "ivt.h"
typedef unsigned char IVTNo;
class KernelEv;



class Event {
public:
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();
protected:

 friend class KernelEv;
 void signal(); // can call KernelEv
private:
 KernelEv* myImpl;
};



#endif /* H_EVENT_H_ */
