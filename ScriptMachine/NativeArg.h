#ifndef __NATIVEARG_H__
#define __NATIVEARG_H__

#pragma pack(push, 1)
class NativeArg
{
private:
	int* m_pvReturnValues;
	unsigned int m_uiArgCount;
	int* m_pvArgValues;
	unsigned int m_uiReadCount;

public:
	NativeArg();
	~NativeArg();

	template<typename T>
	inline void Push(T a_Value)
	{
		if(sizeof(T) <= 4)
		{
			*(T*)&m_pvArgValues[m_uiArgCount] = a_Value;
			m_uiArgCount++;
		}
	}

	template<typename T>
	inline T GetResult()
	{
		T* Result = (T*)&m_pvReturnValues[m_uiReadCount];

		m_uiReadCount += sizeof(T);
		if((sizeof(T) % 4) != 0)
			m_uiReadCount += 4 - (sizeof(T) % 4);

		return *Result;
	}
};
#pragma pack(pop)

#endif
