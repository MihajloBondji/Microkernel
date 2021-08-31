/*
 * pcb.cpp
 *
 *  Created on: Aug 30, 2021
 *      Author: OS1
 */
#include "pcb.h"
#include "list.h"
#include <dos.h>

PCB* PCB::running = 0;

PCB* PCB::main = 0;
ID PCB::mainId = 0;

PCB* PCB::idle = 0;
ID PCB::idleId = 0;

List* PCB::listAll=new List();

PCB::PCB(Thread* t,StackSize ss,Time ts):myThread(t),myThreadTimeSlice(ts){
	myThreadStackSize=(ss>maxStackSize?maxStackSize:ss)>>1;
	this->myThreadState=CREATED;

	stack = new unsigned[myThreadStackSize];

		stack[myThreadStackSize - 1] = 0x200;
	#ifndef BCC_BLOCK_IGNORE
		stack[myThreadStackSize - 2] = FP_SEG(&PCB::wrapper);
		stack[myThreadStackSize - 3] = FP_OFF(&PCB::wrapper);
		Context.bp = FP_OFF(stack + myThreadStackSize - 12);
		Context.sp = FP_OFF(stack + myThreadStackSize - 12);
		Context.ss = FP_SEG(stack + myThreadStackSize - 12);
	#endif

		this->listAll->add(this);
}

Time PCB::getMyThreadTimeSlice(){
	return this->myThreadTimeSlice;
}

PCB::~PCB(){
  myThread->myPCB = 0;
  //PCB::getPCBList()->remove(this);
}

void PCB::setMyThreadState(PCB::state s){
	myThreadState=s;
}

void PCB::wrapper() {
	PCB::running->myThread->run();
	PCB::running->listAll->freeBlocked();
	dispatch();
}
