/*
 * uthread.h
 *
 *  Created on: Aug 27, 2018
 *      Author: OS1
 */

#ifndef H_UTHREAD_H_
#define H_UTHREAD_H_

#include "thread.h"

extern int userMain(int argc, char *argv[]);

class UThread : public Thread{
public:
	UThread(int argc, char *argv[]);
	char **argv;
	int argc, retValue;

protected:
	void run();

};

#endif /* H_UTHREAD_H_ */
