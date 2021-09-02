/*
 * pcb.h
 *
 *  Created on: Aug 30, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"

struct context{
	unsigned ss;
	unsigned sp;
	unsigned bp;
};

class PCB{
public:
	static PCB* running, *main, *idle;
	static ID mainId, idleId;
	unsigned* stack;
	context Context;
	 friend class List;
	 static List* listAll;

	 static void wrapper();

	enum state{CREATED,BLOCKED,STARTED,DELETED,READY,RUNNING,IDLE,DONE};
	//getters
	Thread* getMyThread();
	void setMyThreadState(state s);
	Time getMyThreadTimeSlice();
	ID getThreadId();
protected:
	friend class Thread;
	friend class List;
	friend class Contex;
	friend class KerSem;
	Time myThreadTimeSlice;
	PCB(Thread* thread, StackSize stackSize, Time timeSlice);
	~PCB();
	state myThreadState;
	Thread *myThread;
	int imFromWaitTimeOut;
private:
	ID threadId;
	StackSize myThreadStackSize;
	void deletePointers();
	//State myThreadState;
};


#endif /* PCB_H_ */
