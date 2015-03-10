#ifndef __NATIVECALL_H__
#define __NATIVECALL_H__

struct NativeList
{	
	struct Natives*	prevList;
	unsigned int 	funcs[7];
	unsigned int 	count;
	unsigned int 	hashes[7];	
};

class NativeCall
{
public:	

	void Invoke(unsigned int hash, NativeArg* a_pArgs)
	{
		NativeList* nativeList = ((NativeList**) 0x01E5F838)[hash & 0xFF];

		do
		{
			for(unsigned int i = 0; i < nativeList->uiNativeCount; i++)
			{
				if(nativeList->hashes[i] == hash)
				{
					((void (*)(NativeArg*))nativeList->funcs[i])(a_pArgs);
					return;
				}
			}

			nativeList = nativeList->prevList;
		}
		while(nativeList);
	}


	template<typename R>
	R Invoke(unsigned int hash, unsigned int argc, ...)
	{
		va_list vaList;
		va_start(vaList, argc);

		NativeArg argv;

		for(unsigned int i = 0; i < argc; i++)
			argv.Push(va_arg(vaList, unsigned int));

		va_end(vaList);

		Invoke(hash, &argv);

		return argv.GetResult<R>();
	}
};



#endif
