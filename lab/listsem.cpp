/*
 * listsem.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: OS1
 */
#include "listsem.h"
#include "kersem.h"

void ListSem::add(KerSem* sem){
	if(first)
		{
			last->next=new pcbelem(sem);
			last=last->next;
		}
	else {
		first=last=new pcbelem(sem);
	}
}

void ListSem::remove(KerSem* sem){
	pcbelem* pom=first;
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
	pcbelem* pret=first;
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

	pcbelem* pom=first;
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
