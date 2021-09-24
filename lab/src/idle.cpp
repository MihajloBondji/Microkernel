/*
 * idle.cpp
 *
 *  Created on: Aug 31, 2021
 *      Author: OS1
 */

#include "idle.h"

volatile int i=0;

void Idle::run(){
	int j=i+1;
	while(i!=j){
		i++;
		j--;
	}
}
