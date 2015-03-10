#include "../main.h"

#define unk_whit_thread_addr 0x6F94
#define thread_addr 0x6F98

unsigned int GetR13Reg()
{
	__asm("mr %r3, %r13");
}

scrThread::scrThread(char* a_szName)
{
	m_iThreadID = 0;
	m_iThreadHash = jenkins_one_at_a_time_hash(a_szName, strlen(a_szName));
	m_iThreadState = 0;
	m_iIP = 0;
	m_iFrameSP = 0;
	m_iStackPointer = 0;
	m_iTimerA = 0;
	m_iTimerB = 0;
	m_fWaitTime = 0.0f;
	m_iUnk0028 = 0;
	m_iUnk002C = 0;
	m_iUnk0030 = 0;
	m_iUnk0034 = 0;
	m_iUnk0038 = 0;
	m_iUnk003C = 0;
	m_iVarsOnStack	= 0;
	m_iUnk0044 = 0;
	m_iUnk0048 = 0;
	m_iUnk004C = 0;
	m_iUnk0050 = 0;
	m_pStack = 0;
	m_iUnk0058 = 0;
	m_iUnk005C = 0;
	m_iUnk0060 = 0;
	m_szQuitMessage	= "Why a quit message ? who cares ?";
	
	strcpy(m_szScriptName, a_szName);
}

scrThread::~scrThread()
{

}

void scrThread::virtual_function_1()
{

}

void scrThread::reset()
{
	m_iThreadID = 0;
	m_iThreadState = 0;
	m_iIP = 0;
	m_iFrameSP = 0;
	m_iStackPointer = 0;
	m_iTimerA = 0;
	m_iTimerB = 0;
	m_fWaitTime = 0.0f;
	m_iUnk0028 = 0;
	m_iUnk002C = 0;
	m_iUnk0030 = 0;
	m_iUnk0034 = 0;
	m_iUnk0038 = 0;
	m_iUnk003C = 0;
	m_iVarsOnStack = 0;
	m_iUnk0044 = 0;
	m_iUnk0048 = 0;
	m_iUnk004C = 0;
	m_iUnk0050 = 0;
	m_pStack = 0;
	m_iUnk0058 = 0;
	m_iUnk005C = 0;
	m_iUnk0060 = 0;
}

void scrThread::parse()
{
	unsigned int r13 = GetR13Reg();

	unsigned int oldThread = *(unsigned int*)(r13 - thread_addr);
	*(unsigned int*)(r13 - thread_addr) = (unsigned int)this;
	*(unsigned char*)(r13 - unk_whit_thread_addr) = 1;

	CallNativesHere();

	*(unsigned int*)(r13 - thread_addr) = oldThread;
	*(unsigned char*)(r13 - unk_whit_thread_addr) = 0;
}

void scrThread::loop()
{

}

void scrThread::kill()
{

}
