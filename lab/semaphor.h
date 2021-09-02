// File: semaphor.h
#ifndef _semaphor_h_
#define _semaphor_h_
#include "thread.h"
class Semaphore {

public:
	Semaphore (int init=1);
	virtual ~Semaphore ();
	virtual int wait (Time maxTimeToWait);
	virtual int signal(int i);
	int val () const; // Returns the current value of the semaphore

private:
	friend class KerSem;
	KerSem* myImpl;

};
#endif
