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

void tick();
unsigned tmpsp=0;
unsigned tmpss=0;
unsigned tmpbp=0;
volatile int Context::request=0;
volatile int Context::timeleft=0;

void interrupt Context::timer(...) {

	if((request==0)&&timeleft>=0)
		timeleft=0;
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
		PCB::running->setMyThreadState(PCB::READY);
		Scheduler::put((PCB *) PCB::running);
	}


		if ((PCB::running = Scheduler::get()) != 0)
			PCB::running->setMyThreadState(PCB::RUNNING);
		else{
			//PCB::running = PCB::idlePCB;
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
		if (request==0) {
		#ifndef  BCC_BLOCK_IGNORE
				asm int 60h;
				tick();
		#endif
		}

}

void Context::init() {
	PCB::main = (new Thread(150, 5))->getMyPCB();
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
