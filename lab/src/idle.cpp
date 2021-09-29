/*
 * idle.cpp
 *
 *  Created on: Aug 31, 2021
 *      Author: OS1
 */

#include "idle.h"
#include "pcb.h"
volatile int i=0;

Idle::Idle():Thread(defaultStackSize,1){
	this->getMyPCB()->setMyThreadState(PCB::IDLE);
}

void Idle::run(){
	int j=i+1;
	while(i!=j){
		i++;
		j--;
	}
}
