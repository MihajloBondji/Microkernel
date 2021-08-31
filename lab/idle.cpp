/*
 * idle.cpp
 *
 *  Created on: Aug 31, 2021
 *      Author: OS1
 */

#include "idle.h"

volatile int i=0,j=1;
void Idle::run(){
	while(i!=j){
		i++;
		j--;
	}
}
