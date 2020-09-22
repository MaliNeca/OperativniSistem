/*
 * Queue.h
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#ifndef H_QUEUE_H_
#define H_QUEUE_H_

#include "pcb.h"

class Queue {
private:
	struct Elem {
		PCB *pcb;
		Elem *next;
		Time timeToSleep;
		Elem(PCB *p, Time tts = 0) {
			pcb = p;
			next = 0;
			timeToSleep = tts;
		}
	};
	friend class PCB;

public:
	Elem *first, *last;

	Queue() {
		first = 0;
		last = 0;
	}
	;

	void put(PCB *p);
	PCB *getFirst();
	void putSleep(PCB *p, Time tts);
	~Queue();

};

#endif /* H_QUEUE_H_ */
