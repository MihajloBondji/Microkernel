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

	struct kerelem{
		KerSem* data;
		kerelem* next;
		kerelem(KerSem* d){
			data=d;
			next=0;
		}
	};

	kerelem *first;
	kerelem *last;

	void add(KerSem* sem);
	KerSem* getAndRemove();
	void remove(KerSem*);
	void deleteList();
};


#endif /* LISTSEM_H_ */
