#ifndef __THREADARRAY_H__
#define __THREADARRAY_H__


template <typename T>
struct sysArray
{
	T**					pData;
	short				uSize;
	short				uCount;
};


// Script Thread Array

namespace ThreadArray
{
	int GetThreadCount();

	scrThread* GetThreadByName(char* a_szName);
	scrThread* GetThreadByHash(unsigned int a_uiHash);


};


#endif