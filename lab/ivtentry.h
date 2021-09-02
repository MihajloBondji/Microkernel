/*
 * ivtentry.h
 *
 *  Created on: Sep 2, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "kerevent.h"
#include "contex.h"

class IVTEntry {
	KernelEv* myKernelEvent;
public:
	friend class KernelEv;
	IVTNo ivtNo;
	static IVTEntry* ivtEntry[256];
	IVTEntry(IVTNo ivtNo,interruptPointer routine);
	~IVTEntry();
	void signal();
	void setEvent(KernelEv * myKernelEvent);
	interruptPointer defaultRoutine;
	static void initEntries();
};

#define PREPAREENTRY(entryNumber, shouldCallDefault)\
	void interrupt inter##entryNumber(...);\
	IVTEntry ivtEntry##entryNumber(entryNumber, inter##entryNumber);\
	void interrupt inter##entryNumber(...){\
        if(shouldCallDefault == 1) \
			(ivtEntry##entryNumber.defaultRoutine)();\
		ivtEntry##entryNumber.signal();\
}


#endif /* IVTENTRY_H_ */
