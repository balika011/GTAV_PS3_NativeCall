#ifndef __THREADARRAY_H__
#define __THREADARRAY_H__


template <typename T>
struct sysArray
{
	T**					pData;
	short				uCount;
	short				uSize;
};


// Script Thread Array

namespace ThreadArray
{
	inline int GetThreadCount();
	inline void SetThreadCount(int a_iValue);

	scrThread* GetThreadByName(char* a_szName);
	scrThread* GetThreadByHash(unsigned int a_uiHash);

	void DbgShowAllThread();


	scrThread* NewThread(char* a_szThreadName);


};


#endif