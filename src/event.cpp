/*
 * event.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: OS1
 */

#include "event.h"
#include "kerevent.h"

Event::Event(IVTNo ivtNo) {
	myImpl = new KernelEv(ivtNo);
}

Event::~Event() {
	delete myImpl;
}

void Event::wait() {
if(myImpl==0)return;
myImpl->wait();
}

void Event::signal() {
if(myImpl==0)return;
myImpl->signal();
}


