#include "ft_malloc.h"

void	*realloc(void *ptr, size_t size)
{
	write(1, "realloc\n", 8);
	if (ptr == NULL)
		return (malloc(size));
	return (NULL);
}