#ifndef __THREADARRAY_H__
#define __THREADARRAY_H__


template <typename T>
struct sysArray
{
	T**	pData;
	short	uCount;
	short	uSize;
};


// Script Thread Array

namespace ThreadArray
{
	scrThread* GetThreadByName(char* name);
	scrThread* GetThreadByHash(unsigned int hash);

	void DbgShowAllThread();

	scrThread* NewThread(char* name);
};


#endif
