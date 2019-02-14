#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	(void)ac; (void)av;

	void *a = malloc(1 << 6);
	void *b = malloc(1 << 7);
	void *c = malloc(1 << 8);

	free(a);
	free(b);
	free(c);

	a = malloc(1 << 4);
	b = malloc(1 << 4);
	c = malloc(1 << 4);

	a = realloc(a, 1 << 2);
	b = realloc(b, 1 << 10);
	c = realloc(c, 0);

	if (realloc(a + 5, 1 << 2) == NULL)
		write(1, "NULL\n", 5);

	free(a);
	free(b);
	free(c);


	// while (1){;}

	return (0);
}