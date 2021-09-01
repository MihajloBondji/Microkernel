/*
 * syncPrintf.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: OS1
 */
#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>

int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
		return res;
}



