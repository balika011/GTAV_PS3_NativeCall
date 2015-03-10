#include "main.h"

#define THREAD_ARRAY_ADDR	0x01E5FE80
#define THREAD_COUNT_ADDR	0x01E5FE84
#define threadArray ((struct sysArray<scrThread>*)THREAD_ARRAY_ADDR);
#define threadCount (*(int*)(THREAD_COUNT_ADDR));

scrThread* ThreadArray::GetThreadByName(char* name)
{
	scrThread* ret = 0;

	int i = 0;
	while(i < threadArray->uCount && ret == 0 && threadArray->pData != 0)
	{
		if(threadArray->pData[i]->m_iThreadID)
			if(strcmp(threadArray->pData[i]->m_szScriptName, name) == 0)
				ret = threadArray->pData[i];
		++i;
	}
	return ret;
}

scrThread* ThreadArray::GetThreadByHash(unsigned int hash)
{
	scrThread* ret = 0;
	
	int i = 0;
	while(i < threadArray->uCount && ret == 0 && threadArray->pData != 0)
	{
		if(threadArray->pData[i]->m_iThreadID)
			if(threadArray->pData[i]->m_iThreadHash == hash)
				ret = threadArray->pData[i];
		++i;
	}
	return ret;
}

void ThreadArray::DbgShowAllThread()
{
	int i = 0;
	while(i < threadArray->uCount)
	{
		if(threadArray->pData[i]->m_iThreadID)
			printf("Id %d: Thread id %d - %s\n", i, threadArray->pData[i]->m_iThreadID, threadArray->pData[i]->m_szScriptName);
		++i;
	}

	printf("Count %d\n", threadArray->uCount);
}


scrThread* ThreadArray::NewThread(char* name)
{
	int i = 0;
	while(i < threadArray->uCount && threadArray->pData[i]->m_iThreadID != 0)
		++i;

	// we failed to find a free slot
	if(i == threadArray->uCount)
		return 0;

	scrThread* newThread = new scrThread(name);
	threadArray->pData[i] = newThread;

	newThread->m_iThreadID = ++threadCount;

	newThread->reset();

	return newThread;
}
