/*
 * main.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: OS1
 */
#include "contex.h"
#include "thread.h"
#include "pcb.h"
#include <iostream.h>

extern int userMain(int argc, char **argv);

int main(int argc, char**argv){
cout<<"Start\n";
Context::init();
cout<<"Init\n";
int a = userMain(argc,argv);
cout<<"userMain\n";
Context::restore();
cout<<"End\n";
return a;
}


