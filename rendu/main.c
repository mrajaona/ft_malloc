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
	b = malloc(1 << 7);
	c = malloc(1 << 8);

	if (!a) write(1, "a is NULL\n", 10);
	if (!b) write(1, "b is NULL\n", 10);
	if (!c) write(1, "c is NULL\n", 10);

	show_mem_alloc();
	write(1, "2 --\n", 5);

	free(a); a = NULL;
	free(b); b = NULL;
	free(c); c = NULL;

	a = malloc(1 << 4);
	b = malloc(1 << 4);
	c = malloc(1 << 4);

	if (!a) write(1, "a is NULL\n", 10);
	if (!b) write(1, "b is NULL\n", 10);
	if (!c) write(1, "c is NULL\n", 10);

	show_mem_alloc();
	write(1, "3 --\n", 5);

	free(a); a = NULL;
	free(b); b = NULL;
	free(c); c = NULL;

	a = malloc(1 << 12);
	b = malloc(1 << 12);
	c = malloc(1 << 12);

	if (!a) write(1, "a is NULL\n", 10);
	if (!b) write(1, "b is NULL\n", 10);
	if (!c) write(1, "c is NULL\n", 10);

	show_mem_alloc();
	write(1, "4 --\n", 5);

	free(a); a = NULL;
	free(b); b = NULL;
	free(c); c = NULL;

	a = realloc(a, 1 << 2);
	b = realloc(b, 1 << 10);
	c = realloc(c, 0); // free

	if (!a) write(1, "a is NULL\n", 10);
	if (!b) write(1, "b is NULL\n", 10);
	if (!c) write(1, "c is NULL\n", 10);

	if (realloc(a + 5, 1 << 2) == NULL)
		write(1, "-N\n", 3);

	show_mem_alloc();
	write(1, "5 --\n", 5);

	free(a); a = NULL;
	free(b); b = NULL;
	free(c); c = NULL;

	if (!a) write(1, "a is NULL\n", 10);
	if (!b) write(1, "b is NULL\n", 10);
	if (!c) write(1, "c is NULL\n", 10);

	show_mem_alloc();
	write(1, "6 --\n", 5);
	return (0);
}