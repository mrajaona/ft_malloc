#include "ft_malloc.h"

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main()
{
	int i;
	char *addr;
	struct rusage usage;

	i = 0;
	show_alloc_mem();
	write(1, ">>>>>\n", 6);
//	while (i < 1024)
	while (i < 10)
	{
		getrusage(RUSAGE_SELF, &usage);
		ft_printf("1 > %li\n", usage.ru_minflt);

		addr = (char*)malloc(1500);
		addr[0] = 42;

		getrusage(RUSAGE_SELF, &usage);
		ft_printf("2 > %li\n", usage.ru_minflt);

		free(addr);
		addr = NULL;

		i++;

		getrusage(RUSAGE_SELF, &usage);
		ft_printf("3 > %li\n", usage.ru_minflt);

	}
	write(1, "<<<<<\n", 6);
	show_alloc_mem();
	return (0);
} 
