#include "main.h"




#define THREAD_ARRAY_ADDR	0x01DDBD78
#define THREAD_COUNT_ADDR	0x01DDBD80

int ThreadArray::GetThreadCount()
{
	return *(int*)(THREAD_COUNT_ADDR);
}

scrThread* ThreadArray::GetThreadByName(char* a_szName)
{
	scrThread* l_Thread;
	struct sysArray<scrThread>* l_pThreadArray = (struct sysArray<scrThread>*)THREAD_ARRAY_ADDR;
	int i;


	l_Thread = 0;
	i = 0;

	while(i < l_pThreadArray->uSize && l_Thread == 0 && l_pThreadArray->pData != 0)
	{
		if(l_pThreadArray->pData[i])
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

	while(i < l_pThreadArray->uSize && l_Thread == 0 && l_pThreadArray->pData != 0)
	{
		if(l_pThreadArray->pData[i])
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

