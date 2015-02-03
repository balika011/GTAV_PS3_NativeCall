#ifndef __SCRTHREAD_H__
#define __SCRTHREAD_H__

#pragma pack(push, 1)

class scrThread
{
public:

	virtual void virtual_function_0() = 0;
	virtual void virtual_function_1() = 0;
	virtual void reset() = 0;
	virtual void parse() = 0;
	virtual void loop() = 0;
	virtual void kill() = 0;
	virtual void virtual_function_6() = 0;


//private:
	//void* 	__vmt;				// + 0x00
	int 	m_iThreadID;		// + 0x04
	int		m_iThreadHash;		// + 0x08
	int		m_iThreadState;		// + 0x0C	
	int 	m_iIP;				// + 0x10
	int 	m_iFrameSP;			// + 0x14
	int 	m_iStackPointer;	// + 0x18	
	int		m_iTimerA;			// + 0x1C
	int 	m_iTimerB;			// + 0x20
	int 	m_iUnk0024;			// + 0x24
	int 	m_iUnk0028;			// + 0x28
	int 	m_iUnk002C;			// + 0x2C
	int 	m_iUnk0030;			// + 0x30
	int 	m_iUnk0034;			// + 0x34
	int 	m_iUnk0038;			// + 0x38
	int 	m_iUnk003C;			// + 0x3C
	int 	m_iUnk0040;			// + 0x40
	int 	m_iUnk0044;			// + 0x44
	int 	m_iUnk0048;			// + 0x48
	int 	m_iUnk004C;			// + 0x4C
	int 	m_iUnk0050;			// + 0x50	
	void*	m_pStack;			// + 0x54	
	int 	m_iUnk0058;			// + 0x58
	int 	m_iUnk005C;			// + 0x5C
	int 	m_iUnk0060;			// + 0x60
	int 	m_iUnk0064;			// + 0x64
	char	m_szScriptName[24];	// + 0x68	
};

#pragma pack(pop)

#endif // CScript_h