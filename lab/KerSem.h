/*
 * KerSem.h
 *
 *  Created on: Sep 1, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_
#include "thread.h"
class KerSem{
public:
	friend class Semaphore;
	friend class ListSem;
	friend class List;
	int signal(int n=0);
	int wait(Time maxWait);
	static ListSem* listAllSem;
	static void updateTime();
	void updateTime2();
protected:
	KerSem(int val);
	~KerSem();
	int getVal();

private:
	int value;
	List* blockedThreadsList;
};



#endif /* KERSEM_H_ */
