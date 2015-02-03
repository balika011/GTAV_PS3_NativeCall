#include "main.h"

/*
void* malloc(uint32_t a_uiSize)
{
	sys_addr_t l_uiAddr;

	a_uiSize = ((a_uiSize+65536)/65536)*65536;

	sys_memory_allocate(a_uiSize, SYS_MEMORY_PAGE_SIZE_64K, &l_uiAddr);

	return (void*)l_uiAddr;
}

void free(void* a_Addr)
{
	sys_memory_free((sys_addr_t)a_Addr);
}
*/