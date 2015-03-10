#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/memory.h>

void * operator new (std::size_t sz)
{
	void *p;

	/* malloc (0) is unpredictable; avoid it. */
	if (sz == 0)
		sz = 1;

	p = malloc (sz);
	return p;
}


void operator delete (void *ptr)
{
	free(ptr);
}


namespace std
{

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

	void *memset(void *m, int c, size_t n)
	{
		char *s = (char *) m;

		while (n-- != 0)
		{
			*s++ = (char) c;
		}

		return m;
	}

	void *memcpy(void *dst0, const void *src0, size_t len0)
	{
		char *dst = (char *)dst0;
		char *src = (char *)src0;

		void *save = dst0;

		while (len0--)
			*dst++ = *src++;

		return save;
	}

	int memcmp(const void* s1, const void* s2,size_t n)
	{
		const unsigned char *p1 = (const unsigned char*)s1, *p2 = (const unsigned char*)s2;
		while(n--)
			if( *p1 != *p2 )
				return *p1 - *p2;
			else
				*p1++,*p2++;
		return 0;
	}


	size_t strlen(const char *s) {
		const char *p = s;
		while (*s) ++s;
		return s - p;
	}

	
	const char *strchr(const char *s, int c)
	{
		while (*s != (char)c)
			if (!*s++)
				return (char*)0;
		return (char *)s;
	}
	
	const char *strrchr(const char *s, int c)
	{
		char* ret=0;
		do {
			if( *s == (char)c )
				ret=(char*)s;
		} while(*s++);
		return (const char*) ret;
	}
	
	const char *strstr(const char *s1, const char *s2)
	{
		size_t n = strlen(s2);
		while(*s1)
			if(!memcmp(s1++,s2,n))
				return s1-1;
		return 0;
	}

	int strncasecmp (const char *s1, const char *s2, size_t n)
	{
	  int c1, c2;
	  while (n > 0)
		{
		  c1 = *((unsigned char *)(s1++));
		  if (c1 >= 'A' && c1 <= 'Z')
			c1 = c1 + ('a' - 'A');
		  c2 = *((unsigned char *)(s2++));
		  if (c2 >= 'A' && c2 <= 'Z')
			c2 = c2 + ('a' - 'A');
		  if (c1 != c2)
			{
			  return (c1 - c2);
			}
		  if (c1 == '\0')
			{
			  return 0;
			}
		  --n;
		}
	  return 0;
	}

	int strcasecmp (__const char *s1, __const char *s2)
	{
	  int c1, c2, n;
	  n=strlen(s1);
	  while (n > 0)
		{
		  c1 = *((unsigned char *)(s1++));
		  if (c1 >= 'A' && c1 <= 'Z')
			c1 = c1 + ('a' - 'A');
		  c2 = *((unsigned char *)(s2++));
		  if (c2 >= 'A' && c2 <= 'Z')
			c2 = c2 + ('a' - 'A');
		  if (c1 != c2)
			{
			  return (c1 - c2);
			}
		  if (c1 == '\0')
			{
			  return 0;
			}
		  --n;
		}
	  return 0;
	}

	int strncmp(const char* s1, const char* s2, size_t n)
	{
		if(n==0) return 0;
		while(*s1 && (*s1==*s2))
		{
			s1++,s2++;
			n--;
			if(n==0) break;
		}
		return *(const unsigned char*)s1-*(const unsigned char*)s2;
	}

	int strcmp(const char* s1, const char* s2)
	{
		while(*s1 && (*s1==*s2))
			s1++,s2++;
		return *(const unsigned char*)s1-*(const unsigned char*)s2;
	}


	char *strcpy(char *dest, const char* src)
	{
		char *ret = dest;
		while (*dest++ = *src++)
			;
		return ret;
	}


	char *strncpy(char *dest, const char *src, size_t n)
	{
		char *ret = dest;
		do {
			if (!n--)
				return ret;
		} while (*dest++ = *src++);
		while (n--)
			*dest++ = 0;
		return ret;
	}

	char *strcat(char *dest, const char *src)
	{
		char *ret = dest;
		while (*dest)
			dest++;
		while (*dest++ = *src++)
			;
		return ret;
	}

	char *strtok(char * str, const char * delim)
	{
		static char* p=0;
		if(str)
			p=str;
		else if(!p)
			return 0;
		str=p+strspn(p,delim);
		p=str+strcspn(str,delim);
		if(p==str)
			return p=0;
		p = *p ? *p=0,p+1 : 0;
		return str;
	}

	size_t strcspn(const char *s1, const char *s2)
	{
		size_t ret=0;
		while(*s1)
			if(strchr(s2,*s1))
				return ret;
			else
				s1++,ret++;
		return ret;
	}

	size_t strspn(const char *s1, const char *s2)
	{
		size_t ret=0;
		while(*s1 && strchr(s2,*s1++))
			ret++;
		return ret;
	}

};
