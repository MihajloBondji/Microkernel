/*
 * contex.cpp
 *
 *  Created on: Aug 31, 2021
 *      Author: OS1
 */

#include "contex.h"
#include "SCHEDULE.h"
#include "pcb.h"
#include "thread.h"
#include "idle.h"
#include "KerSem.h"
#include <stdio.h>

extern void tick();
unsigned tmpsp=0;
unsigned tmpss=0;
unsigned tmpbp=0;
interruptPointer Context::timerRoutine;
volatile int Context::request=0;
volatile int Context::timeleft=0;

void interrupt Context::timer(...) {

	if(request==0)
		{
		KerSem::updateTime();
		if(timeleft>=0)
				timeleft--;
			#ifndef  BCC_BLOCK_IGNORE
					asm int 60h;
			#endif
			tick();
		}
	if(timeleft==0||request)
	{
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tmpsp, sp
			mov tmpss, ss
			mov tmpbp, bp
		}
#endif

	if(PCB::running!=0)
	{
		PCB::running->Context.sp = tmpsp;
		PCB::running->Context.ss = tmpss;
		PCB::running->Context.bp = tmpbp;
		if (PCB::running->getMyThreadState() == PCB::RUNNING) {
			PCB::running->setMyThreadState(PCB::READY);
			Scheduler::put((PCB *) PCB::running);
		}
	}


		if ((PCB::running = Scheduler::get()) != 0)
			PCB::running->setMyThreadState(PCB::RUNNING);
		else{
			PCB::running = PCB::idle;
			PCB::running->setMyThreadState(PCB::IDLE);
		}

		tmpsp = PCB::running->Context.sp;
		tmpss = PCB::running->Context.ss;
		tmpbp = PCB::running->Context.bp;
		timeleft = PCB::running->getMyThreadTimeSlice();

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tmpsp
			mov ss, tmpss
			mov bp, tmpbp
		}
#endif
	}
		request=0;
}

void Context::init() {
	PCB::main = (new Thread(300, 5))->getMyPCB();
	PCB::main->setMyThreadState(PCB::RUNNING);
	PCB::running = PCB::main;
	PCB::idle = (new Idle())->getMyPCB();
	PCB::idle->setMyThreadState(PCB::IDLE);
	timeleft = PCB::main->getMyThreadTimeSlice();

#ifndef BCC_BLOCK_IGNORE
	asm {pushf;cli};
	timerRoutine = getvect(0x08);
	setvect(0x08,timer);
	setvect(0x60,timerRoutine);
	asm {popf};
#endif
}

void Context::restore() {
	delete PCB::idle->getMyThread();
	delete PCB::main->getMyThread();
#ifndef BCC_BLOCK_IGNORE
	asm cli
	setvect(0x08,timerRoutine);
	asm sti
#endif
	PCB::idle = 0;
	PCB::main = 0;
	PCB::listAll = 0;
	PCB::running = 0;
}
