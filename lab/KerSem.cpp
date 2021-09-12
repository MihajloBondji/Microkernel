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
#include <stdio.h>

ListSem* KerSem::listAllSem=new ListSem();

KerSem::KerSem(int val):value(val){
	this->blockedThreadsList=new List();
	this->listAllSem->add(this);
}


int KerSem::wait(Time maxWait){
	value--;
	if(value>=0) return -1;
#ifndef BCC_BLOCK_IGNORE
		asm {pushf;cli};
#endif
	PCB::running->setMyThreadState(PCB::BLOCKED);
	this->blockedThreadsList->add(PCB::running,maxWait);
#ifndef BCC_BLOCK_IGNORE
		asm {popf};
#endif
	if(maxWait!=0)
		PCB::running->imFromWaitTimeOut=1;
	dispatch();
	if(PCB::running->imFromWaitTimeOut==1)
	{
		PCB::running->imFromWaitTimeOut=0;
		return 0;
	}
	return 1;
}

int KerSem::signal(int n){
	if(n<0)return n;
	if(n==0)
		n=1;
	int j=0;
	if(value<0)
	{
		j = ( (n > -1 * value) ? -1 * value : n );
#ifndef BCC_BLOCK_IGNORE
		asm {pushf;cli};
#endif
		for(int i=0;i<j;i++)
		{
			PCB* pom=this->blockedThreadsList->remove();
			pom->myThreadState = PCB::READY;
			Scheduler::put(pom);
		}
#ifndef BCC_BLOCK_IGNORE
		asm {popf};
#endif
	}
	value+=n;
	return j;
}

KerSem::~KerSem(){
	listAllSem->remove(this);
#ifndef BCC_BLOCK_IGNORE
		asm {pushf;cli};
#endif
	blockedThreadsList->freeBlocked();
#ifndef BCC_BLOCK_IGNORE
		asm {popf};
#endif
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
				pom->data->setMyThreadState(PCB::READY);
				Scheduler::put(pom->data);
				List::pcbelem* pom2=pom;
				pom=pom->next;
				blockedThreadsList->remove(pom2->data->getThreadId());
			}
			else{pom=pom->next;}
		}
		else pom=pom->next;
	}
}
