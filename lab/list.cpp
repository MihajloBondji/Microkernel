/*
 * list.cpp
 *
 *  Created on: Aug 30, 2021
 *      Author: OS1
 */

#include "list.h"
#include "thread.h"
#include "pcb.h"
#include "SCHEDULE.H"


List::List() {
	first=0;
	last=0;
}


PCB* List::get(int id=0) {
	if(first==0) return 0;
	if(id==0) return 0;

	pcbelem* pom=first;
	while(pom)
		{
			if(pom->data->myThread->getId()==id)
				return pom->data;
			else pom=pom->next;
		}
	return 0;
}

PCB* List::remove(){
	if(first!=0){
	pcbelem* pom=first;
	PCB* pompcb=pom->data;
	if(first->next!=0)
		first=first->next;
	else first=last=0;
	delete pom;
	return pompcb;
	}
	else
	return 0;
}

void List::remove(int id){
	pcbelem* pom=first;
	if(first->data->getThreadId()==id)
	{
		if(first==last)
			first=last=0;
		else
		first=first->next;
		delete pom;
		return;
	}
	pom=first->next;
	pcbelem* pret=first;
	while(pom)
	{
		if(pom->data->getThreadId()==id)
			{
				pret->next=pom->next;
				if(pom==last)
					last=pret;
				delete pom;
				return;
			}
		pret=pom;
		pom=pom->next;
	}
}

void List::freeBlocked(){
	if(!first) return;
	for(pcbelem* tek =first; tek; tek=tek->next){
		if(tek->data->myThreadState!=PCB::DONE){
			tek->data->myThreadState = PCB::READY;
			Scheduler::put(tek->data);
		}
	}

}

void List::deleteList(){
	pcbelem* pom = 0;
		while(first){
			pom=first;
			first=first->next;
			pom->data = 0;
			pom->next=0;
			delete pom;
		}
		first = last = 0;
}

List::~List() {
	deleteList();
}

void List::add(PCB* pcb){
	if(first)
		{
			last->next=new pcbelem(pcb);
			last=last->next;
		}
	else {
		first=last=new pcbelem(pcb);
	}
}





