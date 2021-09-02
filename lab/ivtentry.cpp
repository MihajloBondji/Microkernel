/*
 * ivtentry.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: OS1
 */

#include "ivtentry.h"
#include "kerevent.h"
#include <dos.h>
#include "contex.h"

IVTEntry* IVTEntry::ivtEntry[256];

IVTEntry::IVTEntry(IVTNo ivtNo,interruptPointer routine){

myKernelEvent = 0;
#ifndef BCC_BLOCK_IGNORE
defaultRoutine = getvect(ivtNo);
setvect(ivtNo,routine);

ivtEntry[ivtNo] = this;
this->ivtNo = ivtNo;
#endif
}

void IVTEntry::setEvent(KernelEv* kernelEvent) {
	this->myKernelEvent = kernelEvent;
}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, defaultRoutine);
	defaultRoutine = 0;
	myKernelEvent = 0;
	if(ivtEntry!=0) ivtEntry[ivtNo] = 0;
	ivtNo = 0;
	#endif
}
void IVTEntry::signal() {
	if(myKernelEvent == 0) return;

	myKernelEvent->signal();
}

