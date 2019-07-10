#include "malloc.h"

void *calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = malloc(count * size);
	// TODO : set memory to 0
	if (ptr)
		ft_memset(ptr, count * size);
	return (ptr);
}