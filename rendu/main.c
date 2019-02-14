#include <unistd.h>
// #include <stdlib.h>

# include "ft_malloc.h"

int	main(int ac, char **av)
{
	(void)ac; (void)av;

	void *a = malloc(1 << 6);
	void *b = malloc(1 << 7);
	void *c = malloc(1 << 8);

	show_mem_alloc();

	free(a);
	free(b);
	free(c);

	a = malloc(1 << 4);
	b = malloc(1 << 4);
	c = malloc(1 << 4);

	show_mem_alloc();

	a = realloc(a, 1 << 2);
	b = realloc(b, 1 << 10);
	c = realloc(c, 0);

	if (realloc(a + 5, 1 << 2) == NULL)
		write(1, "NULL\n", 5);

	show_mem_alloc();

	free(a);
	free(b);
	free(c);

	show_mem_alloc();

	return (0);
}