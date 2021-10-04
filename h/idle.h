/*
 * idle.h
 *
 *  Created on: Aug 31, 2021
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "Thread.h"

class Idle :public Thread{
public:
	friend class Context;
	Idle();
protected:
  void run();
  void start();
};




#endif /* IDLE_H_ */
