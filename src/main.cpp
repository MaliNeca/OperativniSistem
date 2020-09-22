/*
 * main.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: OS1
 */
#include <iostream.h>
#include "system.h"
#include <stdlib.h>

extern int userMain(int argc, char *argv[]);

int main(int argc, char * argv[]){

	System::initialization();

	System::retValue = userMain(argc,argv);
	System::restore();
	return System::retValue;
}
