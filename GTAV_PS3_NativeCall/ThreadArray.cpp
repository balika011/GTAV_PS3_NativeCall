#include "main.h"




#define THREAD_ARRAY_ADDR	0x01E5FE80
#define THREAD_COUNT_ADDR	0x01E5FE84

int ThreadArray::GetThreadCount()
{
	return *(int*)(THREAD_COUNT_ADDR);
}

void ThreadArray::SetThreadCount(int a_iValue)
{
	*(int*)(THREAD_COUNT_ADDR) = a_iValue;
}

scrThread* ThreadArray::GetThreadByName(char* a_szName)
{
	scrThread* l_Thread;
	struct sysArray<scrThread>* l_pThreadArray = (struct sysArray<scrThread>*)THREAD_ARRAY_ADDR;
	int i;


	l_Thread = 0;
	i = 0;

	while(i < l_pThreadArray->uCount && l_Thread == 0 && l_pThreadArray->pData != 0)
	{
		if(l_pThreadArray->pData[i]->m_iThreadID)
		{			
			if(strcmp(l_pThreadArray->pData[i]->m_szScriptName, a_szName) == 0)
			{
				l_Thread = l_pThreadArray->pData[i];
			}
		}
		i ++;
	}
	return l_Thread;
}

scrThread* ThreadArray::GetThreadByHash(unsigned int a_uiHash)
{
	scrThread* l_Thread;
	struct sysArray<scrThread>* l_pThreadArray = (struct sysArray<scrThread>*)THREAD_ARRAY_ADDR;
	int i;


	l_Thread = 0;
	i = 0;

	while(i < l_pThreadArray->uCount && l_Thread == 0 && l_pThreadArray->pData != 0)
	{
		if(l_pThreadArray->pData[i]->m_iThreadID)
		{
			
			if(l_pThreadArray->pData[i]->m_iThreadHash == a_uiHash)
			{
				l_Thread = l_pThreadArray->pData[i];
			}
		}
		i ++;
	}
	return l_Thread;
}

void ThreadArray::DbgShowAllThread()
{
	struct sysArray<scrThread>* l_pThreadArray = (struct sysArray<scrThread>*)THREAD_ARRAY_ADDR;
	int i;

	i = 0;

	while(i < l_pThreadArray->uCount)
	{
		if(l_pThreadArray->pData[i]->m_iThreadID)
		{
			printf("Id %d : Thread id %d - %s\n", i, l_pThreadArray->pData[i]->m_iThreadID, l_pThreadArray->pData[i]->m_szScriptName);
		}
		i++;
	}

	printf("Count %d\n", l_pThreadArray->uCount);

}


scrThread* ThreadArray::NewThread(char* a_szThreadName)
{
	struct sysArray<scrThread>* l_pThreadArray = (struct sysArray<scrThread>*)THREAD_ARRAY_ADDR;
	int i;
	scrThread* l_pNewThread;

	i = 0;

	//printf("Searching for a free slot.\n");

	// let's find a free slot
	while(i < l_pThreadArray->uCount && l_pThreadArray->pData[i]->m_iThreadID != 0)
	{
		i++;
	}

	//printf("Free slot found, id %d\n", i);
	//printf("Thread count %d\n", l_pThreadArray->uCount);

	// we failed to find a free slot
	if(i == l_pThreadArray->uCount) return 0;

	//printf("Allocating new thread.\n");
	l_pNewThread = new scrThread(a_szThreadName);			// I need to alloc mine to be sure the method stored on the vmt are mine
//	printf("Free Thread addr 0x%08X\n", l_pThreadArray->pData[i]);
	l_pThreadArray->pData[i] = l_pNewThread;
	//printf("Allocated at addr 0x%08X\n", l_pNewThread);

	l_pNewThread = l_pThreadArray->pData[i];
	//printf("New thread addr 0x%08X\n", l_pNewThread);
	l_pNewThread->m_iThreadID = GetThreadCount() + 1;
	//printf("Setting new thread id to %d\n", l_pNewThread->m_iThreadID);
	SetThreadCount(l_pNewThread->m_iThreadID);
	//printf("Setting thread count to %d\n", l_pNewThread->m_iThreadID);
	l_pNewThread->reset();
	//printf("Resetted.\n");

	return l_pNewThread;
}