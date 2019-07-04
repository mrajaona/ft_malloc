#include <string.h>
#include <unistd.h>

#include "ft_malloc.h"

int main(void)
{
	char	*tmp[10];
	int		i;

	i = 0;
	while (i < 10)
	{
		// tmp[i] = malloc(1025);
		tmp[i] = malloc(16);
		if (tmp[i])
		{
			strcpy(tmp[i], "abcdefghijklmn\n");
			write(1, tmp[i], 15);
		}
		else
			write(1, "not allocated\n", 14);
		i++;
	}

	show_alloc_mem();

	i = 0;
	while (i < 10)
	{
		free(tmp[i]);
		i++;
	}

	show_alloc_mem();

	return (0);
}
