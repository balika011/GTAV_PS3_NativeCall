#include "main.h"

sys_ppu_thread_t g_MainThreadID;

// Thanks wikipedia
uint32_t jenkins_one_at_a_time_hash(char *key, size_t len)
{
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

int float_int(float f)
{
	return *(int*)&f;
}

void CallNativesHere()
{

}

void MainThread(uint64_t)
{
	while(ThreadArray::GetThreadByName("main") == 0)
		sys_timer_sleep(1);

	printf("Creating our own thread.\n");
	while(ThreadArray::NewThread("NativeCallThread") == 0)
		sys_timer_usleep(100);
	printf("Thread created, have fun!\n");

	for(;;)
	{
		// This thread is useless
		// we need it to make the sprx always loaded on memory
		sys_timer_sleep(5);
	}
}

// Just a dummy, useless function.
extern "C" int FakeExportFunction()
{
	return CELL_OK;
}
SYS_LIB_EXPORT(FakeExportFunction, LIBNAME);

extern "C" int EntryPoint()
{
	if(sys_ppu_thread_create(&g_MainThreadID, MainThread, 0, 1000, 2048, 0, "GTA V NativeCall") != CELL_OK)
	{
		printf("Unable to create the Thread !");
	}

	return SYS_PRX_RESIDENT;
}
SYS_MODULE_START(EntryPoint);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_MODULE_INFO("GTA V NativeCall", 0, 1, 1);
