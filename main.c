#include "ft_malloc.h"

/*
		sys		usr
	0	187		248
	1	442		250 (TINY) || 518
	2	185		248 (TINY) || 1274
	3
	4
	5
*/

#include <unistd.h>

int main()
{
	int i;
	// char *addr;

	i = 0;
	show_alloc_mem();
	write(1, ">>>>>\n", 6);
	while (i < 1024)
	{
		addr = (char*)malloc(256);
		addr[0] = 42;
		// free(addr);
		i++;
	}
	write(1, "<<<<<\n", 6);
	show_alloc_mem();
	return (0);
} 
