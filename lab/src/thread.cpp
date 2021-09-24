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
#include <stdio.h>

volatile ID Thread::id = 1;


Thread::Thread(StackSize stackSize,Time timeSlice){
	myID=id++;
	myWaitingList=new List();
	myPCB=new PCB(this,stackSize,timeSlice);


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
	if (this->myPCB != 0) {
		this->waitToComplete();
		myPCB->myThread = 0;
		delete this->myPCB;
		this->myPCB = 0;
	}
}

void Thread::waitToComplete(){
	if (this->myPCB == PCB::running||this->myPCB == PCB::main||this->myPCB == PCB::idle||this->myPCB->myThreadState == PCB::DELETED||this->myPCB->myThreadState == PCB::CREATED||this->myPCB->myThreadState == PCB::DONE)
		return;
	this->myWaitingList->add((PCB*)PCB::running);
	PCB::running->myThreadState=PCB::BLOCKED;
	dispatch();
}
void dispatch() {
	Context::request = 1;
#ifndef BCC_BLOCK_IGNORE
	asm int 0x08
#endif
}


PCB* Thread::getMyPCB(){
	return this->myPCB;
}
