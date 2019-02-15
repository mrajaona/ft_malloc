#include <unistd.h>
// #include <stdlib.h>

# include "ft_malloc.h"

int	main(int ac, char **av)
{
	(void)ac; (void)av;
	void *a = NULL;
	void *b = NULL;
	void *c = NULL;

	if (!a) write(1, "a is NULL\n", 10);
	if (!b) write(1, "b is NULL\n", 10);
	if (!c) write(1, "c is NULL\n", 10);

	show_mem_alloc();
	write(1, "1 --\n", 5);

	a = malloc(1 << 6);
	b = malloc(0);
	c = malloc(1 << 11);

	if (!a) write(1, "a is NULL\n", 10);
	if (!b) write(1, "b is NULL\n", 10);
	if (!c) write(1, "c is NULL\n", 10);

	show_mem_alloc();
	write(1, "2 --\n", 5);

	free(a); a = NULL;
	free(b); b = NULL;
	free(c); c = NULL;
	return (0);
}