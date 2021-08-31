/*
 * thread.cpp
 *
 *  Created on: Aug 30, 2021
 *      Author: OS1
 */
#include "thread.h"
#include <iostream.h>
#include "SCHEDULE.h"
#include "contex.h"
#include "pcb.h"
#include "list.h"

volatile ID Thread::id = 1;


Thread::Thread(StackSize stackSize,Time timeSlice){
	myPCB=new PCB(this,stackSize,timeSlice);
	myWaitingList=new List();
	myID=id++;
}

void Thread::start() {
	if(this->myPCB->myThreadState!=PCB::CREATED)
	{
		return;
	}
	this->myPCB->myThreadState=PCB::READY;
	Scheduler::put(myPCB);
}

ID Thread::getId() {
		return myID;
	}

ID Thread::getRunningId(){
	return PCB::running->myThread->myID;
}

Thread * Thread::getThreadById(ID id){
	return PCB::listAll->get(id)->myThread;
}

Thread::~Thread() {
	if (myPCB != 0) {
		//myPCB->waitToComplete();
		myPCB->myThread = 0;
		delete myPCB;
		myPCB = 0;
	}
}

void Thread::waitToComplete(){

	this->myWaitingList->add(PCB::running);
	PCB::running->myThreadState=PCB::BLOCKED;
	dispatch();
}
void dispatch() {
	//Context::preemptionOnRequest = 1;
#ifndef BCC_BLOCK_IGNORE
	asm int 0x08
#endif
}
