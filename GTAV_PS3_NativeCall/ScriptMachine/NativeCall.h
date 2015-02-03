#ifndef __NATIVECALL_H__
#define __NATIVECALL_H__

struct Natives // SNative
{	
	struct Natives*	pLastNativesTable;			// + 0x00
	unsigned int 	uiNativeFunctions[7];		// + 0x04
	unsigned int 	uiNativeCount;				// + 0x20
	unsigned int 	uiNativeHashes[7];			// + 0x24	
};



static Natives** g_Natives = (Natives**) 0x01DDB730;


class NativeCall
{
public:	

	void Invoke(unsigned int a_uiNativeHash, NativeArg* a_pArgs)
	{
		Natives*		l_pNatives;

		l_pNatives = g_Natives[a_uiNativeHash & 0xFF];

		do
		{
			for(unsigned int l_uiIndex = 0; l_uiIndex < l_pNatives->uiNativeCount; l_uiIndex++)
			{
				if(l_pNatives->uiNativeHashes[l_uiIndex] == a_uiNativeHash)
				{
					((void (*)(NativeArg*))l_pNatives->uiNativeFunctions[l_uiIndex])(a_pArgs);
					return;
				}
			}

			l_pNatives = l_pNatives->pLastNativesTable;
		}
		while(l_pNatives);
	}


	template<typename R>
	R Invoke(unsigned int a_uiNativeHash, unsigned int a_uiArgCount, ...)
	{
		NativeArg		l_Args;
		va_list			l_VaList;
		unsigned int	l_uiIndex;


		va_start(l_VaList, a_uiArgCount);
		for(l_uiIndex = 0; l_uiIndex < a_uiArgCount; l_uiIndex++)
		{
			l_Args.Push(va_arg(l_VaList, unsigned int));
		}
		va_end(l_VaList);

		Invoke(a_uiNativeHash, &l_Args);

		return l_Args.GetResult<R>();
	}
};



#endif