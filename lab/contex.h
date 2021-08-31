/*
 * contex.h
 *
 *  Created on: Aug 30, 2021
 *      Author: OS1
 */
#include "DOS.H"
#ifndef CONTEX_H_
#define CONTEX_H_

typedef void interrupt(*interruptPointer )(...);
class Context{
public:
	static volatile int timeleft;
	static volatile int request;

	static interruptPointer timerRoutine;
	static void interrupt timer(...);

static void init();
static void restore();
protected:
friend class PCB;
friend class Thread;
};


#endif /* CONTEX_H_ */
