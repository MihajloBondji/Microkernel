/*
 * list.h
 *
 *  Created on: Aug 30, 2021
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

class List{
public:
	List();
	virtual ~List();

	friend class PCB;
	friend class Thread;

	struct pcbelem{
		PCB* data;
		pcbelem* next;

		pcbelem(PCB* d){
			data=d;
			next=0;
		}
	};

	pcbelem *first;
	pcbelem *last;

	void add(PCB* pcb);
	PCB* get(int id);
	void listDel();
	void freeBlocked();
	void remove();
	void deleteList();
};



#endif /* LIST_H_ */
