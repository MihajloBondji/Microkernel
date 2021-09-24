// File: thread.h
#ifndef _thread_h_
#define _thread_h_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
const StackSize maxStackSize = 65536;

typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

class PCB; // Kernel's implementation of a user's thread

class Thread {
public:

 void start();
 void waitToComplete();
 virtual ~Thread();

 ID getId();
 static ID getRunningId();
 static Thread * getThreadById(ID id);


protected:
 friend class PCB;
 friend class List;
 friend class Context;
 Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
 virtual void run() {}
 PCB* getMyPCB();

 List* myWaitingList;
private:
 PCB* myPCB;
 volatile static ID id;
 ID myID;
};
void dispatch ();
#endif
