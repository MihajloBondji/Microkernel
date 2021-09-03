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
asm {pushf;cli};
defaultRoutine = getvect(ivtNo);
setvect(ivtNo,routine);

ivtEntry[ivtNo] = this;
this->ivtNo = ivtNo;
asm {popf};
#endif
}

void IVTEntry::setEvent(KernelEv* kernelEvent) {
#ifndef BCC_BLOCK_IGNORE
	asm {pushf;cli};
#endif
	this->myKernelEvent = kernelEvent;
#ifndef BCC_BLOCK_IGNORE
	asm {popf};
#endif
}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	asm {pushf;cli};
	setvect(ivtNo, defaultRoutine);
	if(ivtEntry) ivtEntry[ivtNo] = 0;
	if(ivtNo!=0)ivtNo = 0;
	asm {popf};
	#endif
	if(defaultRoutine!=0)defaultRoutine = 0;
	if(myKernelEvent!=0)myKernelEvent = 0;
}
void IVTEntry::signal() {
	if(myKernelEvent == 0) return;

	myKernelEvent->signal();
}

