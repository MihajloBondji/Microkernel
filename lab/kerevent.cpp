/*
 * kerevent.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: OS1
 */

#include "kerevent.h"
#include "contex.h"
#include "pcb.h"
#include "ivtentry.h"
#include "SCHEDULE.h"


KernelEv::KernelEv(IVTNo ivtNo):ivtNo(ivtNo) {
#ifndef BCC_BLOCK_IGNORE
	owner =(PCB * ) PCB::running;
	ownerBlocked = 0;
    if(IVTEntry::ivtEntry==0) {}
    else IVTEntry::ivtEntry[ivtNo]->setEvent(this);
#endif
}

void KernelEv::wait(){
	if (ownerBlocked!=0) return;
		setOwnerBlocked(1);
		PCB::running->setMyThreadState(PCB::BLOCKED);
        dispatch();
}

void KernelEv::signal() {

	if(ownerBlocked!=1) return;

	owner->setMyThreadState(PCB::READY);
	setOwnerBlocked(0);
	Scheduler::put(owner);
	dispatch();

}

KernelEv::~KernelEv() {
	setOwnerBlocked(0);
	owner = 0;
	if(IVTEntry::ivtEntry!=0 && IVTEntry::ivtEntry[ivtNo] !=0)
		IVTEntry::ivtEntry[ivtNo]->setEvent(0);
	ivtNo = 0;
}

void KernelEv::setOwnerBlocked(int i){this->ownerBlocked=i;}
int KernelEv::getOwnerBlocked(){return this->ownerBlocked;}
