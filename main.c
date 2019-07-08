#include "ft_malloc.h"

#include <unistd.h>

int main()
{
	int i;
	char *addr;
	char *zone;
	size_t	size = (1 << 12);

	i = 0;
	show_alloc_mem();
	write(1, ">>>>>\n", 6);

	zone = (char*)malloc(size);

	while (i < 1024)
	{
		addr = (char*)malloc(size);
		addr[0] = 42;
		free(addr);
		i++;
	}
	write(1, "<<<<<\n", 6);
	show_alloc_mem();
	return (0);
} 
