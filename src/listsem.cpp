/*
 * listsem.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: OS1
 */
#include "listsem.h"
#include "kersem.h"

ListSem::ListSem() {
	first=0;
	last=0;
}


void ListSem::add(KerSem* sem){
	if(first)
		{
			last->next=new kerelem(sem);
			last=last->next;
		}
	else {
		first=last=new kerelem(sem);
	}
}

void ListSem::remove(KerSem* sem){
	kerelem* pom=first;
	if(first->data==sem)
	{
		if(first==last)
			first=last=0;
		else
		first=first->next;
		delete pom;
		return;
	}
	pom=first->next;
	kerelem* pret=first;
	while(pom)
	{
		if(pom->data==sem)
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

KerSem* ListSem::getAndRemove() {
	if(first==0) return 0;

	kerelem* pom=first;
	while(pom)
		{
			if(pom->data==this)
			{
				KerSem* pomker=pom->data;
				remove(pom->data);
				return pomker;
			}
			else pom=pom->next;
		}
	return 0;
}

void ListSem::deleteList(){
	kerelem* pom = 0;
		while(first!=0){
			pom=first;
			first=first->next;
			pom->data = 0;
			pom->next=0;
			delete pom;
		}
		first = 0;
		last = 0;
}

ListSem::~ListSem() {
	deleteList();
}
