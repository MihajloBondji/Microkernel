/*
 * semaphor.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: OS1
 */
#include "semaphor.h"
#include "KerSem.h"

Semaphore::Semaphore(int i) {
	this->myImpl = new KerSem(i);
}

Semaphore::~Semaphore() {
	delete myImpl;
	myImpl = 0;
}

int Semaphore::wait(Time maxTimeToWait) {
	if(myImpl == 0) return 0;
	return myImpl->wait(maxTimeToWait);
}

int Semaphore::signal(int n) {
	return myImpl->signal(n);
}

int Semaphore::val() const {
	if(myImpl == 0) return 0;
return myImpl->value;
}


