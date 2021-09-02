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
	dispatch();

	return maxWait?1:0;
}

int KerSem::signal(int n){

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
	}
}

void KerSem::updateTime2(){

}
