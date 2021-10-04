// File: event.h
#ifndef _event_h_
#define _event_h_
typedef unsigned char IVTNo;

class Event {
public:
friend class KernelEv;
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();

protected:
 void signal();

private:
 KernelEv* myImpl;

};
#endif
