/*
 * listsem.h
 *
 *  Created on: Sep 1, 2021
 *      Author: OS1
 */

#ifndef LISTSEM_H_
#define LISTSEM_H_
#include "thread.h"
#include "KerSem.h"
class ListSem{
public:
	ListSem();
	virtual ~ListSem();

	struct pcbelem{
		KerSem* data;
		pcbelem* next;
		pcbelem(KerSem* d){
			data=d;
			next=0;
		}
	};

	pcbelem *first;
	pcbelem *last;

	void add(KerSem* sem);
	KerSem* getAndRemove();
	void remove(KerSem*);
	void deleteList();
	static void updateTime(ListSem* semaphoresList);
};


#endif /* LISTSEM_H_ */
