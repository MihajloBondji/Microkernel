/*
 * KerSem.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: OS1
 */
#include "kersem.h"
#include "listsem.h"
#include "list.h"
#include "Thread.h"
#include "pcb.h"
#include "SCHEDULE.h"

ListSem* KerSem::listAllSem=new ListSem();

KerSem::KerSem(int val):value(val){
	this->blockedThreadsList=new List();
	this->listAllSem->add(this);
}


int KerSem::wait(Time maxWait){
	value--;
	if(value>=0) return -1;

	PCB::running->setMyThreadState(PCB::BLOCKED);
	this->blockedThreadsList->add(PCB::running);
	if(maxWait!=0)
		PCB::running->imFromWaitTimeOut=1;
	dispatch();
	if(PCB::running->imFromWaitTimeOut==1)
	{
		PCB::running->imFromWaitTimeOut=0;
		return 1;
	}
	return 0;
}

int KerSem::signal(int n){
	if(n<0)return n;
	if(n==0)
		n=1;
	int j=0;
	if(value<0)
	{
		j = ( (n > -1 * value) ? -1 * value : n );
		for(int i=0;i<j;i++)
		{
			PCB* pom=this->blockedThreadsList->remove();
			pom->myThreadState = PCB::READY;
			Scheduler::put(pom);
		}
	}
	value+=n;
	return j;
}

KerSem::~KerSem(){
	listAllSem->remove(this);
	blockedThreadsList->freeBlocked();
	delete blockedThreadsList;
	value=0;
}

void KerSem::updateTime(){
	ListSem::kerelem* pom=listAllSem->first;
	while(pom)
	{
		pom->data->updateTime2();
		pom=pom->next;
	}
}

void KerSem::updateTime2(){
	List::pcbelem* pom=this->blockedThreadsList->first;
	while(pom){
		if(pom->myWaitState==List::TIME)
		{
			pom->maxWait--;
			if(pom->maxWait==0)
			{
				Scheduler::put(pom->data);
				blockedThreadsList->remove(pom->data->getThreadId());
			}
		}
		pom=pom->next;
	}
}
