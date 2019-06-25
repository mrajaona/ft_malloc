#include "realloc.h"

void	*realloc(void *ptr, size_t size)
{
    write(1, "r", 1); // debug
	if (ptr == NULL)
		return (malloc(size));
	return (NULL);
}