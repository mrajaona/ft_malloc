#include "ft_malloc.h"

void	*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	return (NULL);
}