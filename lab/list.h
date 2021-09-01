/*
 * list.h
 *
 *  Created on: Aug 30, 2021
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_
#include "thread.h"
class List{
public:
	List();
	virtual ~List();

	friend class PCB;
	friend class Thread;

	struct pcbelem{
		PCB* data;
		pcbelem* next;
		Time maxWait;
		pcbelem(PCB* d,Time mw=0){
			data=d;
			next=0;
			maxWait=mw;
		}
	};

	pcbelem *first;
	pcbelem *last;

	void add(PCB* pcb);
	PCB* get(int id);
	void freeBlocked();
	void remove();
	void remove(int id);
	void deleteList();
};



#endif /* LIST_H_ */
