#include "main.h"


SYS_MODULE_INFO("GTA V Mod Menu", 0, 1, 1);
SYS_MODULE_START(EntryPoint);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(FakeExportFunction, LIBNAME);


sys_ppu_thread_t	g_MainThreadID;


void (*scrThread_loop_original)(scrThread*, int);


int float_int(float f)
{
	return *(int*)&f;
}

void scrThread__loop(scrThread* __this, int r4)
{
	// Here you call your natives.

	// PLAYER::PLAYER_ID(); // - for example, to retrieve player id
	// OBJECT::DOES_PICKUP_EXIST(0); // blahblah

	scrThread_loop_original(__this, r4);
}

#pragma pack(push, 1)
struct GTAThread__VMT
{
	void* dtor;
	void* unknown;
	void* reset;
	void* parse;
	void* loop;
	void* kill;
	void* virtual_function_6;
};
#pragma pack(pop, 1)

void MainThread(uint64_t)
{
	scrThread*			l_MainPersistent;
	GTAThread__VMT*		l_ThreadVMT;
	GTAThread__VMT*		l_NewVMT;

	// First Step, wait until the script 'main_persistent' is loaded	
	printf("Waiting for 'main_persistent' to be found.\n");
	do
	{
		sys_timer_sleep(1);
		l_MainPersistent = ThreadArray::GetThreadByName("main_persistent");		
	}
	while(l_MainPersistent == 0);
	printf("Script 'main_persistent' found !\n");

	// Second Step, Hijack loop virtual function

	printf("Retrieving original GTAThread VMT and Hijackig it...\n");
	l_ThreadVMT = *(GTAThread__VMT**)l_MainPersistent;				// Get VMT address
	l_NewVMT = (GTAThread__VMT*)malloc(sizeof(GTAThread__VMT));		// Alloc a new VMT struct
	memcpy(l_NewVMT, l_ThreadVMT, sizeof(GTAThread__VMT));			// copy the real VMT to the new one
	scrThread_loop_original = (void(*)(scrThread*, int))l_ThreadVMT->loop;
	l_NewVMT->loop = (void*)scrThread__loop;						// Change the loop addr 
	*(GTAThread__VMT**)l_MainPersistent = l_NewVMT;					// Hijack the VMT
	printf("Done !\n");

	for(;;)
	{
		// This thread is useless
		// we need it to make the sprx always loaded on memory
		sys_timer_sleep(5);
	}

}


extern "C" int FakeExportFunction()
{
	return CELL_OK;
}

extern "C" int EntryPoint()
{
	if(sys_ppu_thread_create(&g_MainThreadID, MainThread, 0, 1000, 2048, 0, "GTA V Mod Menu") != CELL_OK)
	{
		printf("Unable to create the Thread !");
	}

	return SYS_PRX_RESIDENT;
}
