#include "ft_malloc.h"

#include <unistd.h>

/*
int main()
{
	int i;
	char *addr;

	i = 0;
	show_alloc_mem();
	write(1, ">>>>>\n", 6);
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	write(1, "<<<<<\n", 6);
	show_alloc_mem();
	return (0);
} 
*/

#include "unistd.h"

int main()
{
	show_alloc_mem();

	write (1, " ------------ \n", 15);

	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}
