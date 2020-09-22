/*
 * queue.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#include "queue.h"

void Queue::put(PCB *p) {
	Elem *elem = new Elem(p);
	if (!first) {
		first = elem;

	} else {
		last->next = elem;
	}
	last = elem;
}

PCB *Queue::getFirst() {

	if (first) {
		Elem *elem = first;
		first = first->next;
		if (!first)
			last = 0;
		return elem->pcb;
	}
	return 0;
}
Queue::~Queue() {
	Elem *curr, *next;
	if (first) {
		curr = first;
		while (curr) {
			next = curr->next;
			delete (curr);
			curr = next;
		}
	}
	first = 0;
	last = 0;
}

void Queue::putSleep(PCB *p, Time tts){
	Elem *elem = new Elem(p,tts);
	Elem *tek;
	if(!first){
		first = elem;
		last = elem;
	}else if(tts<first->timeToSleep){
		tek = first;
		first = elem;
		first->next = tek;
		tek->timeToSleep = tek->timeToSleep - first->timeToSleep;
			}else{
				tek = first;
				while(tek->next){
					if((elem->timeToSleep-tek->timeToSleep)<tek->next->timeToSleep){
						elem->next = tek->next;
						tek->next = elem;
						elem->timeToSleep = elem->timeToSleep - tek->timeToSleep;
						elem->next->timeToSleep = elem->next->timeToSleep - elem->timeToSleep;
						return;



					}
					elem->timeToSleep= elem->timeToSleep - tek->timeToSleep;
					tek=tek->next;
				}
				tek->next = elem;
				elem->timeToSleep = elem->timeToSleep - tek->timeToSleep;
				last = elem;

			}

}
