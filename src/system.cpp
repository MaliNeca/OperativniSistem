#include "system.h"

#include<iostream.h>
#include<stdlib.h>
#include<stdio.h>
#include "pcb.h"
#include <dos.h>
#include "SCHEDULE.H"



volatile int System::forced = 0;
pInterrupt System::oldRoutine = 0;
PCB* System::running = 0;
PCB* System::idlle = 0;
Queue *System::sleepQueue = 0;
Queue *System::pcbList = 0;
volatile unsigned int System::change = 0;
unsigned tsp,tss,tbp;
IThread *idlleTh;
int System::retValue = 0;
PCB* System::starting = 0;

void System::dispatch(){
#ifndef BCC_BLOCK_IGNORE
	asm{pushf;cli;}
#endif
	forced = 1;
	System::timer();
#ifndef BCC_BLOCK_IGNORE
	asm{popf;}
#endif

}
void System::sleepUp(){
	if(sleepQueue->first && sleepQueue){
		if(sleepQueue->first->timeToSleep>0) sleepQueue->first->timeToSleep--;
		while(sleepQueue->first && sleepQueue->first->timeToSleep == 0){
			PCB *pcb = sleepQueue->getFirst();
			pcb->status = READY;
			Scheduler::put(pcb);
		}
	}
}
void interrupt System::timer(...){
	if(!forced){
		(*oldRoutine)();
		System::running->timeToCount--;
		System::sleepUp();
		tick();
	}

	if(forced || (System::running->timeToCount <= 0 && System::running->timeSlice !=0)){
		if((!forced) && (System::running->val >0 )){
			change = 1;
			return;
		}
		forced = 0;

#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tsp, SP
			mov tss, SS
			mov tbp, BP
		}
#endif
		System::running->sp = tsp;
		System::running->ss = tss;
		System::running->bp = tbp;

		if(System::running->status == READY && System::running!= System::idlle){
			Scheduler::put(System::running);
		}

		System::running = Scheduler::get();
		if(System::running == 0) System::running = System::idlle;

		tsp = System::running->sp;
		tss = System::running->ss;
		tbp = System::running->bp;

#ifndef BCC_BLOCK_IGNORE
		asm{
			mov SP, tsp
			mov SS, tss
			mov BP, tbp
		}
#endif
		System::running->timeToCount= System::running->timeSlice;
	}


}

void System::replaceRoutine(){
#ifndef BCC_BLOCK_IGNORE
	asm{pushf;cli;}


	System::oldRoutine=getvect(0x08);
	setvect(0x08,System::timer);
	setvect(0x60,System::oldRoutine);
	asm{popf;}




#endif
}


void System::initialization(){

	pcbList = new Queue();
	sleepQueue = new Queue();
	System::forced = 0;
	System::running = new PCB(0,0,0);
	System::running->timeSlice = 0;

	System::starting = System::running;
	System::running->status = READY;

	idlleTh = new IThread();
	System::idlle = idlleTh->myPCB;
	idlleTh->start();

	System::replaceRoutine();

}

void System::restore(){
#ifndef BCC_BLOCK_IGNORE
	asm{pushf;cli;}

	System::oldRoutine = getvect(0x60);
	setvect(0x08,System::oldRoutine);
	asm{popf;}

#endif

	delete idlle->myThread;
	delete System::running;
	delete sleepQueue;
	delete pcbList;
}
