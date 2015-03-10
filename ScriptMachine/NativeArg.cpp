#include "../main.h"

NativeArg::NativeArg()
{	
	m_uiArgCount = 0;
	m_uiReadCount = 0;

	m_pvArgValues = (int *)malloc(32 * sizeof(unsigned int));
	m_pvReturnValues = m_pvArgValues;
}

NativeArg::~NativeArg()
{
	if(m_pvReturnValues)
	{
		free((void*)m_pvReturnValues);
	}
}

