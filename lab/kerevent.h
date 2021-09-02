/*
 * kerevent.h
 *
 *  Created on: Sep 2, 2021
 *      Author: OS1
 */

#ifndef KEREVENT_H_
#define KEREVENT_H_

class PCB;
typedef unsigned char IVTNo;

class KernelEv{
public:
	 friend class Event;
	 friend class IVTEntry;
	 void signal();
	 void setOwnerBlocked(int i);
	 int getOwnerBlocked();
private:
	 KernelEv(IVTNo ivtNo);
  ~KernelEv();

  void wait();
  int ownerBlocked;
  IVTNo ivtNo;
  PCB* owner;
};



#endif /* KEREVENT_H_ */
