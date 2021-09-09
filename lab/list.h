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
	enum wait{ZERO,TIME};
	struct pcbelem{
		PCB* data;
		pcbelem* next;
		Time maxWait;
		wait myWaitState;
		pcbelem(PCB* d,Time mw=0){
			data=d;
			next=0;
			maxWait=mw;
			myWaitState=(mw==0?ZERO:TIME);
		}
	};

	pcbelem *first;
	pcbelem *last;

	void add(PCB* pcb,Time mw=0);
	PCB* get(int id);
	void freeBlocked();
	PCB* remove();
	void remove(int id);
	void deleteList();

};



#endif /* LIST_H_ */
