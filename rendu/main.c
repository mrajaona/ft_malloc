#include <stdlib.h>

int	main(int ac, char **av)
{
	(void)ac; (void)av;

	void *a = malloc(1 << 6);
	void *b = malloc(1 << 7);
	void *c = malloc(1 << 8);

	free(a);
	free(b);
	free(c);

	return (0);
}