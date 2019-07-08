#include "ft_malloc.h"

#include <unistd.h>

int main()
{
	int i;
	char *addr;

	i = 0;
	show_alloc_mem();
	write(1, ">>>>>\n", 6);
	while (i < 1024)
	{
		addr = (char*)malloc(256);
		addr[0] = 42;
		free(addr);
		i++;
	}
	write(1, "<<<<<\n", 6);
	show_alloc_mem();
	return (0);
} 
