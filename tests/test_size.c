#include <stdlib.h>
#include <malloc/malloc.h>
#include <stdio.h>
#include "ft_malloc.h"

int main()
{
	const size_t	size = 100;
	void			*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Malloc fail\n");
		return (1);
	}
	printf("%s\nsize :\t%zu\nmgs :\t%zu\nms :\t%zu\n",
		"On teste printf en même temps.",
		size,
		malloc_good_size(size),
		malloc_size(ptr));
	free(ptr);
	return (0);
}
