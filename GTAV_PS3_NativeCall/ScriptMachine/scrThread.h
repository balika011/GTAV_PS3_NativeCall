#ifndef __SCRTHREAD_H__
#define __SCRTHREAD_H__


extern uint32_t jenkins_one_at_a_time_hash(char *key, size_t len);

unsigned int __shittyHack();
void CallNativesHere();

#pragma pack(push, 1)
class scrThread
{
public:

	scrThread(char* a_szName)
	{
		//printf("scrThread()\n");
		m_iThreadID		= 0;
		m_iThreadHash	= jenkins_one_at_a_time_hash(a_szName, strlen(a_szName));
		m_iThreadState	= 0;
		m_iIP			= 0;
		m_iFrameSP		= 0;
		m_iStackPointer = 0;
		m_iTimerA		= 0;
		m_iTimerB		= 0;
		m_fWaitTime		= 0.0f;
		m_iUnk0028		= 0;
		m_iUnk002C		= 0;
		m_iUnk0030		= 0;
		m_iUnk0034		= 0;
		m_iUnk0038		= 0;
		m_iUnk003C		= 0;
		m_iVarsOnStack	= 0;
		m_iUnk0044		= 0;
		m_iUnk0048		= 0;
		m_iUnk004C		= 0;
		m_iUnk0050		= 0;
		m_pStack		= 0;
		m_iUnk0058		= 0;
		m_iUnk005C		= 0;
		m_iUnk0060		= 0;
		m_szQuitMessage	= "Why a quit message ? who cares ?";
		
		strcpy(m_szScriptName, a_szName);
	}

	virtual ~scrThread()
	{
		//printf("~scrThread()\n");
	}

	virtual void virtual_function_1()
	{
		//printf("virtual_function_1()\n");
	}

	virtual void reset()
	{
		//printf("reset()\n");

		m_iThreadID		= 0;
		m_iThreadState	= 0;
		m_iIP			= 0;
		m_iFrameSP		= 0;
		m_iStackPointer = 0;
		m_iTimerA		= 0;
		m_iTimerB		= 0;
		m_fWaitTime		= 0.0f;
		m_iUnk0028		= 0;
		m_iUnk002C		= 0;
		m_iUnk0030		= 0;
		m_iUnk0034		= 0;
		m_iUnk0038		= 0;
		m_iUnk003C		= 0;
		m_iVarsOnStack	= 0;
		m_iUnk0044		= 0;
		m_iUnk0048		= 0;
		m_iUnk004C		= 0;
		m_iUnk0050		= 0;
		m_pStack		= 0;
		m_iUnk0058		= 0;
		m_iUnk005C		= 0;
		m_iUnk0060		= 0;
	}

	virtual void parse()
	{
		unsigned int l_iOldThread;
		unsigned int l_iRegister13;

		l_iRegister13 = __shittyHack();

		l_iOldThread = *(unsigned int*)(l_iRegister13 - 0x6FA0);
		*(unsigned int*)(l_iRegister13 - 0x6FA0) = (unsigned int)this;
		*(unsigned char*)(l_iRegister13 - 0x6F9C) = 1;


		CallNativesHere();


		*(unsigned int*)(l_iRegister13 - 0x6FA0) = l_iOldThread;
		*(unsigned char*)(l_iRegister13 - 0x6F9C) = 0;
	}

	virtual void loop()
	{
		//printf("loop()\n");
	}

	virtual void kill()
	{
		//printf("kill()\n");
	}

//private:
	//void* 	__vmt;				// + 0x00
	int		m_iThreadID;		// + 0x04
	int		m_iThreadHash;		// + 0x08
	int		m_iThreadState;		// + 0x0C
	int		m_iIP;				// + 0x10
	int		m_iFrameSP;			// + 0x14
	int		m_iStackPointer;	// + 0x18
	int		m_iTimerA;			// + 0x1C
	int		m_iTimerB;			// + 0x20
	float 	m_fWaitTime;		// + 0x24
	int 	m_iUnk0028;			// + 0x28
	int 	m_iUnk002C;			// + 0x2C
	int 	m_iUnk0030;			// + 0x30
	int 	m_iUnk0034;			// + 0x34
	int 	m_iUnk0038;			// + 0x38
	int 	m_iUnk003C;			// + 0x3C
	int 	m_iVarsOnStack;		// + 0x40
	int 	m_iUnk0044;			// + 0x44
	int 	m_iUnk0048;			// + 0x48
	int 	m_iUnk004C;			// + 0x4C
	int 	m_iUnk0050;			// + 0x50
	void*	m_pStack;			// + 0x54
	int 	m_iUnk0058;			// + 0x58
	int 	m_iUnk005C;			// + 0x5C
	int 	m_iUnk0060;			// + 0x60
	char* 	m_szQuitMessage;	// + 0x64
	char	m_szScriptName[24];	// + 0x68	
};

#pragma pack(pop)

#endif // CScript_h