#ifndef __SCRTHREAD_H__
#define __SCRTHREAD_H__


extern uint32_t jenkins_one_at_a_time_hash(char *key, size_t len);

void CallNativesHere();

#pragma pack(push, 1)
class scrThread
{
	int	m_iThreadID;
	int	m_iThreadHash;
	int	m_iThreadState;
	int	m_iIP;
	int	m_iFrameSP;
	int	m_iStackPointer;
	int	m_iTimerA;
	int	m_iTimerB;
	float 	m_fWaitTime;
	int 	m_iUnk0028;
	int 	m_iUnk002C;
	int 	m_iUnk0030;
	int 	m_iUnk0034;
	int 	m_iUnk0038;
	int 	m_iUnk003C;
	int 	m_iVarsOnStack;
	int 	m_iUnk0044;
	int 	m_iUnk0048;
	int 	m_iUnk004C;
	int 	m_iUnk0050;
	void*	m_pStack;
	int 	m_iUnk0058;
	int 	m_iUnk005C;
	int 	m_iUnk0060;
	char* 	m_szQuitMessage;
	char	m_szScriptName[24];

public:
	scrThread(char* a_szName);

	virtual ~scrThread();

	virtual void virtual_function_1();

	virtual void reset();

	virtual void parse();

	virtual void loop();

	virtual void kill();
};

#pragma pack(pop)

#endif // CScript_h
